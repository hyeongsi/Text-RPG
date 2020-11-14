#include "Monster.h"
#include "Slime.h"
#include "Oak.h"
#include "Tank.h"

vector<Monster*>* Monster::monster = nullptr;
list<Pos>* Monster::itemPosition = new list<Pos>();
list<int>* Monster::deathMonster = new list<int>();

void Monster::Init()
{
	Monster::itemPosition = new list<Pos>();
	Monster::deathMonster = new list<int>();
}

//각 자식몬스터에서 호출
void Monster::AddInstance()
{
	if (monster == nullptr)
		monster = new vector<Monster*>();
}

//모든몬스터 삭제 + 할당받은 포인터들 반환
void Monster::ReleaseInstance()
{
	if (monster == nullptr)
		return;
	
	for (int i = 0; i < monster->size(); i++)
		delete (*monster)[i];

	monster->clear();

	delete monster;
	monster = nullptr;

	delete itemPosition;
	delete deathMonster;
}

//몬스터반환
vector<Monster*>* Monster::GetInstance()
{
	return monster;
}

//몬스터체력없으면 삭제
void Monster::Die()
{
	//죽은몬스터 기록하고 (나중에 exp랑 아이템드랍확률에 사용하고 지워버림)
	if (typeid(*this) == typeid(Slime))
		deathMonster->emplace_back(MonsterSpace::SLIME);
	if (typeid(*this) == typeid(Oak))
		deathMonster->emplace_back(MonsterSpace::OAK);
	if (typeid(*this) == typeid(Tank))
		deathMonster->emplace_back(MonsterSpace::TANK);

	//아이템확률에 따라 죽은놈의 좌표 저장(죽은놈좌표 = 아이템박스좌표),, 좌표저장을 안하면 아이템박스안생김 지금은 100%로 고정
	//srand((unsigned int)rand());
	//if (rand() % this->itemDropPercentage == 0)
		itemPosition->emplace_back(Pos((this->GetPos().GetX() % 2 == 0) ? this->GetPos().GetX() + 1 : this->GetPos().GetX(), this->GetPos().GetY()));

	int tempIndex = -1;
	int deathMonsterIndex = 0;
	//죽은놈의 인덱스구하기.. this값을 이용해서 vector에서 삭제하고싶은데 방법을 모르겠음
	//this값으로 삭제하면 굳이 반복문안써도 되는데
	//list는 remove(*this)이런형식으로 하면될것같은데 vector는 remove가 없어서 인덱스값을 찾아서 삭제하는형식으로만듦
	for (auto monsterHP : *monster)
	{
		tempIndex++;
		if (monsterHP->GetHp() <= 0)
		{
			if (this == monsterHP)
			{
				deathMonsterIndex = tempIndex;
				break;
			}
		}
	}

	delete (this);
	monster->erase(monster->begin() + deathMonsterIndex);
}

//몬스터 스텟설정
void Monster::SetStats(int hp, int power, int speed, int itemDropPercentage)
{
	this->Hp = hp;
	this->power = power;
	this->speed = speed;
	this->itemDropPercentage = itemDropPercentage;
}

//몬스터 스텟외 정보들 설정
void Monster::Setting(const int& invincibilityTime, const int& bounceSize)
{
	this->invincibilityTime = invincibilityTime;
	this->bounceSize = bounceSize;
}

//몬스터 움직임
void Monster::Move(const Pos& position)
{
	//플레이어 위치값 받기
	int playerXPosition = position.GetX();
	int playerYPosition = position.GetY();

	if (this->isMove)
	{
		moveDelaymanager.SetStartTime();
		moveDelaymanager.SetDelayTime(this->speed);
	}
	this->isMove = false;

	if (!moveDelaymanager.CheckEndDelay())
		return;

	//간단히 설명하자면 캐릭터가있는 위치와 슬라임위치를 기준으로 슬라임이동방향을 결정
	this->SetPos((this->GetPos().GetX()-playerXPosition>0) ? this->GetPos().GetX() - 1 : this->GetPos().GetX() + 1, (this->GetPos().GetY()- playerYPosition > 0) ? this->GetPos().GetY() - 1 : this->GetPos().GetY() + 1);
	this->isMove = true;
}

//몬스터 기본공격 피격처리
void Monster::IsHit(const Pos& position, const int& playerDirection, const int& playerPower, const bool isAttack, const bool isNotPlayer)
{
	if(isAttack == true)
		isAttacked = true;

	//플레이어 위치값 받기
	int playerXPosition = position.GetX();
	int playerYPosition = position.GetY();

	//타점
	int attackXPosition = 0;
	int attackYPosition = 0;

	//각 슬라임들의 위치
	int slimeXPosition = this->GetPos().GetX();
	int slimeYPosition = this->GetPos().GetY();

	if (isNotPlayer == false)
	{
		//플레이어보는방향에 따라서 공격위치설정
		if (playerDirection == RIGHT)
		{
			attackXPosition = playerXPosition + 3;
			attackYPosition = playerYPosition - 1;
		}
		else if (playerDirection == LEFT)
		{
			attackXPosition = playerXPosition - 5;
			attackYPosition = playerYPosition - 1;
		}
	}
	else
	{
		attackXPosition = playerXPosition;
		attackYPosition = playerYPosition;
	}

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y >= -2; y--)
		{
			if ((attackXPosition == slimeXPosition + y) && (attackYPosition == slimeYPosition - 2 + x))
			{
				isAttacked = true;
			}
		}
	}

	if (isAttacked == true && isInvincibility == false)
	{
		if (this->GetHp() - playerPower > 0)		//죽을때 죽은자리에서 아이템생성되게하기위함
		{
			if (playerDirection == RIGHT)
				this->SetPos(slimeXPosition + bounceSize, slimeYPosition);

			else if (playerDirection == LEFT)
				this->SetPos(slimeXPosition - bounceSize, slimeYPosition);
		}

		attackDelaymanager.SetStartTime();
		attackDelaymanager.SetDelayTime(invincibilityTime);
		isInvincibility = true;
		this->Hit(playerPower);
	}
	
	if (isInvincibility == true)
	{
		if (attackDelaymanager.CheckEndDelay() == false)
			return;

		isAttacked = false;
		isInvincibility = false;
	}
}

//몬스터 스킬 피격처리
void Monster::EarthquakeSkillHit(const Pos& position, const int& playerPower)
{
	//플레이어 위치값 받기
	int playerXPosition = position.GetX();
	int playerYPosition = position.GetY();

	//각 슬라임들의 위치
	int slimeXPosition = this->GetPos().GetX();
	int slimeYPosition = this->GetPos().GetY();

	//플레이어위치에 따라 슬라임이 스킬맞고 튕겨나가는 방향을 결정
	if (playerXPosition - slimeXPosition < 0)
		this->SetPos(slimeXPosition + bounceSize, slimeYPosition);
	else if (playerXPosition - slimeXPosition >= 0)
		this->SetPos(slimeXPosition - bounceSize, slimeYPosition);

	//스킬쓰면 무조건 맞아야하니까 그냥 Hit호출
	this->Hit(playerPower);
}

list<Pos>* Monster::GetItemPosition()
{
	return itemPosition;
}

//죽은몬스터번호 리턴
int Monster::GetDeathMonster()
{
	int tempMonsterNumber = deathMonster->front();
	deathMonster->pop_front();

	return tempMonsterNumber;
}