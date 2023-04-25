#pragma once

#include "resources.h"
#include "Lib.h"

#define DISPLAY_WC L"Display Window"
#define REFRESH_IDT 1
#define REFRESH_RATE 1000 / 144

// лаба 6 - »ƒс окон
#define ST11 11
#define ST12 12
#define ST21 21
#define ST22 22
#define BT11 111
#define BT12 112
#define BT21 121
#define BT22 122

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

	Display(const V3 _Size = V3{ 400, 300, 0 });
	HWND GenWnd(const V3 _Size = V3{400, 300, 0});
	
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

	static Display* GetInstance(const V3 _Size = V3{ 400, 300, 0 });
protected:

};

void MB(string _Msg, BOOL _IsWarning = 0);