#include "InventoryUI.h"

InventoryUI::InventoryUI()
{
	string index;
	for (int i = 0; i <= 8; i++)
	{
		index = to_string(i);
		ReadFileString("inventory", index, inventory, "GameInfo\\SelectDungeonUI.ini");
	}
}

void InventoryUI::OpenInventory()
{
	string index;

	setlocale(LC_ALL, "ko_KR.UTF8");
	for (int i = 0; i < inventory.size(); i++)
	{
		GoToXY(3, 30 + i);
		index = to_string(i);
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

void InventoryUI::AddItemUI()
{

}
