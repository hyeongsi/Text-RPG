#pragma once
#include "UI.h"

class InventoryUI : public UI
{
private:
	map <string, string> inventory;
	map <string, string> tempInventory;
public:
	InventoryUI();

	void OpenInventory();
	void CloseInventory();
	void SetItemUI(string itemName, int index, int inventoryColSize);
	void ClearInventoryUI();
};

