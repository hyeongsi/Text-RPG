#include "Inventory.h"

void Inventory::OpenInventory()
{
	inventoryUI.OpenInventory();
}

void Inventory::CloseInventory()
{
	inventoryUI.CloseInventory();
}

void Inventory::PushItem(const int item)
{
	if(!IsFullInventory())
		bag->emplace_back(item);
}

const int Inventory::GetItem(const int selectIndex)
{
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
			//inventoryUI.SetItemUI(L"HP", count, 4);
			inventoryUI.SetItemUI("HP", count, 4);
			break;
		case 1: //MP포션
			//inventoryUI.SetItemUI(L"MP", count, 4);
			inventoryUI.SetItemUI("MP", count, 4);
			break;
		case 2:	//도끼
			//inventoryUI.SetItemUI(L"-v", count, 4);
			inventoryUI.SetItemUI("-v", count, 4);
			break;
		case 3:	//칼
			//inventoryUI.SetItemUI(L"+-", count, 4);
			inventoryUI.SetItemUI("+-", count, 4);
			break;
		default:
			break;
		}	
	}
	OpenInventory();
}

const bool Inventory::IsEmptyInventory()
{
	return (0==bag->size());
}

const bool Inventory::IsFullInventory()
{
	return (BAG_SIZE==bag->size());
}