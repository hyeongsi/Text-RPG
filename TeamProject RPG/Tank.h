#pragma once
#include "Monster.h"

class Tank : public Monster
{
public:
	static void AddInstance();

	inline void NoMakeMonster() {};
};