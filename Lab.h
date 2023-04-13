#pragma once

#include "base.h"
#include "Time.h"

#define max(a, b) (a >= b? a : b)
#define min(a, b) (a <= b? a : b)

using namespace std;

//		ЛАБА 4
//
BOOL Palindrom(string _Str);
double S(unsigned int n);

//		ЛАБА 5
//
struct TRAIN
{
	string NAZN;
	UINT NUMR;
	TS TIME;
};
struct FIO
{
	string surname, name, otchestvo;
} static const myFIO{"Фомин", "Никита", "Алексеевич"};
struct Player
{
	string origin, team;
	FIO fio;
	UINT num, age, height, weight;
};
struct trainwnd
{
	HWND NAZN;
	HWND NUMR;
	HWND TIME;
	HWND DelBtn;
	UINT onDelete;
	UINT y;
	void Delete();
	void move();
};
struct playerwnd
{
	HWND origin, team;
	HWND surname, name, otchestvo;
	HWND num, age, height, weight;
	HWND DelBtn;
	UINT onDelete;
	UINT y;
	RECT mr;
	void Delete();
	void move();
};

namespace SpecialFunctionsForLabs {
	bool is_int(string str);
	bool is_double(string str);
	bool is_char(string str);
	bool is_natural(string str);
	string dtos(double value, unsigned int absolutePresision = 2);
	double round(double value, unsigned int precision);

	template<typename T>
	T input(string _Message = "", string _DefaultErrorMessage = "Ошибка ввода! Повторите ввод: ")
	{
		cout << _Message;
		string input;
		getline(cin, input);

		if (is_same<T, unsigned int>::value) {
			while (!(is_int(input) && stoi(input) > 0)) {
				cout << _DefaultErrorMessage;
				getline(cin, input);
			}
			return stoi(input);
		}
		if (is_same<T, int>::value) {
			while (!is_int(input)) {
				cout << _DefaultErrorMessage;
				getline(cin, input);
			}
			return stoi(input);
		}
		else if (is_same<T, float>::value) {
			while (!is_double(input)) {
				cout << _DefaultErrorMessage;
				getline(cin, input);
			}
			return stof(input);  // для setlocale(LC_NUMERIC, "C")
		}
		else if (is_same<T, double>::value) {
			while (!is_double(input)) {
				cout << _DefaultErrorMessage;
				getline(cin, input);
			}
			return stod(input);  // для setlocale(LC_NUMERIC, "C")
		}
		else if (is_same<T, char>::value) {
			while (!is_char(input)) {
				cout << _DefaultErrorMessage;
				getline(cin, input);
			}
			return input[0];
		}

		return NULL;
	}
}