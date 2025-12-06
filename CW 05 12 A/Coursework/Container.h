#pragma once
#include "Item.h"
#include <string>

class Container : public Item
{
public:
	Container(std::string a, std::string b);
	~Container();
private:
	Item* contents;
	Item* containerKey;
	bool opened;
public:
	bool Open();

};
