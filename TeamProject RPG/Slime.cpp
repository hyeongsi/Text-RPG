
#include "Slime.h"

vector<Slime*>* Slime::slime = nullptr;

//객체추가
void Slime::AddInstance()
{
	if (slime == nullptr)
		slime = new vector<Slime*>();
	slime->push_back(new Slime());		//slime객체 추가
}

//객체벡터반환
vector<Slime*>* Slime::GetInstance()
{
	return slime;
}

//동적할당해제하기
void Slime::ReleaseInstance()
{
	//동적할당해제하기
}

//각 슬라임마다 체력과 공격력과 스피드 설정하기
void Slime::SetStats(int hp, int power, int speed)
{
	this->Hp = hp;
	this->power = power;
	this->speed = speed;
}

//속도에 따라 움직이기,,, 플레이어 위치방향으로 움직임
void Slime::Move(int index)
{
	int playerPosX = player->GetPos().GetX();
	int playerPosY = player->GetPos().GetY();

	if ((*slime)[index]->isMove)
	{
		moveDelaymanager.SetStartTime();
		moveDelaymanager.SetDelayTime((*slime)[index]->speed);
	}
	(*slime)[index]->isMove = false;

	if (!moveDelaymanager.CheckEndDelay())
		return;

	//간단히 설명하자면 캐릭터가있는 위치와 슬라임위치를 기준으로 슬라임이동방향을 결정
	(*slime)[index]->SetPos(((*slime)[index]->GetPos().GetX()-playerPosX>0) ? (*slime)[index]->GetPos().GetX() - 1 : (*slime)[index]->GetPos().GetX() + 1, ((*slime)[index]->GetPos().GetY()- playerPosY > 0) ? (*slime)[index]->GetPos().GetY() - 1 : (*slime)[index]->GetPos().GetY() + 1);
	(*slime)[index]->isMove = true;
}

void Slime::Move()
{
}

//이름 isDie변경생각.. 아유는 vector의 특정항목을 없앨라면 iterator를 사용해야하는데.. 그럴라면 자동적으로
//처음부터 끝까지 반복하니까.. 죽은놈객체의값으로 삭제할방법이 없는것같아서.. 이것도찾아보기
void Slime::Die()
{
	//슬라임체력없으면 삭제
	for (auto slimeHP = slime->begin(); slimeHP != slime->end(); slimeHP++)
	{
		if ((*slimeHP)->Hp <= 0 && slimeHP == --slime->end())		//벡터의 마지막에 있는놈은 특별대우.. 안하면 에러남 이유찾기
		{
			slime->pop_back();
			return;
		}
		else if((*slimeHP)->Hp <= 0)
			slimeHP = slime->erase(slimeHP);
	}
}

//슬라임이 맞았을 때 실행할 함수
void Slime::isHit(int index)
{
	//타점
	int weaponXPosition = 0;
	int weaponYPosition = 0;

	//각 슬라임들의 위치
	int slimeXPosition = (*slime)[index]->GetPos().GetX();
	int slimeYPosition = (*slime)[index]->GetPos().GetY();

	if (player->GetDir() == RIGHT)
	{
		weaponXPosition = player->GetPos().GetX() + 3;
		weaponYPosition = player->GetPos().GetY() - 1;
	}
	else if (player->GetDir() == LEFT)
	{
		weaponXPosition = player->GetPos().GetX() - 5;
		weaponYPosition = player->GetPos().GetY() - 1;
	}

	//여기 단순하게 만들기 생각해보기
	for (int x = 0; x < 3; x++)
	{
		if (player->GetIsAttacking() && (weaponXPosition == slimeXPosition - 2) && (weaponYPosition == slimeYPosition - 2 + x))
		{
			isAttacked = true;
		}
		else if (player->GetIsAttacking() && (weaponXPosition == slimeXPosition - 1) && (weaponYPosition == slimeYPosition - 2 + x))
		{
			isAttacked = true;
		}
		else if (player->GetIsAttacking() && (weaponXPosition == slimeXPosition) && (weaponYPosition == slimeYPosition - 2 + x))
		{
			isAttacked = true;
		}
	}
	//getX setX안되는이유
	if (isAttacked == true && isInvincibility == false)
	{
		if (player->GetDir() == RIGHT)
			(*slime)[index]->SetPos(slimeXPosition + rename, slimeYPosition);
		else if (player->GetDir() == LEFT)
			(*slime)[index]->SetPos(slimeXPosition - rename, slimeYPosition);
		attackDelaymanager.SetStartTime();
		attackDelaymanager.SetDelayTime(1000);
		isInvincibility = true;
		(*slime)[index]->Hit(1);		//파워받아와서 매개변수교체
	}
	
	if (isInvincibility == true)
	{
		if (attackDelaymanager.CheckEndDelay() == false)
			return;

		isAttacked = false;
		isInvincibility = false;
	}
}