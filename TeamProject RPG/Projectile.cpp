#include "Projectile.h"
#include "Player.h"

Projectile::Projectile(const Pos& spawnPos, const int& dir, const int& power)
{
	pos = spawnPos;
	this->dir = dir;
	this->power = power;
	if (dir == RIGHT)
		pos.SetX(pos.GetX() + 3);
	else
		pos.SetX(pos.GetX() - 3);

	pos.SetY(pos.GetY() - 1);

	//스폰 x위치 확인 추가하기
}

Pos& Projectile::GetPos()
{
	return pos;
}

void Projectile::SetPos(Pos& pos)
{
	this->pos = pos;
}

const int& Projectile::GetDir()
{
	return dir;
}

const int& Projectile::GetPower()
{
	return power;
}

void Projectile::MoveProjectile()
{
	//이동불가 확인 후
	//이동불가면 삭제

	if (dir == RIGHT)
		pos.SetX(pos.GetX() + 1);
	else
		pos.SetX(pos.GetX() - 1);
}
