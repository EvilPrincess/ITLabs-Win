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