#include "Lib.h"

RECT GetLocalRect(HWND hWnd)
{
	RECT childr;
	GetWindowRect(hWnd, &childr);
	MapWindowPoints(HWND_DESKTOP, GetParent(hWnd), (LPPOINT)&childr, 2);
	return childr;
}
VOID GetLocalRect(HWND hWnd, LPRECT r)
{
	GetWindowRect(hWnd, r);
	MapWindowPoints(HWND_DESKTOP, GetParent(hWnd), (LPPOINT)r, 2);
}
WNDCLASS NewWindowClass(LPCWSTR Name, WNDPROC Procedure, HBRUSH BGColor, HCURSOR Cursor, HICON Icon) {
	WNDCLASS NWC = { };

	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}
void Register()
{
	WNDCLASS wc = { };
	RegisterClass(&(wc = NewWindowClass(EDIT_WC, Edit::EditProc, (HBRUSH)GetStockObject(HOLLOW_BRUSH))));
	RegisterClass(&(wc = NewWindowClass(BUTTON_WC, Button::ButtonProc, (HBRUSH)GetStockObject(HOLLOW_BRUSH))));
	RegisterClass(&(wc = NewWindowClass(STATIC_WC, Static::StaticProc, (HBRUSH)GetStockObject(HOLLOW_BRUSH))));
	RegisterClass(&(wc = NewWindowClass(VBOX_WC, NULL)));
	RegisterClass(&(wc = NewWindowClass(HBOX_WC, NULL)));
}
