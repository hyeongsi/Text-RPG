#include "Oak.h"

//객체추가
void Oak::AddInstance()
{
	Monster::AddInstance();
	monster->push_back(new Oak());		//slime객체 추가
}