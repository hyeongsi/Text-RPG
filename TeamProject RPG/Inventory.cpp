#include "Inventory.h"

void Inventory::OpenInventory(const bool isMenu)
{
	if (isMenu == true)
		inventoryUI.OpenInventory(true);
	else
		inventoryUI.OpenInventory();
}

void Inventory::CloseInventory()
{
	inventoryUI.CloseInventory();
}

void Inventory::PushItem(const int item, const bool isMenu)
{
	if (!IsFullInventory())
	{
		bag->emplace_back(item);
		SyncInventoryUI();
		if (isMenu)
			return;

		OpenInventory();
	}
}

const int Inventory::GetItem(const int selectIndex)
{
	if (IsEmptyInventory())
		return -1;
	if (!(selectIndex >= 0 && selectIndex < bag->size()))
		return -1;
	count = 0;
	for (auto bagIterator = bag->begin(); bagIterator != bag->end();)
	{
		if (count == selectIndex)
			return *bagIterator;
		
		count++;
		bagIterator++;
	}

	return -1;
}

void Inventory::DeleteItem(const int selectIndex)
{
	count = 0;
	for (auto bagIterator = bag->begin(); bagIterator != bag->end();)
	{
		if (count == selectIndex)
		{
			bag->erase(bagIterator);
			SyncInventoryUI();
			OpenInventory();
			return;
		}
		count++;
		bagIterator++;
	}
}

void Inventory::SyncInventoryUI()
{
	inventoryUI.ClearInventoryUI();

	int count = 0;
	for (auto bagIterator = bag->begin(); bagIterator != bag->end(); bagIterator++)
	{
		count++;
		switch (*bagIterator)
		{
		case 0:	//HP포션
			inventoryUI.SetItemUI("HP", count, 4);
			break;
		case 1: //MP포션
			inventoryUI.SetItemUI("MP", count, 4);
			break;
		case 2:	//도끼
			inventoryUI.SetItemUI("-v", count, 4);
			break;
		case 3:	//칼
			inventoryUI.SetItemUI("+-", count, 4);
			break;
		default:
			break;
		}	
	}
}

const bool Inventory::IsEmptyInventory()
{
	return (0==bag->size());
}

const bool Inventory::IsFullInventory()
{
	return (BAG_SIZE==bag->size());
}

const int Inventory::GetInventorySize()
{
	return static_cast<int>(bag->size());
}
