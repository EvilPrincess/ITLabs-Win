#include "Lab.h"

BOOL Palindrom(std::string _Str)
{
	if (_Str == "" || _Str.length() == 1) return TRUE;
	if (_Str[0] != _Str.back()) return FALSE;
	return Palindrom(_Str.substr(1, _Str.length() - 2));
}
double S(unsigned int n)
{
	if (n == 1) return 0.5;
	return pow(n, 3) / (n + 1) + S(n - 1);
}

bool SpecialFunctionsForLabs::is_int(string str)
{
    char availables[]{ '-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    if (count(str.begin(), str.end(), '-') > 0 && str[0] != '-') return false;
    if (count(str.begin(), str.end(), '-') > 1) return false;

    for (char c : str) {
        if (find(begin(availables), end(availables), c) == end(availables)) return false;
    }

    return true;
}
bool SpecialFunctionsForLabs::is_float(string str)
{
    char availables[]{ '-', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    if (count(str.begin(), str.end(), '-') > 0 && str[0] != '-') return false;
    if (count(str.begin(), str.end(), '-') > 1) return false;

    if (count(str.begin(), str.end(), '.') > 1) return false;
    if (count(str.begin(), str.end(), '.') > 0 && (str[0] == '.' || str[0] == '-' && str[1] == '.' || str.back() == '.')) return false;

    for (char c : str) {
        if (find(begin(availables), end(availables), c) == end(availables)) return false;
    }

    return true;
}
bool SpecialFunctionsForLabs::is_natural(string str)
{
    char availables[]{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    if (!is_int(str) || stoi(str) < 1) return false;

    return true;
}
bool SpecialFunctionsForLabs::is_char(string str)
{
    return str.length() == 1;
}