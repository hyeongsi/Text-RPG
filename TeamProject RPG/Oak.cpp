#include "Oak.h"

vector<Oak*>* Oak::oak = nullptr;
Pos* Oak::itemPosition = new Pos();

//��ü�߰�
void Oak::AddInstance()
{
	if (oak == nullptr)
		oak = new vector<Oak*>();

	oak->push_back(new Oak());		//slime��ü �߰�
}

//��ü���͹�ȯ
vector<Oak*>* Oak::GetInstance()
{
	return oak;
}

//�����Ҵ������ϱ�
void Oak::ReleaseInstance()
{
	//�����Ҵ������ϱ�
}

//�� ��ũ���� ü�°� ���ݷ°� ���ǵ� �����ϱ�
void Oak::SetStats(int hp, int power, int speed)
{
	this->Hp = hp;
	this->power = power;
	this->speed = speed;
}

//�ӵ��� ���� �����̱�,,, �÷��̾� ��ġ�������� ������
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

	//������ �������ڸ� ĳ���Ͱ��ִ� ��ġ�� ��ũ��ġ�� �������� ��ũ�̵������� ����
	this->SetPos((this->GetPos().GetX() - playerXPosition > 0) ? this->GetPos().GetX() - 1 : this->GetPos().GetX() + 1, (this->GetPos().GetY() - playerYPosition > 0) ? this->GetPos().GetY() - 1 : this->GetPos().GetY() + 1);
	this->isMove = true;
}

//�̸� isDie�������.. ������ vector�� Ư���׸��� ���ٶ�� iterator�� ����ؾ��ϴµ�.. �׷���� �ڵ�������
//ó������ ������ �ݺ��ϴϱ�.. ������ü�ǰ����� �����ҹ���� ���°Ͱ��Ƽ�.. �̰͵�ã�ƺ���
void Oak::Die()
{
	//��ũü�¾����� ����
	for (auto oakHP = oak->begin(); oakHP != oak->end(); oakHP++)
	{
		if ((*oakHP)->Hp <= 0 && oakHP == --oak->end())		//������ �������� �ִ³��� Ư�����.. ���ϸ� ������ ����ã��
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

//������ �¾��� �� ������ �Լ�
void Oak::isHit(int playerXPosition, int playerYPosition)
{
	//Ÿ��
	int attackXPosition = 0;
	int attackYPosition = 0;

	//�� ��ũ���� ��ġ
	int oakXPosition = this->GetPos().GetX();
	int oakYPosition = this->GetPos().GetY();

	//�÷��̾�¹��⿡ ���� ������ġ����
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

	//getX setX�ȵǴ�����
	if (isAttacked == true && isInvincibility == false)
	{
		if (player->GetDir() == RIGHT)
			this->SetPos(oakXPosition + rename, oakYPosition);

		else if (player->GetDir() == LEFT)
			this->SetPos(oakXPosition - rename, oakYPosition);
		attackDelaymanager.SetStartTime();
		attackDelaymanager.SetDelayTime(invincibilityTime);
		isInvincibility = true;
		this->Hit(player->GetPower());		//Hit()�� �ۿ��� ������ ����غ����ҵ�
	}

	if (isInvincibility == true)
	{
		if (attackDelaymanager.CheckEndDelay() == false)
			return;

		isAttacked = false;
		isInvincibility = false;
	}
}
