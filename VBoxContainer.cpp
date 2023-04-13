#include "VBoxContainer.h"

void VBoxContainer::VBoxRegister()
{
	WNDCLASS wc = { 0 };

	wc.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = VBoxContainer::VBoxProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = VBOXCONT_WC;
	RegisterClass(&wc);
}

void VBoxContainer::VBoxUnregister()
{
	UnregisterClass(VBOXCONT_WC, NULL);
}

LRESULT CALLBACK VBoxContainer::VBoxProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{

			break;
		}
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
}