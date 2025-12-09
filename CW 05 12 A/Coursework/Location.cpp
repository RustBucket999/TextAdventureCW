#include "Location.h"
#include "Item.h"
#include <iostream>

Location::Location(std::string information)
{
	// Find information, cut it out, store it, repeat.
	int iteration = 0;
	std::string detail = "";
	std::string temp = ""; // Does this cause a memory leak?
	bool loop = true;

	while (loop)
	{
		if (iteration == 0)
		{
			std::string tempID = information.substr(information.find("Location: "));
			tempID = tempID.substr(10);
			detail = tempID;
		}
		else if (iteration == 1)
		{
			name = information.substr(information.find("Name: "));
			name = name.substr(6);
			detail = name;
		}
		else if (iteration == 2)
		{
			description = information.substr(information.find("Description: "));
			description = description.substr(13);
			detail = description;
		}
		else if (iteration >= 3)
		{

			//std::cout << "Directions not implemented yet." << "\n";
			if (information == "")
			{
				//std::cout << "End of information" << "\n";
				loop = false;
			}
		}
		
		
		//std::cout << information; // Debug to check wether there will be an attempted to read past memory
		for (auto& t : detail)
		{
			if (t != '\n')
			{
				temp += t;
			}
			else
			{	
				break;
			}
		}
		if (iteration == 0)
		{
			numberID = std::stoi(temp) - 1;
		}
		else if (iteration == 1)
		{
			name = temp;
		}
		else if (iteration == 2)
		{
			description = temp;
		}
		else if (iteration == 3)
		{
			//contents = temp;
		}
		else if (iteration >= 4)
		{
			//directions = temp;
		}
		temp = "";
		information = information.substr(information.find('\n') + 1);
		iteration++;
	}

}

Location::~Location()
{
}

std::string Location::GetName()
{
	return name;
}
int Location::GetID()
{
	return numberID;
}
std::string Location::GetDescription()
{
	return description;
}

std::vector<std::string> Location::GetDirectionNames()
{
	return directionNames;
}

std::map<std::string, Location*> Location::GetDirections()
{
	return directions;
}

std::map<std::string, Item*> Location::GetLockedPaths()
{
	return lockedPaths;
}

std::list<Item*> Location::GetContents()
{
	return contents;
}

void Location::AddDirection(std::string direction, Location* location, Item* doorKey)
{
	if (location != nullptr)
	{
		directionNames.push_back(direction);
		directions[direction] = location;
		if (doorKey != nullptr)
		{
			lockedPaths[direction] = doorKey;
		}

		//std::cout << "Direction added: " << direction << std::endl;
		//std::cout << "Location assigned : " << location->GetName() << std::endl;
		if (doorKey != nullptr)
		{
			//std::cout << "Door locked with : " << doorKey->GetName() << std::endl;
		}


	}
	else 
	{
		//std::cout << "Error No Location" << "\n";
	}

}

void Location::AddItem(Item* item)
{
	contents.push_back(item);
	//std::cout << item->GetName() << "      " << "BRRRRRRRRRRRRRRRRRR" << "\n";
}

void Location::RemoveItem(Item* item)
{
	for (Item* ite : contents)
	{
		if (ite == item)
		{
			contents.remove(ite);
			break;
		}
	}
}