#include "Pos.h"

Pos::Pos()
{
	x = 0;
	y = 0;
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
	//x���� ����
	this->x = x;
}

const int& Pos::GetY()
{
	return y;
}

void Pos::SetY(const int y)
{
	//y���� ����
	this->y = y;
}
