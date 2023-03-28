#pragma once

#include "base.h"

#define OnExitClicked 0
#define OnClearAllClicked 1

class MainWindow
{
private:
	HWND hWnd;
public:
	void SetWindow(HWND _hWnd);
	HWND GetWindow();

	void AddMenus(HWND hWnd);
	void AddWidgets(HWND hWnd);

	static WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
	static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};