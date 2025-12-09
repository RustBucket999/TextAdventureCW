#pragma once
#include <string>
#include "Inventory.h"


class Item
{
public:
	Item(std::string a, std::string b);
	Item() = default;
	~Item();
protected:
	std::string name;
	std::string description;
public:
	std::string GetName();
	std::string GetDescription();
	virtual bool TryAddItem(Item* item);
	virtual bool TryLock(Item* item);
	virtual bool TryOpen(Inventory* inv);

};

