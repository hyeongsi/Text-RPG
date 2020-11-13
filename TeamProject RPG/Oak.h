#pragma once
#include "Monster.h"

class Oak : public Monster
{
public:
	static void AddInstance();

	inline void NoMakeMonster() {};
};