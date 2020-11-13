#include "Tank.h"

void Tank::AddInstance()
{
	Monster::AddInstance();
	monster->push_back(new Tank());		//slime객체 추가
}