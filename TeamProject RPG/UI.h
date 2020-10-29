
#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <map>
#include <conio.h>

using namespace std;


class UI
{
protected:
	const string CHOICE = "☞";

protected:
	void GoToXY(SHORT x, SHORT y);
	void ReadFileString(const char* section, string key, map<string, string>& test, const char* path);
	void ReadFileString(const char* section, const char* key, string& test, const char* path);

public:


};

