#include "MapManager.h"

void MapManager::GoToXY(const int x, const int y)
{
	COORD pos = { (SHORT)x,(SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void MapManager::PrintCharacter(Character* character)
{
	GoToXY(character->GetPos().GetX() - 1, character->GetPos().GetY() + 3);

	if (1)		//���⼭ ĳ���Ͱ� ����Ű�°��� ���� �Ǻ��ϴ°� ã�Ƽ� �ְ�
	{
		//���⼭ .. ĳ���� ���..
	}


}

void MapManager::CheckOutOfMap()
{

}
