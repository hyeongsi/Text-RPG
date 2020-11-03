#include "InventoryUI.h"

InventoryUI::InventoryUI()
{
	string index;
	for (int i = 0; i <= 8; i++)
	{
		index = to_string(i);
		//ReadFileString("inventory", index, inventory, "GameInfo\\SelectDungeonUI.ini");
		ReadFileString("inventory", index, inventory, "GameInfo\\SelectDungeonUI.ini");
	}

	tempInventory = inventory;
}

void InventoryUI::OpenInventory()
{
	string index;

	setlocale(LC_ALL, "ko_KR.UTF8");
	for (int i = 0; i < inventory.size(); i++)
	{
		GoToXY(3, 30 + i);
		index = to_string(i);
		//wcout << inventory[index];
		cout << inventory[index];
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

//void InventoryUI::SetItemUI(wstring itemName, int index, int inventoryColSize)
//{
//	//인벤토리 첫칸 인덱스
//	int startColNum = 2;
//	int startRowNum = 1;	
//
//	startRowNum += (((index-1) / inventoryColSize) * 2);
//	startColNum += (((index-1) % inventoryColSize) * 4);
//
//	for (int index = 0; index < 2; index++)
//		inventory[to_string(startRowNum)][startColNum + index] = itemName[index];
//}
void InventoryUI::SetItemUI(string itemName, int index, int inventoryColSize)
{
	//인벤토리 첫칸 인덱스
	int startColNum = 2;
	int startRowNum = 1;

	startRowNum += (((index-1) / inventoryColSize) * 2);
	startColNum += (((index-1) % inventoryColSize) * 4);

	//요것만 잘수정하면 아이템 출력 정상적으로 될것같음..
	for (int i = 0; i < 2; i++)
		(inventory[to_string(startRowNum)])[startColNum + i] = itemName[i];
}

void InventoryUI::ClearInventoryUI()
{
	inventory = tempInventory;
}