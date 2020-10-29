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
		bag.emplace_back(item);
}

const int Inventory::GetItem(const int selectIndex)
{
	count = 0;
	for (auto bagIterator = bag.begin(); bagIterator != bag.end();)
	{
		if (count == selectIndex)
			return *bagIterator;
		
		count++;
		bagIterator++;
	}
}

void Inventory::DeleteItem(const int selectIndex)
{
	count = 0;
	for (auto bagIterator = bag.begin(); bagIterator != bag.end();)
	{
		if (count == selectIndex)
		{
			bag.erase(bagIterator);
			return;
		}

		count++;
		bagIterator++;
	}
}

const bool Inventory::IsEmptyInventory()
{
	return (0==bag.size());
}

const bool Inventory::IsFullInventory()
{
	return (BAG_SIZE==bag.size());
}