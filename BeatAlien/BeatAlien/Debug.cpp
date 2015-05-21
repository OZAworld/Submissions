/*
*	デバッグ用の関数
*
*	2015/05/01		Y.Ozawa
*/


#include <cstdio>
#include "include.h"

//デバッグ用のアラートを出力する
void DebugAlert(char *format, ...)
{
	va_list	data;
	char str[256];
	va_start(data, format);
	vsprintf_s(str, format, data);
	va_end(data);

	OutputDebugString(str);
	MessageBox(nullptr, str, "Error", MB_ICONSTOP);
}
//デバッグ用のログを出力する
void DebugLog(char *format, ...)
{
	va_list	data;
	char str[256];
	va_start(data, format);
	vsprintf_s(str, format, data);
	va_end(data);

	OutputDebugString(str);
	printf(str);
}
