#include "Inventory.h"

bool Inventory::SetItem(int item)
{
	if(IsFullInventory())
		return false;

	bag[selectInventoryIndex++] = item;
	FixedOutofIndex();
}

bool Inventory::IsFullInventory()
{
	return (selectInventoryIndex >= (sizeof(bag) / sizeof(bag[0])));
}

void Inventory::FixedOutofIndex()
{
	if (0 > selectInventoryIndex)
		selectInventoryIndex = 0;
	if ((sizeof(bag) / sizeof(bag[0])) <= selectInventoryIndex)
		selectInventoryIndex = (sizeof(bag) / sizeof(bag[0]))-1;
}
