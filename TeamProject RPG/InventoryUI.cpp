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

void InventoryUI::OpenInventory()
{
	string index;

	for (int i = 0; i < inventory.size(); i++)
	{
		GoToXY(3, 30 + i);
		index = to_string(i);
		wcout << inventory[index];
	}
}

void InventoryUI::CloseInventory()
{
	for (int i = 0; i < inventory.size(); i++)
	{
		GoToXY(3, 30 + i);
		cout << "                                       ";
	}
}

void InventoryUI::SetItemUI(wstring itemName, int index, int inventoryColSize)
{
	//인벤토리 첫칸 인덱스
	int startColNum = 2;
	int startRowNum = 1;	

	startRowNum += ((index / inventoryColSize) * 2);
	startColNum += ((index % inventoryColSize - 1) * 4);

	for (int index = 0; index < 2; index++)
		inventory[to_string(startRowNum)][startColNum + index] = itemName[index];
}

void InventoryUI::ClearInventoryUI()
{
	inventory = tempInventory;
}