#pragma once
#include "Pos.h"
#include "ShopUI.h"

//여기좀애매한게 NPC는 캐릭터를 상속받기가 애매해가지고 일단 직접선언
//네임스페이스저징이유는 Character의 LFEF랑 RIGHT랑 겹쳐서 중복선언되가지고
namespace NpcCheck
{
	enum PlayerDir
	{
		LEFT = 2,
		RIGHT = 3
	};
}

class Npc
{
private:
	static Npc* npc;
	Npc() {};

	Pos pos;
	ShopUI shopUI;

public:
	static Npc* GetInstance();
	static void ReleaseInstance();
	
	const Pos& GetPos();
	void SetPos(const int& x, const int& y);
	array<int, 2>& OpenShop(const int& playerXPosition, const int& playerYPosition, const int& playerDirection);
};