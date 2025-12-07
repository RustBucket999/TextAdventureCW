#pragma once
#include <vector>
#include <list>
#include <string>
#include "Item.h"

class Inventory
{
public:
	Inventory();
	~Inventory();
private:
	std::list<Item*> inventory;
	
public:
	Item* GetItem(Item* item);
	std::list<Item*> GetInventory();
	void AddItem(Item* newItem);
	void RemoveItem(Item* i);
	void ReadInventory();
	bool InspectItem(Item* i);
	
};

