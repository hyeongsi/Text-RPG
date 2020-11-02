#include "Pos.h"

Pos::Pos()
{
	this->x = 0;
	this->y = 0;
}

Pos::Pos(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool Pos::operator==(Pos pos)
{
	return (x == pos.GetX() && y == pos.GetY());
}

const int& Pos::GetX() const
{
	return x;
}

void Pos::SetX(const int x)
{
	//x범위 제한
	this->x = x;
}

const int& Pos::GetY() const
{
	return y;
}

void Pos::SetY(const int y)
{
	//y범위 제한
	this->y = y;
}
