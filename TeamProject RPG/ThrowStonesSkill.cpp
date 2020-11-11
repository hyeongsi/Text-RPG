#include "ThrowStonesSkill.h"

ThrowStonesSkill::ThrowStonesSkill(string skill_name, int use_mp, int power)
{
	this->skill_name = skill_name;
	this->use_mp = use_mp;
	this->power = power;
}

void ThrowStonesSkill::UseSkill(Player* player)
{
	//player mp 구현 필요
	/*if (!(player->Getmp() >= use_mp))
		return;*/


	//player->Setmp(player->Getmp()-use_mp);
}
