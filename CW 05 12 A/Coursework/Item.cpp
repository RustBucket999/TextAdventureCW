#include "Item.h"
#include "Location.h"
#include "Inventory.h"
#include <iostream>

Item::Item(std::string a, std::string b)
{
    name = a;
	description = b;
}

Item::~Item()
{
}

std::string Item::GetName()
{
    return name;
}

std::string Item::GetDescription()
{
    return description;
}

bool Item::TryAddItem(Item* item)
{
    std::cout << "You cannot add items to a non-container item." << "\n";
    return false;
}

bool Item::TryLock(Item* item)
{
    std::cout << "You cannot lock non-containers." << "\n";
    return false;
}

bool Item::TryOpen()
{
    std::cout << "You cannot open non-containers." << "\n";
    return false;
}

Item* Item::GetKey()
{
    return nullptr;
}

std::list<Item*> Item::GetContents()
{
    return std::list<Item*>{};
}



