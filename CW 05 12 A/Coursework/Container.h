#pragma once
#include "Item.h"
#include <string>
#include <list>

class Container : public Item
{
public:
	Container(std::string a, std::string b);
	~Container();
private:
	std::list<Item*> contents;
	Item* containerKey;
	bool opened;
public:
	bool Open();
	void AddItem(Item* item);
	void RemoveItem(Item* item);
	Item* GetKey(Item* item);
	virtual bool TryAddItem(Item* item) override;
	virtual bool TryLock(Item* item) override;
	virtual bool TryOpen(Inventory* inv) override;
};
