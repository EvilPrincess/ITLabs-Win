#include "main.h"
#include "Lab.h"
#include "Time.h"
using namespace SpecialFunctionsForLabs;



//		GLOBAL VARIABLES
//
MainWindow MainInst = { };
char BUFFER[40] = { };


//		FONTS
//
HFONT titlef = CreateFontA(24, 8, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Comic Sans MS");
HFONT textf = CreateFontA(21, 9, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "Calibri");



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	WNDCLASS MainWndClass = MainWindow::NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst,
		LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", MainWindow::MainWndProc);

	if (!RegisterClassW(&MainWndClass)) { return -1; }


	MSG MainWndMessage = { 0 };



	//CreateWindow(L"MainWndClass", L"My Dumb Program", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 1600, 900, NULL, NULL, NULL, NULL);
	MainInst.SetWindow(CreateWindow(L"MainWndClass", L"Лабораторная №4", 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | 
		WS_VISIBLE, 100, 100, 870, 600, NULL, NULL, NULL, NULL));
	while (GetMessage(&MainWndMessage, NULL, NULL, NULL)) {
		TranslateMessage(&MainWndMessage);
		DispatchMessage(&MainWndMessage);
	}
}

WNDCLASS MainWindow::NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) {
	WNDCLASS NWC = { 0 };

	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

LRESULT CALLBACK MainWindow::MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_COMMAND:
		{
			MainInst.CommandHandler(hWnd, uMsg, wParam, lParam);
			break;
		}

		case WM_CREATE:
		{
			MainInst.OnCreated(hWnd);
			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}

		default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
}
void MainWindow::AddMenus(HWND hWnd)
{
	// Менюшка вкладок
	HMENU RootMenu = CreateMenu();

	// Подменюшка Файл'а
	HMENU FileMenu = CreateMenu();

	// Подменюшка ЧаВО
	HMENU WhatMenu = CreateMenu();

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)FileMenu, L"Файл");

	AppendMenu(FileMenu, MF_STRING, OnClearAllClicked, L"Очистить все поля");
	AppendMenu(FileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(FileMenu, MF_STRING, OnExitClicked, L"Выйти");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)WhatMenu, L"ЧаВо");

	AppendMenu(WhatMenu, MF_STRING, OnInfoClicked, L"Справка");
	AppendMenu(WhatMenu, MF_STRING, OnGitSourceClicked, L"Git Source");


	SetMenu(hWnd, RootMenu);
}
void MainWindow::AddWidgets(HWND hWnd)
{
	RECT r;
	UINT y=-30, offset = 30;
	GetClientRect(hWnd, &r);

	SendMessageA(CreateWindowA("static", "Лаба 5", WS_CHILD | WS_VISIBLE | SS_CENTER, 3, y+=offset+3, 847, 40, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);
	SendMessageA(CreateWindowA("static", "Вариант 19", WS_CHILD | WS_VISIBLE | SS_CENTER, 3, y += offset, 847, 30, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);
	y += offset + 23;
	SendMessageA(CreateWindowA("static", "Задача 1", WS_CHILD | WS_VISIBLE | SS_CENTER, 13, y, 384, 30, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);
	SendMessageA(CreateWindowA("static", "Задача 2", WS_CHILD | WS_VISIBLE | SS_CENTER, 453, y, 384, 30, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);

	// Дальше идет реализация лабы
	//
	// Задача 1
	//
	
	//
	// Задача 2
	//
	

}
void MainWindow::SetWindow(HWND _hWnd)
{
	hWnd = _hWnd;
}
HWND MainWindow::GetWindow()
{
	return hWnd;
}
BOOL DrawLine(HDC hdc, int x1, int y1, int x2, int y2) {
	// т.к. WinAPI не предлагает функцию для рисования линии от
	// точки до точки, а LineTo принимает конечную позицию от текущей,
	// заданной MoveToEx(), напишем свою функцию:
	MoveToEx(hdc, x1, y1, NULL);
	return LineTo(hdc, x2, y2);
}
void MainWindow::CommandHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case OnClearAllClicked:
		{
			// TODO CLEAR
			break;
		}

		case OnExitClicked:
		{
			PostQuitMessage(0);
			break;
		}

		case OnInfoClicked:
		{
			MessageBoxA(hWnd, "Донской Государственный Технический Университет\nФакультет: ИиВТ\nКафедра: ПОВТиАС (09.03.04)\nГруппа: ВПР12\nСтудент: Фомин Н. А.\n\nПростое оконное приложение для реализации лаб Аси Михайловны.", "Справка", MB_OK);
			break;
		}

		case OnGitSourceClicked:
		{
			ShellExecute(0, 0, L"https://github.com/EvilPrincess/ITLabs-Win.git", 0, 0, SW_SHOW);
			break;
		}

		//
		// Лабы
		//
		
	}
}
void MainWindow::Redraw(HWND hWnd)
{
	RECT r;
	HDC hDC;

	GetClientRect(hWnd, &r);

	hDC = GetDC(hWnd);

	ReleaseDC(hWnd, hDC);
}
void MainWindow::OnCreated(HWND hWnd)
{
	MainInst.AddMenus(hWnd);
	MainInst.AddWidgets(hWnd);
}
