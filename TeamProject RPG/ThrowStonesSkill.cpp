#include "ThrowStonesSkill.h"
#include "player.h"

ThrowStonesSkill::ThrowStonesSkill(string skill_name, int use_mp, int power)
{
	this->skill_name = skill_name;
	this->use_mp = use_mp;
	this->power = power;
}

void ThrowStonesSkill::UseSkill(Player* player)
{
	if (!(player->GetMp() >= use_mp))
		return;


	player->SetMp(player->GetMp()-use_mp);
}
