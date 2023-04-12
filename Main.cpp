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
	MainInst.SetWindow(CreateWindow(L"MainWndClass", L"������������ �4", 
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
	// ������� �������
	HMENU RootMenu = CreateMenu();

	// ���������� ����'�
	HMENU FileMenu = CreateMenu();

	// ���������� ����
	HMENU WhatMenu = CreateMenu();

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)FileMenu, L"����");

	AppendMenu(FileMenu, MF_STRING, OnClearAllClicked, L"�������� ��� ����");
	AppendMenu(FileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(FileMenu, MF_STRING, OnExitClicked, L"�����");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)WhatMenu, L"����");

	AppendMenu(WhatMenu, MF_STRING, OnInfoClicked, L"�������");
	AppendMenu(WhatMenu, MF_STRING, OnGitSourceClicked, L"Git Source");


	SetMenu(hWnd, RootMenu);
}
void MainWindow::AddWidgets(HWND hWnd)
{
	RECT r;
	UINT y=-30, offset = 30;
	GetClientRect(hWnd, &r);

	SendMessageA(CreateWindowA("static", "���� 5", WS_CHILD | WS_VISIBLE | SS_CENTER, 3, y+=offset+3, 847, 40, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);
	SendMessageA(CreateWindowA("static", "������� 19", WS_CHILD | WS_VISIBLE | SS_CENTER, 3, y += offset, 847, 30, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);
	y += offset + 23;
	SendMessageA(CreateWindowA("static", "������ 1", WS_CHILD | WS_VISIBLE | SS_CENTER, 13, y, 384, 30, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);
	SendMessageA(CreateWindowA("static", "������ 2", WS_CHILD | WS_VISIBLE | SS_CENTER, 453, y, 384, 30, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);

	// ������ ���� ���������� ����
	//
	// ������ 1
	//
	
	//
	// ������ 2
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
	// �.�. WinAPI �� ���������� ������� ��� ��������� ����� ��
	// ����� �� �����, � LineTo ��������� �������� ������� �� �������,
	// �������� MoveToEx(), ������� ���� �������:
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
			MessageBoxA(hWnd, "������� ��������������� ����������� �����������\n���������: ����\n�������: ������� (09.03.04)\n������: ���12\n�������: ����� �. �.\n\n������� ������� ���������� ��� ���������� ��� ��� ����������.", "�������", MB_OK);
			break;
		}

		case OnGitSourceClicked:
		{
			ShellExecute(0, 0, L"https://github.com/EvilPrincess/ITLabs-Win.git", 0, 0, SW_SHOW);
			break;
		}

		//
		// ����
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
