#pragma once
class Inventory
{
private:
	int bag[30] = {0};	//30칸 크기 인벤토리
	int selectInventoryIndex = 0;

public:
	bool SetItem(int item);

	bool IsFullInventory();
	void FixedOutofIndex();
};

