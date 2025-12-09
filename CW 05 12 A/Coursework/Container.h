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
	virtual Item* GetKey() override;
	virtual bool TryAddItem(Item* item) override;
	virtual bool TryLock(Item* item) override;
	virtual bool TryOpen() override;
	virtual std::list<Item*> GetContents() override;
};
