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

void Player::SetStats(const int hpNum, const int powerNum)
{
	Hp = hpNum;
	power = powerNum;
	int walkCount = 0;
}

void Player::CheckDontMoveDir(Pos leftUp, Pos rightDown)
{
	//상 체크
	if (pos.GetY()-1 <= leftUp.GetY())
		dontMoveDir[0] = true;
	else
		dontMoveDir[0] = false;

	//하 체크
	if (pos.GetY()+1 >= rightDown.GetY())
		dontMoveDir[1] = true;
	else
		dontMoveDir[1] = false;

	//좌 체크
	if (pos.GetX()-2 <= leftUp.GetX())
		dontMoveDir[2] = true;
	else
		dontMoveDir[2] = false;

	//우 체크
	if (pos.GetX()+2 >= rightDown.GetX())
		dontMoveDir[3] = true;
	else
		dontMoveDir[3] = false;
}

void Player::Move()
{
	if (GetAsyncKeyState(VK_UP) && 0x8000)			//위
	{
		if (dontMoveDir[0] == true)
			return;
		pos.SetY(pos.GetY() - 1);

		isWalking = true;
		walkCount++;
		if (walkCount > 2)
			walkCount = 0;
	}
	else if (GetAsyncKeyState(VK_DOWN) && 0x8000)	//아래
	{
		if (dontMoveDir[1] == true)
			return;
		pos.SetY(pos.GetY() + 1);
		isWalking = true;
		walkCount++;
		if (walkCount > 2)
			walkCount = 0;
	}
	else if (GetAsyncKeyState(VK_LEFT) && 0x8000)	//왼쪽
	{
		if (dontMoveDir[2] == true)
			return;
		pos.SetX(pos.GetX() - 2);
		isWalking = true;
		dir = true;
		walkCount++;
		if (walkCount > 2)
			walkCount = 0;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && 0x8000)	//오른쪽
	{
		if (dontMoveDir[3] == true)
			return;
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

void Player::Attack()
{
	if (GetAsyncKeyState(VK_SPACE) && 0x8000)			//space 공격
	{
		isAttack = true;
	}else
		isAttack = false;
}

void Player::PickItem()
{
	if (GetAsyncKeyState(VK_CONTROL) && 0x8000)			//ctrl 줍기
	{
		isPickup = true;
	}
	else
		isPickup = false;
}

void Player::Die()
{

}

const string Player::GetHoldWeapon()
{
	return holdWeapon;
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
