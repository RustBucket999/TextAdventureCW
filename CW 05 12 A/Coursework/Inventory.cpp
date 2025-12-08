#include "Inventory.h"
#include <iostream>

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

Item* Inventory::GetItem(Item* i)
{
	for (Item* item : inventory)
	{
		if (item == i)
		{
			return item;
		}
	}
	return nullptr;
}

std::list<Item*> Inventory::GetInventory()
{
	return inventory;
}

void Inventory::AddItem(Item* newItem)
{
	inventory.push_back(newItem);
}

void Inventory::RemoveItem(Item* removeItem)
{
	inventory.remove(removeItem);
}

void Inventory::ReadInventory()
{
	for (Item* item : inventory)
	{
		std::cout << "--" << item->GetName() << "\n";
	}
}

bool Inventory::InspectItem(Item* i)
{
	if (GetItem(i))
	{
		std::cout << i->GetName() << "\n";
		std::cout << i->GetDescription() << "\n";
		return true;
	}
	return false;
}