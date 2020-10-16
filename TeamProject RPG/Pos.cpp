#include "Pos.h"

Pos::Pos()
{
	x = 10;
	y = 10;
}

Pos::Pos(int x, int y)
{
	this->x = x;
	this->y = y;
}

const int& Pos::GetX()
{
	return x;
}

void Pos::SetX(const int x)
{
	//x범위 제한
	this->x = x;
}

const int& Pos::GetY()
{
	return y;
}

void Pos::SetY(const int y)
{
	//y범위 제한
	this->y = y;
}
