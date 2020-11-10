#include "Player.h"

Player* Player::playerInstance = nullptr;

Player* Player::GetInstance()
{
	if (playerInstance == nullptr) 
	{
		srand((unsigned int)time(NULL));
		playerInstance = new Player();
	}

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

void Player::Init()
{
	Hp = MaxHp;

	walkCount = 0;
	isWalking = false;
	isAttack = false;
	isPickup = false;
	isSurvival = true;
	dir = RIGHT;

	playerStatsUI.PrintHp(Hp);
	playerStatsUI.PrintExp(exp);
	playerStatsUI.PrintLevel(level);

	for (auto setInitDontMoveDir : dontMoveDir)
		setInitDontMoveDir = false;
}

void Player::SetStats(const int& hpNum, const int& powerNum, const int& exp, const int& level, const string& weapon)
{
	Hp = hpNum;
	MaxHp = Hp;
	power = powerNum;
	this->exp = exp;
	this->level = level;
	int walkCount = 0;
	holdWeapon = weapon;
 }

void Player::SyncStatsUI()
{
	playerStatsUI.PrintHp(Hp);
	playerStatsUI.PrintExp(exp);
	playerStatsUI.PrintLevel(level);
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

const int Player::InputBehavior()
{
	isAttack = false;
	isPickup = false;

	if (GetAsyncKeyState(VK_UP) && 0x8000)		//위
	{
		return Move(UP);
	}
	if (GetAsyncKeyState(VK_DOWN) && 0x8000)	//아래
	{
		return Move(DOWN);
	}
	if (GetAsyncKeyState(VK_LEFT) && 0x8000)	//왼쪽
	{
		return Move(LEFT);
	}
	if (GetAsyncKeyState(VK_RIGHT) && 0x8000)	//오른쪽
	{
		return Move(RIGHT);
	}
	if (GetAsyncKeyState(VK_SPACE) && 0x8000)	//space 공격
	{
		return Attack();
	}
	if (GetAsyncKeyState(VK_CONTROL) && 0x8000)	//ctrl 줍기
	{
		return SetPickUpState();
	}

	isWalking = false;
	walkCount = 0;

	return NONE;
}

const int Player::Move(const int direct4)
{
	if (UP == direct4)			//위
	{
		if (dontMoveDir[0] == true)
			return NONE;
		pos.SetY(pos.GetY() - 1);

		isWalking = true;
		walkCount++;
		if (walkCount > 2)
			walkCount = 0;
	}
	else if (DOWN == direct4)	//아래
	{
		if (dontMoveDir[1] == true)
			return NONE;
		pos.SetY(pos.GetY() + 1);
		isWalking = true;
		walkCount++;
		if (walkCount > 2)
			walkCount = 0;
	}
	else if (LEFT == direct4)	//왼쪽
	{
		if (dontMoveDir[2] == true)
			return NONE;
		pos.SetX(pos.GetX() - 2);
		isWalking = true;
		dir = LEFT;
		walkCount++;
		if (walkCount > 2)
			walkCount = 0;
	}
	else if (RIGHT == direct4)	//오른쪽
	{
		if (dontMoveDir[3] == true)
			return NONE;
		pos.SetX(pos.GetX() + 2);
		isWalking = true;
		dir = RIGHT;
		walkCount++;
		if (walkCount > 2)
			walkCount = 0;
	}
	else
	{
		isWalking = false;
		walkCount = 0;
	}

	return MOVE;
}

const int Player::Attack()
{
	isAttack = true;
	return ATTACK;
}

const int Player::SetPickUpState()
{
	isPickup = true;
	return PICKUP;
}

const bool Player::PickUp(const int& itemNumber)
{
	if(inventory.IsFullInventory())
		return false;

	if (itemNumber == -1)
	{
		//아이템 박스 습득 시 아이템 사이즈에 따라 랜덤 아이템 드랍
		inventory.PushItem(rand() % RANDOM_ITEM_SIZE);
		return true;
	}
	else
	{
		inventory.PushItem(itemNumber);
		return true;
	}
	
}

void Player::UseItem(int itemNumber)
{
	int tempItem = inventory.GetItem((itemNumber-1));

	if (tempItem != -1)	//itemNumber이 가방에 존재하면
	{
		switch (tempItem)
		{
		case 0:	//hp포션
			Hp += 1;
			break;
		case 1:	//MP포션
			break;
		case 2:	//도끼
			holdWeapon = "axe";
			inventory.PushItem(3);
			break;
		case 3:	//칼
			holdWeapon = "sword";
			inventory.PushItem(2);
			break;
		}

		inventory.DeleteItem(itemNumber-1);
		inventory.OpenInventory();
	}

	//아이템 사용후 UI최신화
	playerStatsUI.PrintHp(Hp);
	playerStatsUI.PrintExp(exp);
	playerStatsUI.PrintLevel(level);
}

void Player::OpenInventory()
{
	inventory.OpenInventory();
}

void Player::CloseInventory()
{
	inventory.CloseInventory();
}

const int Player::GetInventoryItem(int itemIndex)
{
	return inventory.GetItem(itemIndex);
}

void Player::Die()
{
	isSurvival = false;

	//죽었을때 패널티
	SetMaxHp(MaxHp - 2);
	SetPower(power - 1);
	SetExp(-exp);
}

const string Player::GetHoldWeapon()
{
	return holdWeapon;
}

const int Player::GetIsWalking()
{
	return isWalking;
}

const int Player::GetIsAttacking()
{
	return isAttack;
}

const int Player::GetIsPickUp()
{
	return isPickup;
}

const bool Player::GetWalkCount()
{
	return walkCount;
}

const int Player::GetDir()
{
	return dir;
}

const int Player::GetLevel()
{
	return level;
}

const int Player::GetExp()
{
	return exp;
}

const string& Player::GetCurrentWeapon()
{
	return holdWeapon;
}

Inventory& Player::GetInventory()
{
	return inventory;
}

void Player::SetExp(const int exp)
{
	this->exp += exp;
	if (this->exp >= 100)
	{
		this->exp -= 100;
		level += 1;
		MaxHp += 1;
		power += 1;
		Hp = MaxHp;
	}
}

//플레이어가 적과 부딪혔을 때 실행할 함수
void Player::IsHit(const Pos& monsterPosition, const Pos& leftLimit, const Pos& rightLimit, int monsterPower)
{
	if (isInvincibility == false)
	{
		attackedDelaymanager.SetStartTime();
		attackedDelaymanager.SetDelayTime(INVINCIBILITY_TIME);
		isInvincibility = true;

		if ((this->GetPos().GetX() - monsterPosition.GetX() >= 0) && ((this->GetPos().GetX() + NUCKBACK_SIZE) < rightLimit.GetX()))
		{
			this->SetPos(this->GetPos().GetX() + NUCKBACK_SIZE, this->GetPos().GetY());		//오른쪽으로 밀려남,, 조건은 오른쪽경계체크
		}
		if ((this->GetPos().GetX() - monsterPosition.GetX() < 0) && ((this->GetPos().GetX() - NUCKBACK_SIZE) > leftLimit.GetX()))
		{
			this->SetPos(this->GetPos().GetX() - NUCKBACK_SIZE, this->GetPos().GetY());		//왼쪽으로 밀려남,, 조건은 왼쪽 경계체크
		}
		this->Hit(monsterPower);
		playerStatsUI.PrintHp(Hp);
	}
}

//무적시간측정
void Player::IsInvincibilityTimer()
{
	if (isInvincibility == false)
		return;

	//무적시간카운트
	if (isInvincibility == true)
	{
		if (attackedDelaymanager.CheckEndDelay() == false)
			return;

		isInvincibility = false;
	}
}

//현재상태반환
bool Player::GetIsInvincibility()
{
	return isInvincibility;
}
