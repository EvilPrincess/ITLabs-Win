#include "main.h"

Display* display = { };
Display* Display::p_instance = nullptr;
HINSTANCE hMainInst = { };

STATIC *st11, *st12, *st21, *dir1, *dir2, *dir3;
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
	stp.alignh = aligns::center;
	stp.alignv = aligns::top;
	stp.bdDefCol = BUTTON_DEFAULT_BDC - 40;
	stp.textCol = V3(255, 95, 46);

	new STATIC(hWnd, "Лабораторная работа №6", V3(10, 10, 0), NULL, V3{1630, 35, 3}, stp);
	new STATIC(hWnd, "Задача №1", V3(10, 10 + 30 + 10, 0), NULL, V3{810, 35, 3}, stp);
	new STATIC(hWnd, "Задача №2", V3(r.right - 820, 10 + 30 + 10, 0), NULL, V3{810, 35, 3}, stp);

	stp.bdDefCol = STATIC_DEFAULT_BORDER;
	stp.textCol = STATIC_DEFAULT_TEXTCOL;
	st11 = new STATIC(hWnd, "Выберите файл...", V3{ 10, 10 + 70 + 10, 0 }, ST11, V3{400, 670, 3}, stp); stp.textCol = V3(203, 30, 30);
	st12 = new STATIC(hWnd, "Файл не выбран!", V3{ 10 + 400 + 10, 10 + 70 + 10, 0 }, ST12, V3{400, 670, 3}, stp); stp.textCol = STATIC_DEFAULT_TEXTCOL;
	st21 = new STATIC(hWnd, "Выберите файл...", V3{ r.right - 10 - 400 - 10 - 400, 10 + 70 + 10, 0 }, ST21, V3{ 810, 670, 3 }, stp); stp.textCol = V3(203, 30, 30);

	stp.bdDefCol = BUTTON_DEFAULT_BDC - 40;
	stp.textCol = STATIC_DEFAULT_TEXTCOL;
	stp.charHeight = 18;
	dir1 = new STATIC(hWnd, "", V3{10, r.bottom - 60 - 10 - 25, 0}, NULL, V3{400, 30, 3}, stp);
	dir2 = new STATIC(hWnd, "", V3{10 + 400 + 10, r.bottom - 60 - 10 - 25, 0}, NULL, V3{400, 30, 3}, stp);
	dir3 = new STATIC(hWnd, "", V3{10 + 400 + 10 + 400 + 10, r.bottom - 60 - 10 - 25, 0}, NULL, V3{810, 30, 3}, stp);

	bt11 = new BUTTON(hWnd, "Открыть", V3{10, r.bottom - 60, 0}, BT11, V3{400, 50, 3});
	bt12 = new BUTTON(hWnd, "Найти уникальные", V3{ 10 + 400 + 10, r.bottom - 60, 0 }, BT12, V3{ 400, 50, 3 }); bt12->Disable();
	bt21 = new BUTTON(hWnd, "Открыть", V3{ r.right - 10 - 400 - 10 - 400, r.bottom - 60, 0 }, BT21, V3{ 400, 50, 3 });
	bt22 = new BUTTON(hWnd, "Удолить до пробела", V3{ r.right - 10 - 400, r.bottom - 60, 0 }, BT22, V3{ 400, 50, 3 }); bt22->Disable();
}

void Display::OnResize(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

}

UINT FindLastSlash(string &_Str)
{
	for (int i = _Str.length()-1; i > 0; i--)
	{
		if (_Str[i] == '/') return i;
	}
}

void OnOpenPressed1()
{
	CHAR fileName[MAX_PATH] = "";	// эта штука содержит путь к файлу вместе с его именем
	CHAR titleName[MAX_PATH] = "";
	if (OpenDialog(NULL, fileName, titleName))
	{
		fill_n(buffer1, sizeof(buffer1), 0);
		ifstream file(fileName);
		file.read(buffer1, sizeof(buffer1));
		file.close();
		if (string(buffer1) == "")
		{
			MB("Пустой файл!", 1);
			return;
		}
		st11->SetAlignH(aligns::left);
		st11->SetText("Предпросмотр файла:\n\n" + string(buffer1));
		bt12->Enable();
		dir1->SetText(fileName);
	}
}
void OnOpenPressed2()
{
	CHAR fileName[MAX_PATH] = "";	// эта штука содержит путь к файлу вместе с его именем
	CHAR titleName[MAX_PATH] = "";
	if (OpenDialog(NULL, fileName, titleName))
	{
		fill_n(buffer2, sizeof(buffer2), 0);
		ifstream file(fileName);
		file.read(buffer2, sizeof(buffer2));
		file.close();
		if (string(buffer2) == "")
		{
			MB("Пустой файл!", 1);
			return;
		}
		st21->SetAlignH(aligns::left);
		st21->SetText("Предпросмотр файла:\n\n" + string(buffer2));
		bt22->Enable();
		dir3->SetText(fileName);
	}
}
void OnSolvePressed1()
{
	CHAR fileName[MAX_PATH] = "";	// эта штука содержит путь к файлу вместе с его именем
	CHAR titleName[MAX_PATH] = "";
	if (OpenDialog(NULL, fileName, titleName, 0))
	{
		// расчеты и вывод
		vector<char> uniq;
		string result;
		int toskip = string("Предпросмотр файла:\n\n").length();
		for (char c : st11->GetText())
		{
			if (toskip-- > 0) continue;
			if (find(uniq.begin(), uniq.end(), c) == uniq.end()) uniq.push_back(c);
		}
		st12->params.textCol = STATIC_DEFAULT_TEXTCOL;
		st12->SetAlignH(aligns::left);
		st12->SetText("Уникальные символы файла:\n\n" + (result = string(uniq.begin(), uniq.end())));
		// изменение файла
		ofstream file(fileName, ios_base::trunc);
		file << result << endl;
		file.close();
		dir2->SetText(fileName);
	}
}
void OnSolvePressed2()
{
	int toskip = string("Предпросмотр файла:\n\n").length();
	string result = "";
	for (char c : st21->GetText())
	{
		if (toskip-- > 0) continue;
		result += c;
	}
	result = string(find(result.begin(), result.end(), ' ')+1, result.end());
	st21->SetText("Предпросмотр файла:\n\n");
	st21->AddText(result);
	ofstream file(dir3->GetText(), ios_base::trunc);
	file << result << endl;
	file.close();
}
BOOL OpenDialog(HWND hwnd, LPSTR lpFileName, LPSTR lpTitleName, BOOL openOrSave)
{
	OPENFILENAMEA ofn;
	CHAR szFile[MAX_PATH] = "";
	// Инициализация структуры OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0";
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = lpTitleName;
	ofn.Flags = (openOrSave? OFN_FILEMUSTEXIST : 0) | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	// Вызов диалога выбора файла
	if (openOrSave)
	{
		if (GetOpenFileNameA(&ofn))
		{
			strncpy(lpFileName, szFile, strlen(szFile) + 1);
			return TRUE;
		}
		return FALSE;
	}
	else
	{
		if (GetSaveFileNameA(&ofn))
		{
			string str(szFile);
			if (str.substr(str.length()-4, 4) != string(".txt"))
				strcat_s(szFile, ".txt");
			strncpy(lpFileName, szFile, strlen(szFile) + 1);
			return TRUE;
		}
		return FALSE;
	}
}

void Display::CommandHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		// открыть номер 1
		case BT11: 
		{
			OnOpenPressed1();
			break;
		}
		// вычислить номер 1
		case BT12:
		{
			OnSolvePressed1();
			break;
		}
		// открыть номер 2
		case BT21: 
		{
			OnOpenPressed2();
			break;
		}
		// вычислить номер 2
		case BT22:
		{
			OnSolvePressed2();
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
		WS_MINIMIZEBOX | WS_VISIBLE, 10, 10, _Size.x, _Size.y, NULL, NULL, NULL, NULL);
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