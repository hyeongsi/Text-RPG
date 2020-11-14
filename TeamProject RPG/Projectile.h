#pragma once
#include "Pos.h"
class Projectile
{
private:
	Pos pos;
	int dir;
	int power;

public:
	Projectile(const Pos& spawnPos, const int& dir, const int& power);
	Pos& GetPos();
	void SetPos(Pos& pos);

	const int& GetDir();
	const int& GetPower();

	void MoveProjectile();
};

