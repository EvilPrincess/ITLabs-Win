#pragma once

#include "base.h"
using namespace std;

BOOL Palindrom(string _Str);
double S(unsigned int n);

namespace SpecialFunctionsForLabs {
    bool is_int(string str);
    bool is_float(string str);
    bool is_char(string str);
    bool is_natural(string str);

    template<typename T>
    T input(string _Message = "", string _DefaultErrorMessage = "Ошибка ввода! Повторите ввод: ")
    {
        cout << _Message;
        string input;
        cin >> input;

        if (is_same<T, unsigned int>::value) {
            while (!(is_int(input) && stoi(input) > 0)) {
                cout << _DefaultErrorMessage;
                cin >> input;
            }
            cin.ignore(1);
            return stoi(input);
        }
        if (is_same<T, int>::value) {
            while (!is_int(input)) {
                cout << _DefaultErrorMessage;
                cin >> input;
            }
            cin.ignore(1);
            return stoi(input);
        }
        else if (is_same<T, float>::value) {
            while (!is_float(input)) {
                cout << _DefaultErrorMessage;
                cin >> input;
            }
            cin.ignore(1);
            return stof(input);  // для setlocale(LC_NUMERIC, "C")
        }
        else if (is_same<T, double>::value) {
            while (!is_float(input)) {
                cout << _DefaultErrorMessage;
                cin >> input;
            }
            cin.ignore(1);
            return stod(input);  // для setlocale(LC_NUMERIC, "C")
        }
        else if (is_same<T, char>::value) {
            while (!is_char(input)) {
                cout << _DefaultErrorMessage;
                cin >> input;
            }
            cin.ignore(1);
            return input[0];
        }

        return NULL;
    }
}