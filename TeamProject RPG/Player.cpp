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
}

void Player::Move()
{

}

void Player::Die()
{

}
