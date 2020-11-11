#pragma once
#include "Skill.h"
class ThrowStonesSkill : public Skill
{
private:
public:
	ThrowStonesSkill(string skill_name, int use_mp, int power);
	void UseSkill(Player* player);

};

