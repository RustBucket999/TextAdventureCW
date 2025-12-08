#pragma once
#include <string>
#include "Item.h"
#include <vector>
#include <list>
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
	std::map<std::string, Location*> GetDirections();
	std::map<std::string, Item*> GetLockedPaths();
	std::list<Item*> GetContents();
	void AddItem(Item* item);
	void RemoveItem(Item* item);
	void AddDirection(std::string direction, Location* location, Item* doorKey);
private:
	int numberID;
	std::string name;
	std::string description;
	std::list<Item*> contents;
	std::vector<std::string> directionNames;
	std::map<std::string, Location*> directions;
	std::map<std::string, Item*> lockedPaths;
	//Make connections with maps/arrays/vectors / whatever.

};

