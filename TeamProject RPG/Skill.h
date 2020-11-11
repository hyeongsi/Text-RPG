#pragma once
#include <iostream>

using namespace std;

class Player;
class Skill
{
protected:
	string skill_name;
	int use_mp;
	int power;
public:
	virtual void UseSkill(Player* player) = 0;
	virtual ~Skill() {};
};

