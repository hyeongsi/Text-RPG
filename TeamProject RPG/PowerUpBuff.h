#pragma once
#include "Skill.h"

class Player;
class PowerUpBuff : public Skill
{
private:
public:
	PowerUpBuff(string skill_name, int use_mp, int power);
	void UseSkill(Player* player);
};
