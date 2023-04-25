﻿#include "main.h"

Display* display = { };
Display* Display::p_instance = nullptr;
HINSTANCE hMainInst = { };

STATIC* st11, * st12, * st21, * st22;
BUTTON* bt11, * bt12, * bt21, * bt22;

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	Register();

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

	st11 = new STATIC(hWnd, "Выберите файл...", V3{ 10, 10, 0 }, ST11, V3{400, 720, 3}, stp); stp.textCol = V3(203, 30, 30);
	st12 = new STATIC(hWnd, "Файл не выбран!", V3{ 10 + 400 + 10, 10, 0 }, ST12, V3{400, 720, 3}, stp); stp.textCol = STATIC_DEFAULT_TEXTCOL;
	st21 = new STATIC(hWnd, "Выберите файл...", V3{ r.right - 10 - 400 - 10 - 400, 10, 0 }, ST21, V3{ 400, 720, 3 }, stp); stp.textCol = V3(203, 30, 30);
	st22 = new STATIC(hWnd, "Файл не выбран!", V3{ r.right - 10 - 400, 10, 0 }, ST22, V3{ 400, 720, 3 }, stp);

	//bt11 = new BUTTON(hWnd, "Открыть", );

}

void Display::OnResize(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

}

void Display::CommandHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		
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