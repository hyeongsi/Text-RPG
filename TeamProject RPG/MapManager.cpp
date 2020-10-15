#include "MapManager.h"

void MapManager::GoToXY(const int x, const int y)
{
	COORD pos = { (SHORT)x,(SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void MapManager::PrintCharacter(Character* character)
{
	GoToXY(character->GetPos().GetX() - 1, character->GetPos().GetY() + 3);

	if (1)		//여기서 캐릭터가 가르키는값이 뭔지 판별하는거 찾아서 넣고
	{
		//여기서 .. 캐릭터 출력..
	}


}

void MapManager::CheckOutOfMap()
{

}
