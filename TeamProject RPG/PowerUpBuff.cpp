#include "PowerUpBuff.h"
#include "Player.h"

PowerUpBuff::PowerUpBuff(string skill_name, int use_mp, int power)
{
	this->skill_name = skill_name;
	this->use_mp = use_mp;
	this->power = power;
}

void PowerUpBuff::UseSkill(Player* player)
{
	//player mp ���� �ʿ�
	/*if (!(player->Getmp() >= use_mp))
		return;*/
	
	//���� ���ӽð� ����??
	player->SetPower(player->GetPower() + 1);
	player->SetBuffTime(10000);
	//player->Setmp(player->Getmp()-use_mp);
}
