#pragma once
#include "base.h"
#include "WndStruct.h"

#ifndef VBOXCONT_H
#define VBOXCONT_H
#define VBOXCONT_WC _T("VBoxContainer")
#endif

class VBoxContainer
{
private:
	static LRESULT CALLBACK VBoxProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OnCreate(HWND hWnd);
	HWND hWnd;
public:
	static void VBoxRegister();
	static void VBoxUnregister();
	static void Redraw(HWND hWnd);
};

