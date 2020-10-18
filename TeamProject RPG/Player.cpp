#include "Player.h"

Player* Player::playerInstance = nullptr;

Player* Player::GetInstance()
{
	if (playerInstance == nullptr)
		playerInstance = new Player();

	return playerInstance;
}

void Player::ReleaseInstance()
{
	if (playerInstance)
	{
		delete playerInstance;
		playerInstance = nullptr;
	}
}

void Player::SetStats(int hpNum, int powerNum)
{
	Hp = hpNum;
	power = powerNum;
	int walkCount = 0;
}

void Player::Move()
{
	if (GetAsyncKeyState(VK_UP) && 0x8000)			//위
	{
		pos.SetY(pos.GetY() - 1);
		isWalking = true;
		walkCount++;
		if (walkCount > 2)
			walkCount = 0;
	}
	else if (GetAsyncKeyState(VK_DOWN) && 0x8000)	//아래
	{
		pos.SetY(pos.GetY() + 1);
		isWalking = true;
		walkCount++;
		if (walkCount > 2)
			walkCount = 0;
	}
	else if (GetAsyncKeyState(VK_LEFT) && 0x8000)	//왼쪽
	{
		pos.SetX(pos.GetX() - 2);
		isWalking = true;
		dir = true;
		walkCount++;
		if (walkCount > 2)
			walkCount = 0;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && 0x8000)	//오른쪽
	{
		pos.SetX(pos.GetX() + 2);
		isWalking = true;
		dir = false;
		walkCount++;
		if (walkCount > 2)
			walkCount = 0;
	}
	else
	{
		isWalking = false;
		walkCount = 0;
	}
}

void Player::Die()
{

}

const int Player::GetIsWalking()
{
	return isWalking;
}

const bool Player::GetWalkCount()
{
	return walkCount;
}

const bool Player::GetDir()
{
	return dir;
}
