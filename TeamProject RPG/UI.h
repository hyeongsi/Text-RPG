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
	void GoToXY(SHORT x, SHORT y) const;
	void ReadFileString(const char* section, string key, map<string, string>& test, const char* path) const;
	void ReadFileString(const char* section, const char* key, string& test, const char* path) const;
public:


};

