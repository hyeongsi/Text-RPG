#include "InventoryUI.h"

InventoryUI::InventoryUI()
{
	string index;
	for (int i = 0; i <= 8; i++)
	{
		index = to_string(i);
		ReadFileString("inventory", index, inventory, "GameInfo\\SelectDungeonUI.ini");
	}

	tempInventory = inventory;
}

void InventoryUI::OpenInventory(const bool isMenu)
{
	string index;

	setlocale(LC_ALL, "ko_KR.UTF8");

	if (isMenu == false)
	{
		for (int i = 0; i < inventory.size(); i++)
		{
			GoToXY(3, 30 + i);
			index = to_string(i);
			cout << inventory[index];
		}
	}
	else
	{
		for (int i = 0; i < inventory.size(); i++)
		{
			GoToXY(3, 15 + i);
			index = to_string(i);
			cout << inventory[index];
		}
	}
	setlocale(LC_ALL, "");
}

void InventoryUI::CloseInventory()
{
	for (int i = 0; i < inventory.size(); i++)
	{
		GoToXY(3, 30 + i);
		cout << "                                       ";
	}
}

void InventoryUI::SetItemUI(string itemName, int index, int inventoryColSize)
{
	//인벤토리 첫칸 인덱스
	int startColNum = 4;
	int startRowNum = 1;

	startRowNum += (((index-1) / inventoryColSize) * 2);
	startColNum += (((index-1) % inventoryColSize) * 6);

	for (int i = 0; i < 2; i++)
		(inventory[to_string(startRowNum)])[startColNum + i] = itemName[i];
}

void InventoryUI::ClearInventoryUI()
{
	inventory = tempInventory;
}