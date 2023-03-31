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

	if (str.length() < 1) return false;
	if (str.length() > 9) return false;

	if (count(str.begin(), str.end(), '-') > 0 && str[0] != '-') return false;
	if (count(str.begin(), str.end(), '-') > 1) return false;

	for (char c : str) {
		if (find(begin(availables), end(availables), c) == end(availables)) return false;
	}

	return true;
}
bool SpecialFunctionsForLabs::is_double(string str)
{
	char availables[]{ '-', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	if (str.length() < 1) return false;

	if (count(str.begin(), str.end(), '-') > 0 && str[0] != '-') return false;
	if (count(str.begin(), str.end(), '-') > 1) return false;

	if (count(str.begin(), str.end(), '.') > 1) return false;
	if (count(str.begin(), str.end(), '.') > 0 && (str[0] == '.' || str[0] == '-' && str[1] == '.' || str.back() == '.')) return false;

	if (str.substr(0, str.find('.')).length() > 9 || str.substr(str.find('.'), str.length() - 1).length() > 15);

	for (char c : str) {
		if (find(begin(availables), end(availables), c) == end(availables)) return false;
	}

	return true;
}
bool SpecialFunctionsForLabs::is_natural(string str)
{
	return (is_int(str) && stoi(str) > 0);
}
bool SpecialFunctionsForLabs::is_char(string str)
{
	return (str.length() == 1);
}
double SpecialFunctionsForLabs::round(double value, unsigned int precision)
{
    double k = pow(10, precision);
    return (int)(value * k + 0.5) / k;
}
string SpecialFunctionsForLabs::dtos(double value, unsigned int absolutePresision)
{
    string str = to_string(value);
    unsigned int precision = min(absolutePresision + str.find('.'), str.length());
    for (int i = precision; i > 1; i--)
    {
        if (str[i] == '0') precision--;
        else break;
    }
    return str.substr(0, precision+1);
}