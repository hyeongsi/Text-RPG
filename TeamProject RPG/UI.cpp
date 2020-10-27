#include "UI.h"

void UI::GoToXY(SHORT x, SHORT y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void UI::ReadFileString(const char* section, const char* key, map<string, string>& test, const char* path)
{
	TCHAR loadData[1024];
	GetPrivateProfileString(section, key, "", loadData, 1024, path);
	test[key] = loadData;
}

void UI::ReadFileString(const char* section, const char* key, string& test, const char* path)
{
	TCHAR loadData[1024];
	GetPrivateProfileString(section, key, "", loadData, 1024, path);
	test = loadData;
}
