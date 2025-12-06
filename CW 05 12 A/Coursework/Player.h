#pragma once
#include <string>
#include <list>
#include "Item.h"
#include "Inventory.h"
#include "Location.h"

class Player
{
public:
	Player();
	~Player();
private:
	//std::string location;
	Inventory* inventory;
	Location* location;
	int steps;
public:
	bool HasItem(Item* i);
	bool TakeItem(Item* i);
	bool DropItem(Item* i);
	bool OpenItem(Item* i);
	void PrintStatus();
};

