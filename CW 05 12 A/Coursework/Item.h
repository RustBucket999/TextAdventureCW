#pragma once
#include <string>
class Item
{
public:
	Item(std::string a, std::string b);
	Item() = default;
	~Item();
public:
    
private:
	std::string name;
	std::string description;
public:
	std::string GetName();
	std::string GetDescription();

};

