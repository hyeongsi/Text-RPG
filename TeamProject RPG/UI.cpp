#include "UI.h"

void UI::GoToXY(SHORT x, SHORT y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void UI::ReadFileString(const char* section, string tempKey, map<string, string>& test, const char* path)
{
	TCHAR loadData[1024];
	auto key = tempKey.c_str();		//string to const char*(LPCSTR)
	GetPrivateProfileString(section, key, "", loadData, 1024, path);
	test[tempKey] = loadData;
}

void UI::ReadFileString(const char* section, const char* key, string& test, const char* path)
{
	TCHAR loadData[1024];
	GetPrivateProfileString(section, key, "", loadData, 1024, path);
	test = loadData;
}
