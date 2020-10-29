#pragma once
#include <list>
#include "InventoryUI.h"

using namespace std;

constexpr auto RANDOM_ITEM_SIZE = 4;
constexpr auto BAG_SIZE = 16;

class Inventory
{
private:
	InventoryUI inventoryUI;

	list<int>bag;
	int count = 0;
public:
	void OpenInventory();
	void CloseInventory();

	void PushItem(const int item);					//아이템 추가
	const int GetItem(const int selectIndex);		//아이템 찾기
	void DeleteItem(const int selectIndex);			//아이템 삭제

	const bool IsEmptyInventory();		//가방 사이즈를 통해 비었는지 판별
	const bool IsFullInventory();		//가방 사이즈를 통해 가득인지 판별
};

