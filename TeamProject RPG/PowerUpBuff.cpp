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
	//player mp 구현 필요
	/*if (!(player->Getmp() >= use_mp))
		return;*/
	
	//버프 지속시간 설정??
	player->SetPower(player->GetPower() + 1);
	player->SetBuffTime(10000);
	//player->Setmp(player->Getmp()-use_mp);
}
