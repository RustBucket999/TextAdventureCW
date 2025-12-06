#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "Item.h"
#include "Player.h"
#include "Location.h"



std::string FindLocation(int number) // Check the file for formatting.
{
	std::ifstream StatsFile("Stats.txt");
	std::string line;
	std::string target = "";
	target = "Location: " + std::to_string(number);
	std::string output;
	bool hasFound = false;
	if (!StatsFile)
	{
		std::cout << "Error opening file!" << std::endl;
		return 0;
	}

	//size_t location = line.rfind("HP:100");

	while (std::getline(StatsFile, line)) // Search until you find the correct section, then store everything in memory until a blank
	{
		if (line == target)
		{
			hasFound = true;
		}
		else if (line == "\n")
		{
			hasFound = false;
		}
		if (hasFound == true)
		{
			//std::cout << line << "\n";
			output += line + "\n";
		}
	}
	StatsFile.close();
	return output;
	//while (std::getline(StatsFile, line))
	//{
	//	if (location != std::string::npos)
	//	{
	//		std::cout << line.substr(location + std::string("Location:").size());
	//	}
	//	else 
	//	{
	//		std::cout << "Bug";
	//	}
	//}


}

std::string FindItem(std::string itemName)
{
	std::ifstream StatsFile("Stats.txt");
	std::string line;
	std::string target = "Item: " + itemName;
	std::string output = "";
	bool hasFound = false;
	if (!StatsFile)
	{
		std::cout << "Error opening file!" << std::endl;
		return 0;
	}
	while (std::getline(StatsFile, line)) // Search until you find the correct section, then store everything in memory until a blank
	{
		if (line == target)
		{
			hasFound = true;
		}
		else if (line == "")
		{
			hasFound = false;
		}
		if (hasFound == true)
		{
			//std::cout << line << "\n";
			output += line + "\n";
		}
	}
	StatsFile.close();
	return output;
}
std::string FindAllItems()
{
	std::ifstream StatsFile("Stats.txt");
	std::string line;
	std::string target = "Item: ";
	std::string output = "";
	if (!StatsFile)
	{
		std::cout << "Error opening file!" << std::endl;
		return 0;
	}

	while (std::getline(StatsFile, line)) // Search until you find the correct section, then store everything in memory until a blank
	{
		if (line.find(target) == 0)
		{
			output += line.substr(target.length()) + "\n";
		}
	}
	StatsFile.close();
	return output;
}

Item* CreateItem(std::string a, std::string b)
{
	Item* newItem = new Item(a, b);
	std::cout << "Item Name: " << newItem->GetName() << std::endl;
	std::cout << "Item Description: " << newItem->GetDescription() << std::endl;
	return newItem;
}
Location* CreateLocation(int id)
{
	Location* location = new Location(FindLocation(id));
	return location;
}

int main()
{
	/*
	std::ofstream w_StatsFile("Stats.txt", std::ios::app);
	w_StatsFile << "\nARM:15";
	w_StatsFile.close();
	*/

	std::ifstream StatsFile("Stats.txt");
	if (!StatsFile)
	{
		std::cout << "Error opening file!" << std::endl;
		return 1;
	}
	std::string lastLocation;
	std::string lastItem;

	std::string line;
	std::string output;
	std::string playerInput;
	std::string unfilteredItem;
	std::string itemDescription;
	std::string itemName;
	std::string itemDesc;
	std::string tempItem;
	int HP = 0;
	int STR = 0;
	int ARM = 0;

	bool gameLoop = true;
	bool creatingGame = true;
	std::vector<Location*> locationMap;
	unfilteredItem = FindItem("Screwdriver");


	//std::cout << unfilteredItem;

	itemName = unfilteredItem.substr(unfilteredItem.find("Item: "));
	itemName = itemName.substr(6);

	itemDesc = unfilteredItem.substr(unfilteredItem.find("Description: "));
	itemDesc = itemDesc.substr(13);

	for (auto& t : itemName)
	{
		if (t != '\n')
		{
			tempItem += t;
		}
		else
		{
			itemName = tempItem;
			break;
		}
	}
	tempItem = "";
	
	int locationID = 1;
	bool foundLastLocation = false;
	bool foundLastItem = false;
	bool createdLastLocation = false;
	bool createdLastItem = false;
	bool formattingItem = false;
	std::string locationData = "";
	std::string contentData = "";
	std::string itemData = "";
	std::vector <Item*> itemList;
	//Something for finding the last item
	while (creatingGame)
	{
	// Create Locations
		if (foundLastLocation != true)
		{
			 locationData = FindLocation(locationID);
		}
		if (locationData != "")
		{
			std::cout << "Found Location : " << locationID << "\n";
			locationID++;
		}
		else
		{
			foundLastLocation = true;
			std::cout << "No more locations to create." << "\n";
		}
		if (locationID > 1 && foundLastLocation == true)
		{
			
			// creatingGame = false;
			// For loop where you create the locations, moving backwards.
			for (int i = 1; i < locationID; i++)
			{
				Location* tempLocation = CreateLocation(i);
				locationMap.push_back(tempLocation);
			}
			//locationID--;
			int count = locationMap.size();
			for (int i = 0; i < count; i++) // CURRENTLY LOCATIONS ARE JUST A STRAIGHT LINE
			{
				if (i > 0)
				{
					locationMap[i]->AddDirection("SOUTH", locationMap[i- 1]);
				}
				if (i + 1 < count)
				{
					locationMap[i]->AddDirection("NORTH", locationMap[i + 1]);
				}
			}

			createdLastLocation = true;
		}
		if (createdLastLocation)
		{
			// Create Items
			if (foundLastItem != true)
			{
				formattingItem = true;
				std::string itemData = FindAllItems();
				foundLastItem = true;
				while (formattingItem)
				{
					itemName = itemData.substr(0);
					for (auto& n : itemName) // remove everything after end of line
					{
						if (n != '\n')
						{
							tempItem += n;
						}
						else
						{
							itemName = tempItem;
							tempItem = "";
							itemData = itemData.substr(itemName.length()+1);
							break;
						}
					}
					std::string AllDesc = FindItem(itemName);
					AllDesc = AllDesc.substr(AllDesc.find("Description: ")); // remove everything before the first description on each loop
					for (auto&d : AllDesc) // remove everything after end of line
					{
						if (d != '\n')
						{
							tempItem += d;
						}
						else
						{
							itemDesc = tempItem;
							tempItem = "";
							AllDesc = AllDesc.substr(itemDesc.length() + 1);
							break;
						}
					}
					itemList.push_back(CreateItem(itemName, itemDesc));
					if (itemData == "" && AllDesc == "")
					{
						formattingItem = false;
					}
				}
			}
			std::string tempContentData;
			std::string actualItemName;
			int charCount = 0;
			for (int i = 1; i < locationID; i++)
			{ // Places the items in their respective locations

				locationData = FindLocation(i);
				locationData = locationData.substr(locationData.find("Contents: "));
				locationData = locationData.substr(10);
				for (auto& a : locationData) // Isolate only the contents
				{
					charCount = 0;
					if (a != '\n')
					{
						 tempContentData += a;
					}
					else
					{
						contentData = tempContentData;
						tempContentData = "";
						if (locationData.length() > contentData.length())
						{
							locationData = locationData.substr(contentData.length() + 1);
						}
						else locationData = "";
						
						
						for (auto& b : contentData)
						{
							charCount++;
							if (b != ',' && b != '\n' )
							{
								if (b != ' ')
								{
									tempContentData += b;
								}
								else if (tempContentData != "")
								{
									tempContentData += b;
								}
								
								
							} 
							if (b == ',' || b == '\n' || charCount == contentData.length())
							{
								//std::cout << charCount << "charCount" << "\n";
								
								actualItemName = tempContentData;
								std::cout << "content data: " << contentData.length() << "\n";
								tempContentData = "";
								// Actually add the items to the location.

								for (Item* item : itemList)
								{
									if (item->GetName() == actualItemName)
									{
										locationMap[i-1]->AddItem(item);
										break;
									}
								}

							}
						}
						tempContentData = ""; // making sure nothing gets kept
						break;
					}
				}
				std::cout << "finished LOOP: " << i << "\n";
			}
			creatingGame = false;
		}
	
	}

	int count = locationMap.size() - 1;
	Location* currentLocation = locationMap[0];
	Location* nextLocation = locationMap[1];
	std::cout << "Welcome to the game, type 'start' to proceed. Type 'exit' to quit. After beginning play, type 'help' for help." << "\n";
	while (gameLoop)
	{
		std::cin >> playerInput;
		if (playerInput == "exit")
		{
			gameLoop = false;
		}
		else if (playerInput != "start")
		{
			std::cout << "Invalid input, please try again." << "\n";
			continue;
		}
		//Main game loop here
		while (gameLoop)
		{
			std::cout << "LOCATION NUMBER :::" << currentLocation->GetID() << "\n";
			std::cout << currentLocation->GetName() << "\n";
			std::cout << "--------------------" << "\n";
			std::cout << currentLocation->GetDescription() << "\n";
			std::cout << "There are " << currentLocation->GetContents().size() << " items here." << "\n";
			for (int i = 0; i < currentLocation->GetDirectionNames().size(); i++)
			{
				std::cout << "GO: " << currentLocation->GetDirectionNames()[i] << "\n";
			}
			for (Item* i : currentLocation->GetContents())
			{
				std::cout << "- " << i->GetName() << ": " << i->GetDescription() << "\n";
			}
			std::cin >> playerInput;         //CHANGE THE CODE TO BETTER FIX SPECIFICATION. PROBS EASIER TO DELETE EVERYTHING AFTER HERE.
			// Interact code here
			// Move location code here
			if (playerInput == "NORTH")
			{
				if (currentLocation->GetID() + 1 > count)
				{
					std::cout << "You cannot walk there." << "\n";
					continue;
				}
				int nextID = currentLocation->GetID() + 1;
				nextLocation = locationMap[nextID];
				currentLocation = nextLocation;
				nextLocation = nullptr;
				
			}
			else if (playerInput == "SOUTH")
			{
				if (currentLocation->GetID() - 1 < 0)
				{
					std::cout << "You cannot walk there." << "\n";
					continue;
				}
				int nextID = currentLocation->GetID() - 1;
				nextLocation = locationMap[nextID];
				currentLocation = nextLocation;
				nextLocation = nullptr;

			}
			else
			{
				std::cout << "Invalid command." << "\n";
			}
			

		}
		


	}


	//while (std::getline(StatsFile, line))
	//{
	//	if (line.rfind("HP:", 0) == 0) //rfind returns 0 not 1
	//	{
	//		HP = std::stoi(line.substr(3));
	//		std::cout << "HP: " << HP << std::endl;
	//	}
	//	else if (line.rfind("STR:", 0) == 0)
	//	{
	//		STR = std::stoi(line.substr(4));
	//		std::cout << "STR: " << STR << std::endl;
	//	}
	//	else if (line.rfind("ARM:", 0) == 0)
	//	{
	//		ARM = std::stoi(line.substr(4));
	//		std::cout << "ARM: " << ARM << std::endl;
	//	}

	//	if (line.rfind("Item:", 0) == 0)
	//	{
	//		output = line.substr(6);
	//		std::cout << "Item: " << output << std::endl;
	//	}
	//}



	//w_StatsFile.close();
}