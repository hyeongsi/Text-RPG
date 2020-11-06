#include "Oak.h"

vector<Oak*>* Oak::oak = nullptr;
Pos* Oak::itemPosition = new Pos();
int Oak::exp = 0;

//객체추가
void Oak::AddInstance()
{
	if (oak == nullptr)
		oak = new vector<Oak*>();

	oak->push_back(new Oak());		//oak객체 추가
}

//객체벡터반환
vector<Oak*>* Oak::GetInstance()
{
	return oak;
}

//동적할당해제하기
void Oak::ReleaseInstance()
{
	if (oak == nullptr)
		return;

	for (int i = 0; i < oak->size(); i++)
		delete (*oak)[i];

	oak->clear();

	delete oak;
	oak = nullptr;
}

//각 오크마다 체력과 공격력과 스피드 설정하기
void Oak::SetStats(int hp, int power, int speed, int exp)
{
	Monster::MonsterSetStats(hp, power, speed);
	Oak::exp = exp;
}

//속도에 따라 움직이기,,, 플레이어 위치방향으로 움직임
void Oak::Move(const int& playerXPosition, const int& playerYPosition)
{
	if (this->isMove)
	{
		moveDelaymanager.SetStartTime();
		moveDelaymanager.SetDelayTime(this->speed);
	}
	this->isMove = false;

	if (!moveDelaymanager.CheckEndDelay())
		return;

	//간단히 설명하자면 캐릭터가있는 위치와 오크위치를 기준으로 오크이동방향을 결정
	this->SetPos((this->GetPos().GetX() - playerXPosition > 0) ? this->GetPos().GetX() - 1 : this->GetPos().GetX() + 1, (this->GetPos().GetY() - playerYPosition > 0) ? this->GetPos().GetY() - 1 : this->GetPos().GetY() + 1);
	this->isMove = true;
}

void Oak::Die()
{
	//오크체력없으면 삭제
	for (auto oakHP = oak->begin(); oakHP != oak->end();)
	{
		if ((*oakHP)->Hp <= 0)		
		{
			itemPosition->SetX(((*oakHP)->GetPos().GetX() % 2 == 0) ? (*oakHP)->GetPos().GetX() + 1 : (*oakHP)->GetPos().GetX());
			itemPosition->SetY((*oakHP)->GetPos().GetY());
			delete (*oakHP);		//할당받은거 반납
			oak->erase(oakHP);	//벡터에서 삭제
			return;
		}
		else
			oakHP++;
	}
}

//오쿠이 맞았을 때 실행할 함수
void Oak::isHit(const int& playerXPosition, const int& playerYPosition, const int& playerDirection, const int& playerPower)
{
	//타점
	int attackXPosition = 0;
	int attackYPosition = 0;

	//각 오크들의 위치
	int oakXPosition = this->GetPos().GetX();
	int oakYPosition = this->GetPos().GetY();

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

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y >= -2; y--)
		{
			if ((attackXPosition == oakXPosition + y) && (attackYPosition == oakYPosition - 2 + x))
			{
				isAttacked = true;
			}
		}
	}

	if (isAttacked == true && isInvincibility == false)
	{
		if (playerDirection == RIGHT)
			this->SetPos(oakXPosition + bounceSize, oakYPosition);

		else if (playerDirection == LEFT)
			this->SetPos(oakXPosition - bounceSize, oakYPosition);
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
