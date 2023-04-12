#pragma once

#include "base.h"

struct wndstruct
{
	std::string identifier;
	std::string text;
	DWORD dwStyle;
	int x;
	int y;
	int width;
	int height;
	HMENU hMenu;
	HINSTANCE hInstance;
	LPVOID lpParam;
};