#include "main.h"
#include "Lab.h"
#include "Time.h"
using namespace SpecialFunctionsForLabs;



//		GLOBAL VARIABLES
//
MainWindow MainInst = { };
RECT r;
char BUFFER[40] = { };
HWND MainWnd = { };
HWND NewBtn1 = { };
HWND NewBtn2 = { };
HWND SolveBtn1 = { };
HWND SolveBtn2 = { };
HWND Output1 = { };
HWND Output2 = { };

vector<trainwnd> trainlines;
UINT tly;

vector<playerwnd> playerlines;
UINT ply;

UINT newDelete = 100;

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
		WS_VISIBLE, 100, 100, 1800, 900, NULL, NULL, NULL, NULL));
	MainWnd = MainInst.GetWindow();
	MainInst.Redraw(MainWnd);
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
	UINT y = -30, offset = 30;

	SendMessageA(CreateWindowA("static", "Лаба 5", WS_CHILD | WS_VISIBLE | SS_CENTER, r.right / 4 - 100, y += offset + 3, 847, 40, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);
	SendMessageA(CreateWindowA("static", "Вариант 19", WS_CHILD | WS_VISIBLE | SS_CENTER, r.right / 4 - 100, y += offset, 847, 30, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);
	y += offset + 23;
	SendMessageA(CreateWindowA("static", "Задача 1", WS_CHILD | WS_VISIBLE | SS_CENTER, 13, y, 384, 30, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);
	SendMessageA(CreateWindowA("static", "Задача 2", WS_CHILD | WS_VISIBLE | SS_CENTER, r.right - 453, y, 384, 30, hWnd, NULL, NULL, NULL), WM_SETFONT, (WPARAM)titlef, 0);

	// Дальше идет реализация лабы
	NewBtn1 = CreateWindowA("button", "Добавить запись (максимум 10)", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10, y += offset, 240, 20, hWnd, (HMENU)OnNewLinePressed1, NULL, NULL);
	NewBtn2 = CreateWindowA("button", "Добавить запись (максимум 10)", WS_CHILD | WS_VISIBLE | SS_CENTER,
		r.right - 453, y, 240, 20, hWnd, (HMENU)OnNewLinePressed2, NULL, NULL);
	tly = ply = y += offset;
	// заголовок таблицы 1
	CreateWindowA("static", "Пункт назначения", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10, y, 140, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Номер поезда", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10 + 140 + 10, y, 140, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Время отправления", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10 + 140 + 10 + 140 + 10, y, 140, 20, hWnd, NULL, NULL, NULL);
	// заголовок таблицы 2
	CreateWindowA("static", "Вес", WS_CHILD | WS_VISIBLE | SS_CENTER,
		r.right - (90), y, 80, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Рост", WS_CHILD | WS_VISIBLE | SS_CENTER,
		r.right - (90 * 2), y, 80, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Возраст", WS_CHILD | WS_VISIBLE | SS_CENTER,
		r.right - (90 * 3), y, 80, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Номер", WS_CHILD | WS_VISIBLE | SS_CENTER,
		r.right - (90 * 4), y, 80, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Отчество", WS_CHILD | WS_VISIBLE | SS_CENTER,
		r.right - (90 * 4 + 150), y, 140, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Имя", WS_CHILD | WS_VISIBLE | SS_CENTER,
		r.right - (90 * 4 + 150 * 2), y, 140, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Фамилия", WS_CHILD | WS_VISIBLE | SS_CENTER,
		r.right - (90 * 4 + 150 * 3), y, 140, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Команда", WS_CHILD | WS_VISIBLE | SS_CENTER,
		r.right - (90 * 4 + 150 * 4), y, 140, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Страна", WS_CHILD | WS_VISIBLE | SS_CENTER,
		r.right - (90 * 4 + 150 * 5), y, 140, 20, hWnd, NULL, NULL, NULL);

	CreateWindowA("static", "Номер", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER,
		10, r.bottom - 200, 140, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER,
		10 + 140 + 10, r.bottom - 200, 140, 20, hWnd, (HMENU)EditNum1, NULL, NULL);
	CreateWindowA("button", "Найти запись", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10 + 150 + 150, r.bottom - 200, 140, 20, hWnd, (HMENU)Solve1, NULL, NULL);
	CreateWindowA("static", "Пункт назначения", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10, r.bottom-172, 140, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Номер поезда", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10 + 140 + 10, r.bottom-172, 140, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Время отправления", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10 + 140 + 10 + 140 + 10, r.bottom-172, 140, 20, hWnd, NULL, NULL, NULL);
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
	BOOL toMove = FALSE;
	UINT toDel = -1;
	for (UINT i = 0; i < trainlines.size(); i++)
	{
		trainwnd train = trainlines[i];
		if (train.onDelete == wParam)
		{
			train.Delete();
			toMove = TRUE;
			toDel = i;
			continue;
		}
		if (toMove) train.move();
	}
	if (toDel != -1)
	{
		trainlines.erase(trainlines.begin() + toDel);
		tly -= 28;
		toDel = -1;
	}
	toMove = FALSE;
	for (UINT i = 0; i < playerlines.size(); i++)
	{
		playerwnd player = playerlines[i];
		if (player.onDelete == wParam)
		{
			player.Delete();
			toMove = TRUE;
			toDel = i;
			continue;
		}
		if (toMove) player.move();
	}
	if (toDel != -1)
	{
		playerlines.erase(playerlines.begin() + toDel);
		ply -= 28;
		toDel = -1;
	}
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
		case OnNewLinePressed1:
		{
			if (trainlines.size() == 10) break;

			trainwnd newtrain = { };

			newtrain.NAZN = CreateWindowA("edit", "", WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
				10, tly+=28, 140, 20, hWnd, NULL, NULL, NULL);
			newtrain.NUMR = CreateWindowA("edit", "", WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
				10 + 140 + 10, tly, 140, 20, hWnd, NULL, NULL, NULL);
			newtrain.TIME = CreateWindowA("edit", "", WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
				10 + 140 + 10 + 140 + 10, tly, 140, 20, hWnd, NULL, NULL, NULL);
			newtrain.DelBtn = CreateWindowA("button", "Удалить запись", WS_CHILD | WS_VISIBLE | SS_CENTER,
				10 + 140 + 10 + 140 + 10 + 140 + 10, tly, 140, 20, hWnd, (HMENU)(newtrain.onDelete = newDelete++), NULL, NULL);
			newtrain.y = tly;

			trainlines.push_back(newtrain);

			break;
		}

		case OnNewLinePressed2:
		{
			if (playerlines.size() == 10) break;

			playerwnd np = { };

			np.weight = CreateWindowA("edit", "", WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
				r.right - (90), ply += 28, 80, 20, hWnd, NULL, NULL, NULL);
			np.height = CreateWindowA("edit", "", WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
				r.right - (90 * 2), ply, 80, 20, hWnd, NULL, NULL, NULL);
			np.age = CreateWindowA("edit", "", WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
				r.right - (90 * 3), ply, 80, 20, hWnd, NULL, NULL, NULL);
			np.num = CreateWindowA("edit", "", WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
				r.right - (90 * 4), ply, 80, 20, hWnd, NULL, NULL, NULL);
			np.otchestvo = CreateWindowA("edit", "", WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
				r.right - (90 * 4 + 150), ply, 140, 20, hWnd, NULL, NULL, NULL);
			np.name = CreateWindowA("edit", "", WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
				r.right - (90 * 4 + 150 * 2), ply, 140, 20, hWnd, NULL, NULL, NULL);
			np.surname = CreateWindowA("edit", "", WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
				r.right - (90 * 4 + 150 * 3), ply, 140, 20, hWnd, NULL, NULL, NULL);
			np.team = CreateWindowA("edit", "", WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
				r.right - (90 * 4 + 150 * 4), ply, 140, 20, hWnd, NULL, NULL, NULL);
			np.origin = CreateWindowA("edit", "", WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
				r.right - (90 * 4 + 150 * 5), ply, 140, 20, hWnd, NULL, NULL, NULL);
			np.DelBtn = CreateWindowA("button", "Удалить запись", WS_CHILD | WS_VISIBLE | SS_CENTER,
				r.right - (90 * 4 + 150 * 6), ply, 140, 20, hWnd, (HMENU)(np.onDelete = newDelete++), NULL, NULL);
			np.y = ply;
			np.mr = r;

			playerlines.push_back(np);

			break;
		}

		case Solve1:
		{

			break;
		}

		case Solve2:
		{

			break;
		}
	}
}
void MainWindow::Redraw(HWND hWnd)
{
	RECT r;
	HDC hDC;

	GetClientRect(hWnd, &r);

	hDC = GetDC(hWnd);

	/*Rectangle(hDC, 10, 80, r.bottom - 10, 400);
	Rectangle(hDC, r.right - 400, 80, r.bottom - 10, r.right - 10);*/

	ReleaseDC(hWnd, hDC);
}
void MainWindow::OnCreated(HWND hWnd)
{
	GetClientRect(hWnd, &r);
	MainInst.AddMenus(hWnd);
	MainInst.AddWidgets(hWnd);
}
