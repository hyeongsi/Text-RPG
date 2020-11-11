#pragma once
#include "UI.h"

class ShopUI : public UI
{
private:
	map<string, string> salesList;
	int currentChoice = 2;

public:
	ShopUI();
	void Show();
	int SelectUI();
};

namespace Shop
{
	enum Shop {
		NOTHING = -1,
		HP = 0,
		MP = 1,
		SWORD = 2,
		AXE = 3,
		EXIT = 4
	};
}
