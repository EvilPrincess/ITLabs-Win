#pragma once

#define vRGB(v) RGB(v.x, v.y, v.z)

enum states { inactive, hovered, pressed, enabled, disabled, valid, invalid };
enum class haligns { left, center, right };
enum class valigns { top, center, bottom };

//#define LIGHT_THEME

#ifndef LIGHT_THEME
#define MAIN_BK_COL V3(30, 30, 30)
#else
#define MAIN_BK_COL V3(230, 230, 230)
#endif

#define EDIT_WC L"MyCustomEditControl"
#define BUTTON_WC L"MyCustomButtonControl"
#define STATIC_WC L"MyCustomStaticControl"
#define VBOX_WC L"MyCustomVBoxControl"
#define HBOX_WC L"MyCustomHBoxControl"

#include "Vector2.h"
#include "Vector3.h"
#include "Transform.h"
#include "Control.h"
#include "Edit.h"
#include "Button.h"
#include "Static.h"

RECT GetLocalRect(HWND hWnd);
VOID GetLocalRect(HWND hWnd, LPRECT r);
WNDCLASS NewWindowClass(
	LPCWSTR Name,
	WNDPROC Procedure,
	HBRUSH BGColor = (HBRUSH)COLOR_WINDOW,
	HCURSOR Cursor = LoadCursor(NULL, IDC_ARROW),
	HICON Icon = LoadIcon(NULL, IDI_QUESTION)
);
void Register();