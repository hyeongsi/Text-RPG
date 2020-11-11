#pragma once
#include "Skill.h"

class Player;
class EarthquakeSkill : public Skill
{
private:
public:
	EarthquakeSkill(string skill_name, int use_mp, int power);
	void UseSkill(Player* player);
};
