#pragma once
#include <string>
#include <list>
#include "Item.h"
#include "Inventory.h"
#include "Location.h"

class Player
{
public:
	Player(Inventory* inv);
	~Player();
private:
	Inventory* inventory;
	int steps;
public:
	Inventory* GetInventory();
	bool HasItem(Item* i);
	bool TakeItem(Item* i);
	bool DropItem(Item* i);
	bool OpenItem(Item* i);
	void SetLocation(Location* l);
	void PrintStatus();
	bool PlayerMove(Location* t, std::string dir);
public:
	Location* location;
};

