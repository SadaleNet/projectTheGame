///@brief misc utils macros/functions
#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <string>

//convert imagePath to WCHAR* , source: https://stackoverflow.com/questions/8032080/how-to-convert-char-to-wchar-t/8032109#8032109
//I don't bother using std::setlocale(); as it is unlikely that we will use unicode path.
#define CHAR_TO_CONST_WCHAR_ARRAY(_src, _dest) \
	std::wstring wstringDummy( strlen(_src), 0 );\
	std::mbstowcs( &wstringDummy[0], _src, strlen(_src) );\
	const WCHAR* _dest = wstringDummy.data()

#define MIN(a, b) ( a<b? a:b )
#define MAX(a, b) ( a>b? a:b )