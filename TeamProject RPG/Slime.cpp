#include "Slime.h"

//객체추가
void Slime::AddInstance()
{
	Monster::AddInstance();
	monster->push_back(new Slime());		//slime객체 추가
}