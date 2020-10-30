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

void UI::ReadFileString(const char* section, string tempKey, map<string, wstring>& test, const char* path)
{
	TCHAR loadData[1024];
	auto key = tempKey.c_str();		//string to const char*(LPCSTR)
	GetPrivateProfileString(section, key, "", loadData, 1024, path);
	string str = loadData;

	wstring wstr = Str2Wstr(str);

	test[tempKey] = wstr;
}

void UI::ReadFileString(const char* section, const char* key, string& test, const char* path)
{
	TCHAR loadData[1024];
	GetPrivateProfileString(section, key, "", loadData, 1024, path);
	test = loadData;
}

wstring UI::Str2Wstr(const string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}