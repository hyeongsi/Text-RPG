#pragma once
#include "UI.h"

class InventoryUI : public UI
{
private:
	map <string, string> inventory;
public:
	InventoryUI();

	void OpenInventory();
	void CloseInventory();
	void AddItemUI();
};

