#pragma once

#include "base.h"

#define OnExitClicked 0
#define OnClearAllClicked 1
#define OnInfoClicked 2
#define OnGitSourceClicked 3

//		Индексы для лаб
//
#define OnIsPalindromClicked 4
#define OnSSolveClicked 5

class MainWindow
{
private:
	HWND hWnd;
public:
	void SetWindow(HWND _hWnd);
	HWND GetWindow();

	void AddMenus(HWND hWnd);
	void AddWidgets(HWND hWnd);
	void CommandHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	static WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
	static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

BOOL DrawLine(HDC hdc, int x1, int y1, int x2, int y2);