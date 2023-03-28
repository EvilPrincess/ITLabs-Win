#include "main.h"


MainWindow MainWnd = { };
DrawingRectClass DR = { };
std::vector<POINT> PTBUFFER = { };

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	WNDCLASS MainWndClass = MainWindow::NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst,
		LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", MainWindow::MainWndProc);

	DR = DrawingRectClass();

	if (!RegisterClassW(&MainWndClass)) { return -1; }


	MSG MainWndMessage = { 0 };



	//CreateWindow(L"MainWndClass", L"My Dumb Program", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 1600, 900, NULL, NULL, NULL, NULL);
	MainWnd.SetWindow(CreateWindow(L"MainWndClass", L"My Dumb Program 2.0", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, 100, 100, 900, 710, NULL, NULL, NULL, NULL));
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
		switch (wParam)
		{
		case OnClearClicked:
		{
			InvalidateRect(DR.GetWindow(), NULL, TRUE);
			UpdateWindow(DR.GetWindow());
			break;
		}
		}
	}

	case WM_CREATE:
	{
		MainWnd.AddMenus(hWnd);
		MainWnd.AddWidgets(hWnd);
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

	//AppendMenu(FileMenu, MF_STRING, OnNewClicked, L"Новый граф (CTRL+N)");
	//AppendMenu(FileMenu, MF_STRING, OnLoadGraphClicked, L"Загрузить граф (CTRL+L)");
	//AppendMenu(FileMenu, MF_STRING, OnSaveClicked, L"Сохранить (CTRL+S)");
	//AppendMenu(FileMenu, MF_STRING, OnSaveAsClicked, L"Сохранить как (CTRL+ALT+S)");
	//AppendMenu(FileMenu, MF_SEPARATOR, NULL, NULL);
	//AppendMenu(FileMenu, MF_STRING, OnExitClicked, L"Выйти");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)WhatMenu, L"ЧаВо");

	/*AppendMenu(WhatMenu, MF_STRING, OnInfoClicked, L"Справка");
	AppendMenu(WhatMenu, MF_STRING, OnGitSourceClicked, L"Git Source");*/


	SetMenu(hWnd, RootMenu);
}
void MainWindow::AddWidgets(HWND hWnd)
{
	RECT r;
	GetClientRect(hWnd, &r);
	DR.SetWindow(CreateWindow(DR_WC, L"TheDrawingRect", WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 10, 10, r.right - 20, r.bottom - 60, hWnd, (HMENU)DR_IDX, NULL, NULL));
	CreateWindowA("button", "Очистить", WS_CHILD | WS_VISIBLE | SS_CENTER, 10, 610, 395, 40, hWnd, (HMENU)OnClearClicked, NULL, NULL);
	CreateWindowA("static", "Предположительно, это: ", WS_CHILD | WS_VISIBLE | SS_CENTER, 10 + 395 + 10, 610 + 10, 395, 40, hWnd, (HMENU)OnClearClicked, NULL, NULL);
}
void MainWindow::SetWindow(HWND _hWnd)
{
	hWnd = _hWnd;
}
HWND MainWindow::GetWindow()
{
	return hWnd;
}