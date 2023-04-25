#include "main.h"

Display* display = { };
Display* Display::p_instance = nullptr;
HINSTANCE hMainInst = { };
EDIT* ed = { };
BUTTON* btn = { };

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	Register();

	hMainInst = hInst;
	display = Display::GetInstance();


	MSG MainWndMessage = { };

	while (GetMessage(&MainWndMessage, NULL, NULL, NULL)) {
		TranslateMessage(&MainWndMessage);
		DispatchMessage(&MainWndMessage);
	}
}


Display::Display()
{
	DisplayRegister();
	wnd = GenWnd();
}

LRESULT WINAPI Display::DisplayProc(HWND hWnd, 
	UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_COMMAND:
		CommandHandler(hWnd, wParam, lParam);
		break;
	case WM_CREATE:
		OnCreate(hWnd, wParam, lParam);
		break;
	case WM_TIMER:
		TimerManager(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

void Display::OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	SetTimer(hWnd, 0, 1000 / 144, NULL);
	EDITPARAMS edp = { };
	edp.bdFocCol = V3(255, 255, 255);

	// создаю "ЭДИТЫ" - в будущем сделаю из них галочки
	new EDIT(hWnd, "", V3(50, 50, 0), V3(60, 60, 3), edp);
	new EDIT(hWnd, "", V3(50+60+10, 50, 0), V3(60, 60, 3), edp);
	new EDIT(hWnd, "", V3(50+60+10+60+10, 50, 0), V3(60, 60, 3), edp);

	// создаю кнопки
	new BUTTON(hWnd, "A", V3(50, 120, 0), BUT1, V3(60, 60, 3));
	new BUTTON(hWnd, "B", V3(50+60+10, 120, 0), BUT2, V3(60, 60, 3));
	new BUTTON(hWnd, "C", V3(50+60+10+60+10, 120, 0), BUT3, V3(60, 60, 3));

	// создаю статики
	STATICPARAMS stp;
	stp.alignh = haligns::left;
	stp.alignv = valigns::top;
	STATIC* st = new STATIC(hWnd, "Это тип статик", V3(50 + 60 + 10 + 60 + 10 + 60 + 50, 50, 0), NULL, V3(300, 500, 3), stp);
	st->AddLine("другой текст");
}

void Display::OnResize(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

}

void Display::CommandHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case BUT1:
			MB("A pressed");
			break;
		case BUT2:
			MB("B pressed");
			break;
		case BUT3:
			MB("C pressed");
			break;
	}
}

void Display::TimerManager(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0) Display::Refresh(hWnd);
}

void Display::DisplayRegister()
{
	WNDCLASS NWC = { 0 };

	NWC.hIcon = LoadIcon(NULL, IDI_QUESTION);
	NWC.hCursor = LoadCursor(NULL, IDC_ARROW);
	NWC.hInstance = hMainInst;
	NWC.lpszClassName = DISPLAY_WC;
	NWC.hbrBackground = (HBRUSH)COLOR_WINDOW;
	NWC.lpfnWndProc = DisplayProc;

	RegisterClass(&NWC);
}

void Display::DisplayUnregister()
{

}

HWND Display::GetWnd()
{
	return wnd;
}

HWND Display::SetWnd(HWND hWnd)
{
	wnd = hWnd;
	return wnd;
}

HWND Display::GenWnd()
{
	wnd = CreateWindow(DISPLAY_WC, L"My Windows Test Program",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN |
		WS_MINIMIZEBOX | WS_VISIBLE, 100, 100, 700, 600, NULL, NULL, NULL, NULL);
	return wnd;
}

void Display::Refresh(HWND hWnd)
{
	RECT r;
	GetClientRect(hWnd, &r);
	HBRUSH hBrush = CreateSolidBrush(vRGB(MAIN_BK_COL));
	HDC hDC = GetDC(hWnd);
	HDC mDC = CreateCompatibleDC(hDC);
	HBITMAP mBM = CreateCompatibleBitmap(hDC, r.right, r.bottom);
	SelectObject(mDC, mBM);

	HGDIOBJ old = SelectObject(mDC, hBrush);
	Rectangle(mDC, 0, 0, r.right, r.bottom);

	BitBlt(hDC, 0, 0, r.right, r.bottom, mDC, 0, 0, SRCCOPY);

	SelectObject(mDC, old);

	ReleaseDC(hWnd, hDC);
	DeleteDC(mDC);
	DeleteBitmap(mBM);
	DeleteObject(hBrush);
	DeleteObject(old);
}

void MB(string _Msg, BOOL _IsWarning)
{
	MessageBoxA(NULL, _Msg.c_str(), "Да", _IsWarning ? MB_OK | MB_ICONERROR : MB_OK);
}

Display* Display::GetInstance()
{
	if (!p_instance)
		p_instance = new Display();
	return p_instance;
}