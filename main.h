#pragma once

#include "resources.h"
#include "Lib.h"

#define DISPLAY_WC L"Display Window"
#define REFRESH_IDT 1
#define REFRESH_RATE 1000 / 144

#define BUT1 0
#define BUT2 1
#define BUT3 2

//#ifndef REFRESH_RATE
//HDC hDCScreen = GetDC(NULL);
//const int frq = GetDeviceCaps(hDCScreen, VREFRESH);
//ReleaseDC(NULL, hDCScreen);
//#define REFRESH_RATE frq
//#endif

class Display
{
private:
	static Display* p_instance;
	HWND wnd;

	Display();
	HWND GenWnd();
	
	static void CommandHandler(HWND hWnd, WPARAM wParam, LPARAM lParam);
	static void TimerManager(HWND hWnd, WPARAM wParam, LPARAM lParam);
	static void OnCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
	static void OnResize(HWND hWnd, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI DisplayProc(HWND hWnd, 
		UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void DisplayRegister();
	static void DisplayUnregister();
	static void Refresh(HWND hWnd);
public:
	HWND GetWnd();
	HWND SetWnd(HWND hWnd);

	static Display* GetInstance();
protected:

};

void MB(string _Msg, BOOL _IsWarning = 0);