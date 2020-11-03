#pragma once
#include "UI.h"

class InventoryUI : public UI
{
private:
	//map <string, wstring> inventory;
	map <string, string> inventory;
	//map <string, wstring> tempInventory;
	map <string, string> tempInventory;
public:
	InventoryUI();

	void OpenInventory();
	void CloseInventory();
	//void SetItemUI(wstring itemName, int index, int inventoryColSize);
	void SetItemUI(string itemName, int index, int inventoryColSize);
	void ClearInventoryUI();
};

