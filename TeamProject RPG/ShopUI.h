#pragma once
#include "UI.h"
#include <array>

class ShopUI : public UI
{
private:
	map<string, string> shopList;
	map<string, string> buyList;
	map<string, string> salesList;
	int currentChoice = 2;
	array<int, 2> itemChoice;

public:
	ShopUI();
	void ShopShow();
	void BuyShow();
	void SaleShow();
	array<int, 2>& SelectUI();
};

namespace ShopBuy
{
	enum ShopBuy {
		HP,
		MP,
		SWORD,
		AXE
	};
}

namespace Shop
{
	enum Shop {
		BUY,
		SALE,
		EXIT
	};
}
