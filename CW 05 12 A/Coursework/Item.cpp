#include "Item.h"
#include "Location.h"

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



