/*
*	�f�o�b�O�p�̊֐�
*
*	2015/05/01		Y.Ozawa
*/


#include <cstdio>
#include "include.h"

//�f�o�b�O�p�̃A���[�g���o�͂���
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
//�f�o�b�O�p�̃��O���o�͂���
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
