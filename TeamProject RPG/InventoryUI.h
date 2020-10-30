#pragma once
#include "UI.h"

class InventoryUI : public UI
{
private:
	map <string, wstring> inventory;
	map <string, wstring> tempInventory;
public:
	InventoryUI();

	void OpenInventory();
	void CloseInventory();
	void SetItemUI(wstring itemName, int index, int inventoryColSize);
	void ClearInventoryUI();
};

