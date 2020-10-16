#include "MapManager.h"

void MapManager::GoToXY(const int x, const int y)
{
	COORD pos = { (SHORT)x,(SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void MapManager::PrintCharacter(Character* character)
{
	Player* player = dynamic_cast<Player*>(character);

	if (player != NULL)	//Player 형으로 잘 캐스팅 된 경우
	{
		player->GetShape();
	}

	//기준점 좌표로 부터 왼쪽 상단으로 이동해 이미지를[3][3] 출력한다.
	GoToXY(character->GetPos().GetX() - 1, character->GetPos().GetY() + 3);

	


}

void MapManager::CheckOutOfMap()
{

}
