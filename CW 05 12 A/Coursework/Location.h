#pragma once
#include <string>
#include "Item.h"
#include <vector>
#include <map>

class Location
{
public:
	Location(std::string information);
	Location() = default;
	~Location();
public:
	std::string GetName();
	int GetID();
	std::string GetDescription();
	std::vector<std::string> GetDirectionNames();
	std::vector<Item*> GetContents();
	void AddItem(Item* item);
	void RemoveItem(Item* item);
	void AddDirection(std::string direction, Location* location);
private:
	int numberID;
	std::string name;
	std::string description;
	std::vector<Item*> contents;
	std::vector<std::string> directionNames;
	std::map<std::string, Location*> directions;
	Item* doorKey;
	//Make connections with maps/arrays/vectors / whatever.

};

