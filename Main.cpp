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
HWND Out11 = { };
HWND Out12 = { };
HWND Out13 = { };
HWND EditWnd1 = { };

vector<trainwnd> trainlines;
UINT tly;

vector<playerwnd> playerlines;
vector<playerwnd> outputted_playerlines;
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
	MainInst.SetWindow(CreateWindow(L"MainWndClass", L"Лабораторная №5", 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | 
		WS_VISIBLE, 100, 100, 2000, 900, NULL, NULL, NULL, NULL));
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
	EditWnd1 = CreateWindowA("edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER,
		10 + 140 + 10, r.bottom - 200, 140, 20, hWnd, (HMENU)EditNum1, NULL, NULL);
	CreateWindowA("button", "Найти запись", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10 + 150 + 150, r.bottom - 200, 140, 20, hWnd, (HMENU)Solve1, NULL, NULL);
	CreateWindowA("static", "Пункт назначения", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10, r.bottom-172, 140, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Номер поезда", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10 + 140 + 10, r.bottom-172, 140, 20, hWnd, NULL, NULL, NULL);
	CreateWindowA("static", "Время отправления", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10 + 140 + 10 + 140 + 10, r.bottom-172, 140, 20, hWnd, NULL, NULL, NULL);
	Out11 = CreateWindowA("static", "", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10, r.bottom - 154, 140, 20, hWnd, NULL, NULL, NULL);
	Out12 = CreateWindowA("static", "", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10+150, r.bottom - 154, 140, 20, hWnd, NULL, NULL, NULL);
	Out13 = CreateWindowA("static", "", WS_CHILD | WS_VISIBLE | SS_CENTER,
		10+150+150, r.bottom - 154, 140, 20, hWnd, NULL, NULL, NULL);

	CreateWindowA("button", "Информация о самой молодой команде", 
		WS_CHILD | WS_VISIBLE | SS_CENTER,
		r.right - (90 * 4 + 150 * 5), r.bottom - 400, 300, 20, hWnd, (HMENU)Solve2, NULL, NULL);
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

			np.weight = CreateWindowA("edit", "", ES_NUMBER | WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
				r.right - (90), ply += 28, 80, 20, hWnd, NULL, NULL, NULL);
			np.height = CreateWindowA("edit", "", ES_NUMBER | WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
				r.right - (90 * 2), ply, 80, 20, hWnd, NULL, NULL, NULL);
			np.age = CreateWindowA("edit", "", ES_NUMBER | WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
				r.right - (90 * 3), ply, 80, 20, hWnd, NULL, NULL, NULL);
			np.num = CreateWindowA("edit", "", ES_NUMBER | WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
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
			char toFind[256];
			GetWindowTextA(EditWnd1, toFind, 256);
			for (trainwnd train : trainlines)
			{
				char NUMR[256];
				GetWindowTextA(train.NUMR, NUMR, 256);
				if (string(NUMR) == string(toFind))
				{
					char NAZN[256];
					char TIME[256];
					GetWindowTextA(train.NAZN, NAZN, 256);
					GetWindowTextA(train.TIME, TIME, 256);
					SetWindowTextA(Out11, NAZN);
					SetWindowTextA(Out12, NUMR);
					SetWindowTextA(Out13, TIME);
				}
			}
			break;
		}

		case Solve2:
		{
			// уберем все выводы
			for (playerwnd pl : outputted_playerlines)
			{
				pl.Delete();
			}
			outputted_playerlines.clear();

			// заполним вектор инфы для удобства
			vector<Player> players_infos;
			for (playerwnd plwnd : playerlines)
			{
				Player np = { };
				char buf[256];

				GetWindowTextA(plwnd.age, buf, 256);
				if (string(buf) != "") np.age = stoi(string(buf));
				GetWindowTextA(plwnd.height, buf, 256);
				if (string(buf) != "") np.height = stoi(string(buf));
				GetWindowTextA(plwnd.name, buf, 256);
				np.fio.name = string(buf);
				GetWindowTextA(plwnd.num, buf, 256);
				if (string(buf) != "") np.num = stoi(string(buf));
				GetWindowTextA(plwnd.origin, buf, 256);
				np.origin = string(buf);
				GetWindowTextA(plwnd.otchestvo, buf, 256);
				np.fio.otchestvo = string(buf);
				GetWindowTextA(plwnd.surname, buf, 256);
				np.fio.surname = string(buf);
				GetWindowTextA(plwnd.team, buf, 256);
				np.team = string(buf);
				GetWindowTextA(plwnd.weight, buf, 256);
				if (string(buf) != "") np.weight = stoi(string(buf));

				players_infos.push_back(np);
			}

			// проверим, остались ли незаполненные поля
			for (Player p : players_infos)
			{
				if (p.age == 0 || p.fio.name == "" || p.fio.surname == "" ||
					p.fio.otchestvo == "" || p.height == 0 || p.num == 0 ||
					p.origin == "" || p.team == "" || p.weight == 0) {
					MessageBoxA(NULL, "Заполните все пустые поля!", "Ошибка", MB_OK | MB_ICONERROR);
					return;
				}
			}

			// заполним вектор всех возрастов
			vector<pair<string, UINT>> ages;
			for (Player p : players_infos)
			{
				// эта команда уже есть в векторе?
				BOOL found = FALSE;
				for (pair<string, UINT> para : ages)
				{
					if (para.first == p.team)
					{
						para.second += p.age;
						found = TRUE;
						break;
					}
				}
				if (!found) ages.push_back(pair<string, UINT>{p.team, p.age});
			}

			// найдем самую молодую команду
			pair<string, UINT> smol = { "a", 99999 };
			for (pair<string, UINT> para : ages) if (para.second < smol.second) smol = para;

			// выведем информацию о ней
			UINT cur_off = 344 + 28;
			for (Player p : players_infos)
			{
				if (p.team == smol.first)
				{
					playerwnd npw = { };
					npw.weight = CreateWindowA("static", to_string(p.weight).c_str(), WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
						r.right - (90), r.bottom - (cur_off -= 28), 80, 20, hWnd, NULL, NULL, NULL);
					npw.height = CreateWindowA("static", to_string(p.height).c_str(), WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
						r.right - (90 * 2), r.bottom - cur_off, 80, 20, hWnd, NULL, NULL, NULL);
					npw.age = CreateWindowA("static", to_string(p.age).c_str(), WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
						r.right - (90 * 3), r.bottom - cur_off, 80, 20, hWnd, NULL, NULL, NULL);
					npw.num = CreateWindowA("static", to_string(p.num).c_str(), WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
						r.right - (90 * 4), r.bottom - cur_off, 80, 20, hWnd, NULL, NULL, NULL);
					npw.otchestvo = CreateWindowA("static", p.fio.otchestvo.c_str(), WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
						r.right - (90 * 4 + 150), r.bottom - cur_off, 140, 20, hWnd, NULL, NULL, NULL);
					npw.name = CreateWindowA("static", p.fio.name.c_str(), WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
						r.right - (90 * 4 + 150 * 2), r.bottom - cur_off, 140, 20, hWnd, NULL, NULL, NULL);
					npw.surname = CreateWindowA("static", p.fio.surname.c_str(), WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
						r.right - (90 * 4 + 150 * 3), r.bottom - cur_off, 140, 20, hWnd, NULL, NULL, NULL);
					npw.team = CreateWindowA("static", p.team.c_str(), WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
						r.right - (90 * 4 + 150 * 4), r.bottom - cur_off, 140, 20, hWnd, NULL, NULL, NULL);
					npw.origin = CreateWindowA("static", p.origin.c_str(), WS_CHILD | WS_BORDER | WS_VISIBLE | SS_CENTER,
						r.right - (90 * 4 + 150 * 5), r.bottom - cur_off, 140, 20, hWnd, NULL, NULL, NULL);
				
					outputted_playerlines.push_back(npw);
				}
			}

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
