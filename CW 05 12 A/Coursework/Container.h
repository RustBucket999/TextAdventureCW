#pragma once
#include "Item.h"
#include <string>
#include <list>

class Container : public Item
{
public:
	Container();
	~Container();
private:
	std::list<Item*> contents;
	Item* containerKey;
	bool opened;
public:
	bool Open();
	void AddItem(Item* item);
	void RemoveItem(Item* item);
};
