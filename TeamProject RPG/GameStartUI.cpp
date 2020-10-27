#include "GameStartUI.h"

GameStartUI::GameStartUI()
{
	//게임타이틀읽기
	ReadFileString("title", "0", title, "GameInfo\\GameStartUI.ini");
	ReadFileString("title", "1", title, "GameInfo\\GameStartUI.ini");
	ReadFileString("title", "2", title, "GameInfo\\GameStartUI.ini");
	ReadFileString("title", "3", title, "GameInfo\\GameStartUI.ini");
	ReadFileString("title", "4", title, "GameInfo\\GameStartUI.ini");

	//메뉴창읽기
	ReadFileString("select", "0", select, "GameInfo\\GameStartUI.ini");
	ReadFileString("select", "1", select, "GameInfo\\GameStartUI.ini");
	ReadFileString("select", "2", select, "GameInfo\\GameStartUI.ini");
}

void GameStartUI::Show()
{
	string s;
	setlocale(LC_ALL, "ko_KR.UTF8");
	for (int i = 0; i < title.size(); i++)
	{
		string s = to_string(i);
		GoToXY(20, 5 + i);
		cout << title[s] << endl;
	}

	for (int i = 0; i < select.size(); i++)
	{
		string s = to_string(i);
		GoToXY(46, 12 + (i * 2));
		cout << select[s] << endl;
	}
	setlocale(LC_ALL, "");
}

int GameStartUI::Select()
{
	Show();
	GoToXY(42, currentChoice);
	cout << CHOICE;

	while (true)
	{
		if (_kbhit())					//키보드누르면
		{
			if (224 == _getch())		//방향키입력받기위해사용
			{
				switch (_getch())			//키입력받고
				{
				case 72:			//위로이동
					if (currentChoice - 2 < 12)
						break;

					GoToXY(42, currentChoice);
					cout << " ";
					currentChoice -= 2;
					GoToXY(42, currentChoice);
					cout << CHOICE;
					break;

				case 80:							//아래로 이동
					if (currentChoice + 2 > 16)
						break;

					GoToXY(42, currentChoice);
					cout << " ";
					currentChoice += 2;
					GoToXY(42, currentChoice);
					cout << CHOICE;
					break;
				}
			}
			else
				break;
		}
	}

	if (currentChoice == NEWGAME)		//새게임시작
		return 0;
	else if (currentChoice == CHARACTERSELECET)		//게임정보 불러오기
		return 1;
	else if (currentChoice == EXIT)		//게임나가기
		return 2;

	return -1;		//잘못된값
}

//사용한 맵변수들 소멸
GameStartUI::~GameStartUI()
{
	auto titleIterator = title.begin();
	while (titleIterator != title.end())
	{
		title.erase(titleIterator++);
	}

	auto selectIterator = select.begin();
	while (selectIterator != select.end())
	{
		select.erase(selectIterator++);
	}
}