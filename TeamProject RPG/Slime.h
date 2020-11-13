#pragma once
#include "Monster.h"

class Slime : public Monster
{
public:
	static void AddInstance();

	inline void NoMakeMonster() {};
};