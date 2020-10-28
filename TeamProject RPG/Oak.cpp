#include "Oak.h"

vector<Oak*>* Oak::oak = nullptr;
Pos* Oak::itemPosition = new Pos();

//객체추가
void Oak::AddInstance()
{
	if (oak == nullptr)
		oak = new vector<Oak*>();

	oak->push_back(new Oak());		//slime객체 추가
}

//객체벡터반환
vector<Oak*>* Oak::GetInstance()
{
	return oak;
}

//동적할당해제하기
void Oak::ReleaseInstance()
{
	//동적할당해제하기
}

//각 오크마다 체력과 공격력과 스피드 설정하기
void Oak::SetStats(int hp, int power, int speed)
{
	this->Hp = hp;
	this->power = power;
	this->speed = speed;
}

//속도에 따라 움직이기,,, 플레이어 위치방향으로 움직임
void Oak::Move()
{
	int playerXPosition = player->GetPos().GetX();
	int playerYPosition = player->GetPos().GetY();

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

//이름 isDie변경생각.. 아유는 vector의 특정항목을 없앨라면 iterator를 사용해야하는데.. 그럴라면 자동적으로
//처음부터 끝까지 반복하니까.. 죽은놈객체의값으로 삭제할방법이 없는것같아서.. 이것도찾아보기
void Oak::Die()
{
	//오크체력없으면 삭제
	for (auto oakHP = oak->begin(); oakHP != oak->end(); oakHP++)
	{
		if ((*oakHP)->Hp <= 0 && oakHP == --oak->end())		//벡터의 마지막에 있는놈은 특별대우.. 안하면 에러남 이유찾기
		{
			itemPosition->SetX((*oakHP)->GetPos().GetX());
			itemPosition->SetY((*oakHP)->GetPos().GetY());
			oak->pop_back();
			return;
		}
		else if ((*oakHP)->Hp <= 0)
		{
			itemPosition->SetX((*oakHP)->GetPos().GetX());
			itemPosition->SetY((*oakHP)->GetPos().GetY());
			oakHP = oak->erase(oakHP);
		}
	}
}

//오쿠이 맞았을 때 실행할 함수
void Oak::isHit(int playerXPosition, int playerYPosition)
{
	//타점
	int attackXPosition = 0;
	int attackYPosition = 0;

	//각 오크들의 위치
	int oakXPosition = this->GetPos().GetX();
	int oakYPosition = this->GetPos().GetY();

	//플레이어보는방향에 따라서 공격위치설정
	if (player->GetDir() == RIGHT)
	{
		attackXPosition = playerXPosition + 3;
		attackYPosition = playerYPosition - 1;
	}
	else if (player->GetDir() == LEFT)
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

	//getX setX안되는이유
	if (isAttacked == true && isInvincibility == false)
	{
		if (player->GetDir() == RIGHT)
			this->SetPos(oakXPosition + rename, oakYPosition);

		else if (player->GetDir() == LEFT)
			this->SetPos(oakXPosition - rename, oakYPosition);
		attackDelaymanager.SetStartTime();
		attackDelaymanager.SetDelayTime(invincibilityTime);
		isInvincibility = true;
		this->Hit(player->GetPower());		//Hit()를 밖에다 뺄지는 고민해봐야할듯
	}

	if (isInvincibility == true)
	{
		if (attackDelaymanager.CheckEndDelay() == false)
			return;

		isAttacked = false;
		isInvincibility = false;
	}
}
