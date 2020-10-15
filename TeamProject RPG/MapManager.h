#pragma once

#include <Windows.h>
#include "Player.h"
#include "GameInfo.h"
//여기에 몬스터를 로드

class MapManager
{
private:
	string map[30][30] = {""};
	Pos playerPos;	//예시용 player pos

	//1번맵, 2번맵... 1번맵선택하면 gameinfo에서 1번맵에 대한 정보를 ini파일에서 불러와서
	//그 맵 파일에 맞는 몬스터를 new로 생성해서 해당 위치에 배치.
	//그럴려면
	//gameinfo include, monster include...
	//player...로드 
	//출력
	//Mapmanager에서 player.getPos 한 후에 그 정보를 map에 넣고 맵을 출력한 후에
	//한번더 playerPos를 참조해서 9칸 그림을 그린다.
public:
	void GoToXY(const int x,const int y);
	void PrintCharacter(Character* character);
	//void PrintCharacter(Monster monster);

	void CheckOutOfMap(); //이걸 호출 하기 전에 player.move를 먼저 실행한 후에
	//체크해서 만약 = 블록을 오바했다. 그러면 위치값 수정 후 맵 출력..?
};

enum MyEnum
{
	Player

};
