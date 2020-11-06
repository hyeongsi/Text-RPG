#include "Oak.h"

vector<Oak*>* Oak::oak = nullptr;
Pos* Oak::itemPosition = new Pos();
int Oak::exp = 0;

//��ü�߰�
void Oak::AddInstance()
{
	if (oak == nullptr)
		oak = new vector<Oak*>();

	oak->push_back(new Oak());		//oak��ü �߰�
}

//��ü���͹�ȯ
vector<Oak*>* Oak::GetInstance()
{
	return oak;
}

//�����Ҵ������ϱ�
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

//�� ��ũ���� ü�°� ���ݷ°� ���ǵ� �����ϱ�
void Oak::SetStats(int hp, int power, int speed, int exp)
{
	Monster::MonsterSetStats(hp, power, speed);
	Oak::exp = exp;
}

//�ӵ��� ���� �����̱�,,, �÷��̾� ��ġ�������� ������
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

	//������ �������ڸ� ĳ���Ͱ��ִ� ��ġ�� ��ũ��ġ�� �������� ��ũ�̵������� ����
	this->SetPos((this->GetPos().GetX() - playerXPosition > 0) ? this->GetPos().GetX() - 1 : this->GetPos().GetX() + 1, (this->GetPos().GetY() - playerYPosition > 0) ? this->GetPos().GetY() - 1 : this->GetPos().GetY() + 1);
	this->isMove = true;
}

void Oak::Die()
{
	//��ũü�¾����� ����
	for (auto oakHP = oak->begin(); oakHP != oak->end();)
	{
		if ((*oakHP)->Hp <= 0)		
		{
			itemPosition->SetX(((*oakHP)->GetPos().GetX() % 2 == 0) ? (*oakHP)->GetPos().GetX() + 1 : (*oakHP)->GetPos().GetX());
			itemPosition->SetY((*oakHP)->GetPos().GetY());
			delete (*oakHP);		//�Ҵ������ �ݳ�
			oak->erase(oakHP);	//���Ϳ��� ����
			return;
		}
		else
			oakHP++;
	}
}

//������ �¾��� �� ������ �Լ�
void Oak::isHit(const int& playerXPosition, const int& playerYPosition, const int& playerDirection, const int& playerPower)
{
	//Ÿ��
	int attackXPosition = 0;
	int attackYPosition = 0;

	//�� ��ũ���� ��ġ
	int oakXPosition = this->GetPos().GetX();
	int oakYPosition = this->GetPos().GetY();

	//�÷��̾�¹��⿡ ���� ������ġ����
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
