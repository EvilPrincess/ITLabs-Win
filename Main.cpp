#include "main.h"
#include "Lab.h"
using namespace SpecialFunctionsForLabs;



//		GLOBAL VARIABLES
//
MainWindow MainWnd = { };
char BUFFER[40] = { };

HWND PalindromEdit = { };
HWND PalindromStatic = { };
HWND SEdit = { };
HWND SStatic = { };


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
	MainWnd.SetWindow(CreateWindow(L"MainWndClass", L"������������ �4", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, 100, 100, 870, 300, NULL, NULL, NULL, NULL));
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
				case OnClearAllClicked:
				{
					SetWindowTextA(PalindromEdit, "");
					SetWindowTextA(PalindromStatic, "");
					SetWindowTextA(SEdit, "");
					SetWindowTextA(SStatic, "");
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
				case OnIsPalindromClicked:
				{
					GetWindowTextA(PalindromEdit, BUFFER, 40);
					SetWindowTextA(PalindromStatic, string(Palindrom(string(BUFFER))? "���������" : "�� ���������").c_str());
					break;
				}

				case OnSSolveClicked:
				{
					GetWindowTextA(SEdit, BUFFER, 40);
					string str = string(BUFFER);
					if (!is_natural(str))
					{
						MessageBoxA(hWnd, "�������� ���� ������ ���� ����������� ����� ������!", "������ �����!", MB_OK);
						break;
					}
					UINT n = stoi(str);
					double res = S(n);
					SetWindowTextA(SStatic, dtos(res).c_str());
					break;
				}
			}
			break;
		}

		case WM_PAINT:
		{
			RECT r;
			//HBRUSH hbr;
			HPEN hpen;
			HDC hDC;
			PAINTSTRUCT ps;

			hDC = BeginPaint(hWnd, &ps);

			GetClientRect(hWnd, &r);

			hpen = CreatePen(PS_SOLID, 5, RGB(70, 70, 70));
			SelectObject(hDC, hpen);

			Rectangle(hDC, 10, 80, 400, r.bottom - 15);
			Rectangle(hDC, 450, 80, 840, r.bottom - 15);

			hpen = CreatePen(PS_DOT, 1, RGB(70, 70, 70));
			SelectObject(hDC, hpen);
			DrawLine(hDC, 133, 133, 384, 133);
			DrawLine(hDC, 453 + 140, 133, 453 + 140 + 234, 133);

			EndPaint(hWnd, &ps);

			ReleaseDC(hWnd, hDC);
			DeleteObject(hpen);
			//DeleteObject(hbr);
			break;
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

	SendMessageA(CreateWindowA("static", "���� 4", WS_CHILD | WS_VISIBLE | SS_CENTER, 0, y+=offset, 850, 40, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);
	SendMessageA(CreateWindowA("static", "������� 19", WS_CHILD | WS_VISIBLE | SS_CENTER, 0, y += offset, 850, 40, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);
	y += offset + 23;
	SendMessageA(CreateWindowA("static", "������ 1", WS_CHILD | WS_VISIBLE | SS_CENTER, 13, y, 384, 30, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);
	SendMessageA(CreateWindowA("static", "������ 2", WS_CHILD | WS_VISIBLE | SS_CENTER, 453, y, 384, 30, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);

	// ������ ���� ���������� ����
	//
	// ������ 1
	//
	CreateWindowA("static", "������� ������: ", WS_CHILD | WS_VISIBLE, 13, y+=offset, 130, 20, hWnd, NULL, NULL, NULL);
	PalindromEdit = CreateWindowA("edit", "", WS_CHILD | WS_VISIBLE, 130, y, 254, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("button", "���������", WS_CHILD | WS_VISIBLE, 50, y+=offset, 130, 20, hWnd, (HMENU)OnIsPalindromClicked, NULL, NULL);
	PalindromStatic = CreateWindowA("static", "...", WS_CHILD | WS_VISIBLE | SS_CENTER, 220, y, 150, 20, hWnd, NULL, NULL, NULL);
	//
	// ������ 2
	//
	CreateWindowA("static", "������� ���. �����: ", WS_CHILD | WS_VISIBLE, 453, y -= offset, 145, 20, hWnd, NULL, NULL, NULL);
	SEdit = CreateWindowA("edit", "", WS_CHILD | WS_VISIBLE, 453 + 140, y, 234, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("button", "���������", WS_CHILD | WS_VISIBLE, 453 + 50, y += offset, 130, 20, hWnd, (HMENU)OnSSolveClicked, NULL, NULL);
	SStatic = CreateWindowA("static", "...", WS_CHILD | WS_VISIBLE | SS_CENTER, 453 + 220, y, 150, 20, hWnd, NULL, NULL, NULL);

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