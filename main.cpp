#include "main.h"

Display* display = { };
Display* Display::p_instance = nullptr;
HINSTANCE hMainInst = { };

STATIC *st11, *st12, *st21, *st22;
BUTTON *bt11, *bt12, *bt21, *bt22;
HANDLE file1, file2;
char buffer1[16384], buffer2[16384];

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	InitLib();

	hMainInst = hInst;
	display = Display::GetInstance(V3{1665, 900, 0});


	MSG MainWndMessage = { };

	while (GetMessage(&MainWndMessage, NULL, NULL, NULL)) {
		TranslateMessage(&MainWndMessage);
		DispatchMessage(&MainWndMessage);
	}
}


Display::Display(const V3 _Size)
{
	DisplayRegister();
	wnd = GenWnd(_Size);
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

	RECT r;
	GetClientRect(hWnd, &r);
	
	// лаба 6 - интерфейс

	STATICPARAMS stp;
	stp.alignh = haligns::center;
	stp.alignv = valigns::top;
	stp.bdDefCol = BUTTON_DEFAULT_BDC + 60;

	new STATIC(hWnd, "Лабораторная работа №6", V3(10, 10, 0), NULL, V3{1630, 35, 4}, stp);
	new STATIC(hWnd, "Задача №1", V3(10, 10 + 30 + 10, 0), NULL, V3{810, 35, 3}, stp);
	new STATIC(hWnd, "Задача №2", V3(r.right - 820, 10 + 30 + 10, 0), NULL, V3{810, 35, 3}, stp);

	stp.bdDefCol = STATIC_DEFAULT_BORDER;
	st11 = new STATIC(hWnd, "Выберите файл...", V3{ 10, 10 + 70 + 10, 0 }, ST11, V3{400, 700, 3}, stp); stp.textCol = V3(203, 30, 30);
	st12 = new STATIC(hWnd, "Файл не выбран!", V3{ 10 + 400 + 10, 10 + 70 + 10, 0 }, ST12, V3{400, 700, 3}, stp); stp.textCol = STATIC_DEFAULT_TEXTCOL;
	st21 = new STATIC(hWnd, "Выберите файл...", V3{ r.right - 10 - 400 - 10 - 400, 10 + 70 + 10, 0 }, ST21, V3{ 400, 700, 3 }, stp); stp.textCol = V3(203, 30, 30);
	st22 = new STATIC(hWnd, "Файл не выбран!", V3{ r.right - 10 - 400, 10 + 70 + 10, 0 }, ST22, V3{ 400, 700, 3 }, stp);

	bt11 = new BUTTON(hWnd, "Открыть", V3{10, r.bottom - 60, 0}, BT11, V3{400, 50, 3});
	bt12 = new BUTTON(hWnd, "Вычислить", V3{ 10 + 400 + 10, r.bottom - 60, 0 }, BT12, V3{ 400, 50, 3 }); bt12->Disable();
	bt21 = new BUTTON(hWnd, "Открыть", V3{ r.right - 10 - 400 - 10 - 400, r.bottom - 60, 0 }, BT21, V3{ 400, 50, 3 });
	bt22 = new BUTTON(hWnd, "Вычислить", V3{ r.right - 10 - 400, r.bottom - 60, 0 }, BT22, V3{ 400, 50, 3 }); bt22->Disable();
}

void Display::OnResize(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

}

void Display::CommandHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		// открыть номер 1
		case BT11: 
		{
			OPENFILENAMEA ofn;
			char szFile[260];

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = szFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = "Text\0*.TXT\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			if (GetOpenFileNameA(&ofn) == TRUE)
			{
				file1 = CreateFileA(
					ofn.lpstrFile,
					GENERIC_READ,
					0,
					(LPSECURITY_ATTRIBUTES)NULL,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					(HANDLE)NULL
				);
				if (ReadFile(file1, buffer1, sizeof(buffer1), NULL, NULL))
				{
					st11->params.textCol = STATIC_DEFAULT_TEXTCOL;
					st11->SetAlignH(haligns::left);
					st11->SetText("Предпросмотр выбранного файла:\n\n" + string(buffer1));
				}
				else
				{
					st11->params.textCol = V3{ 203, 30, 30 };
					st11->params.alignh = haligns::center;
					st11->SetText("Ошибка чтения файла!");
					bt11->Enable();
					break;
				}
				bt12->Enable();
			}
			bt11->Enable();
			break;
		}
		// вычислить номер 1
		case BT12:
		{
			vector<char> uniq;
			for (char c : buffer1)
			{
				if (find(uniq.begin(), uniq.end(), c) == uniq.end()) uniq.push_back(c);
			}
			st12->params.textCol = STATIC_DEFAULT_TEXTCOL;
			st12->SetAlignH(haligns::left);
			st12->SetText("Уникальные символы файла:\n\n" + string(uniq.begin(), uniq.end()));
			break;
		}
		// открыть номер 2
		case BT21: 
		{
			OPENFILENAMEA ofn;
			char szFile[260];

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = szFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = "Text\0*.TXT\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			if (GetOpenFileNameA(&ofn) == TRUE)
			{
				file2 = CreateFileA(
					ofn.lpstrFile,
					GENERIC_READ,
					0,
					(LPSECURITY_ATTRIBUTES)NULL,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					(HANDLE)NULL
				);
				if (ReadFile(file2, buffer2, sizeof(buffer2), NULL, NULL))
				{
					st21->params.textCol = STATIC_DEFAULT_TEXTCOL;
					st21->SetAlignH(haligns::left);
					st21->SetText("Предпросмотр выбранного файла:\n\n" + string(buffer2));
				}
				else
				{
					st21->params.textCol = V3{ 203, 30, 30 };
					st21->params.alignh = haligns::center;
					st21->SetText("Ошибка чтения файла!");
					bt21->Enable();
					break;
				}
				bt22->Enable();
			}
			bt21->Enable();
			break;
		}
		// вычислить номер 2
		case BT22:
		{
			
			break;
		}
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

HWND Display::GenWnd(const V3 _Size)
{
	wnd = CreateWindow(DISPLAY_WC, L"My Windows Test Program",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN |
		WS_MINIMIZEBOX | WS_VISIBLE, 100, 100, _Size.x, _Size.y, NULL, NULL, NULL, NULL);
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

Display* Display::GetInstance(const V3 _Size)
{
	if (!p_instance)
		p_instance = new Display(_Size);
	return p_instance;
}