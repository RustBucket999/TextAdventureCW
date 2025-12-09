#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Item.h"
#include "Container.h"
#include "Inventory.h"
#include "Player.h"
#include "Location.h"


std::string NormaliseString(std::string victim)
{
	for (auto& v : victim)
	{
		v = std::tolower(v);
	}
	return victim;
}

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
}

void FindConnections(std::string str, Location* loc, std::vector<Location*> lMap, std::vector<Item*> iList)
{
	str = str.substr(str.find("Name:"));
	str = str.substr(0, str.find("Location: "));
	std::vector<std::string> directionList = { "NORTH", "SOUTH", "WEST", "EAST", "IN", "OUT", "UP", "DOWN" };


	std::string line;
	std::string target = "";
	std::string direction = "";
	int locationID = -1; // A number out of range, NULL just sets it to 0
	std::string key = "";
	Item* keyItem = nullptr;
	std::string tempTarget = "";
	int count = 0;

	bool directionSeparated = false;
	bool stitchingConnections = true;

	while (stitchingConnections)
	{
		for (std::string dir : directionList) // for each entry in direction list // If NORTH is first in directionList but not in stats file, then it will skip everything before that. Need strict direction order.
		{
			if (str.find(dir) != std::string::npos)
			{
				target = str.substr(str.find(dir));
				break;
			}
			if (dir == directionList.back())
			{
				stitchingConnections = false;
			}
		}

		if (!stitchingConnections)
		{
			break;
		}
		// filter out the target
		for (auto& a : target) //I realised later this could be a function
		{
			if (a != '\n')
			{
				tempTarget += a;
			}
			else
			{
				target = tempTarget;
				tempTarget = "";
				break;
			}
		}
		directionSeparated = false;
		//split between direction, ID, Key
		for (auto& a : target)
		{
			count++; // this is to fix a bug with the key in which it skips setting a key due to it never reaching a \n if its the last direction
			if (a != ' ' || directionSeparated) 
			{
				tempTarget += a;
			}
			
			if (a != '\n' && a != ',' && !directionSeparated)
			{
				if (!directionSeparated && a == ' ')
				{
					directionSeparated = true;
					direction = tempTarget;
					tempTarget = "";
					continue;
				}
			}
			else if (locationID < 0)
			{
				locationID = std::stoi(tempTarget);
				tempTarget = "";
			}
			if (tempTarget == ", ")
			{
				tempTarget = ""; // tempTarget when trying to store the key into memory also stores ", ", and this gets rid of that since its unnecessary and buggy.
				//I do think there are far cleaner and nicer ways of handling it, but I think that's something to do later.
			}
			if (a == '\n' || count == target.length()) 
			{
				key = tempTarget;
				tempTarget = "";
				if (key != "")
				{
					for (Item* i : iList)
					{
						if (i->GetName() == key)
						{
							keyItem = i;
							break;
						}
					}
				}
				else
				{
					keyItem = nullptr;
				}
			}

		}

		if (str.find(direction) + 2 != str.npos)
		{
			str = str.substr(str.find(direction) + 2); // this is to damage the direction we've already formatted, so it can't be found again
		}

		direction = NormaliseString(direction);
		loc->AddDirection(direction, lMap[locationID - 1], keyItem);
		target = "";
		tempTarget = "";
		key = "";
		keyItem = nullptr;
		locationID = -1;

	}

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

Item* CreateItem(std::string a, std::string b, std::vector<std::string> containers)
{
	bool isContainer = false;

	for (std::string s : containers)
	{
		if (s == a)
		{
			isContainer = true;
			break;
		}
	}
	if (isContainer)
	{
		Container* newItem = new Container(a, b);
		std::cout << "Item Name: " << newItem->GetName() << std::endl;
		std::cout << "Item Description: " << newItem->GetDescription() << std::endl;
		return newItem;
	}
	else 
	{
		Item* newItem = new Item(a, b);

		std::cout << "Item Name: " << newItem->GetName() << std::endl;
		std::cout << "Item Description: " << newItem->GetDescription() << std::endl;
		return newItem;
	}

	
}
Location* CreateLocation(int id)
{
	Location* location = new Location(FindLocation(id));
	return location;
}

Location* FindLocationInMap(int id, std::vector<Location*> locMap)
{
	for (Location* loc : locMap)
	{
		if (loc->GetID() == id)
		{
			return loc;
		}
	}
	return nullptr;
}

Item* SearchInventory(std::string itemName, Player* p)
{
	for (Item* ite : p->GetInventory()->GetInventory())
	{
		std::string tempIte = NormaliseString(ite->GetName());
		if (tempIte == itemName)
		{
			return ite;
		}
	}
}

void Look(Player* p)
{
	std::cout << "--------------------" << "\n";
	std::cout << "You have a look and see: " << "\n";
	std::cout << p->location->GetDescription() << "\n";
	std::cout << "There are " << p->location->GetContents().size() << " items here." << "\n";
	for (Item* i : p->location->GetContents())
	{
		std::cout << "- " << i->GetName() << ": " << i->GetDescription() << "\n";
	}
	for (int i = 0; i < p->location->GetDirectionNames().size(); i++)
	{
		std::cout << "There's a path: " << p->location->GetDirectionNames()[i] << "\n";
	}
}
int main()
{

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
	std::vector<std::string> containers{"Strongbox", "Cake"}; // I wish I could think of a quick way to detect each container within the file without heavily changing the file
	std::vector<std::string> keys{ "Red Key", "Knife" };
	unfilteredItem = FindItem("Screwdriver");
	// delete this section later

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

	bool stitchingLocation = false;

	bool createdLastLocation = false;
	bool createdLastItem = false;
	bool formattingItem = false;
	std::string locationData = "";
	std::string contentData = "";
	std::string itemData = "";

	std::string directionName = "";
	std::string tempDirection = "";
	std::vector <Item*> itemList;
	std::string tempKey = "";
	std::vector <std::string> tempContainerInsides; //just to store the names of the insides to actually add them
	std::map <std::string, std::string> keyToContainer; // Map out which key is linked to which container to know how to lock them, and add to them.
	std::map <std::string, std::vector<std::string>> containerToInsides; //Map out which insides belong to which container

	int count = locationMap.size() - 1;
	int IDcount = 0;

	Inventory* inventory = new Inventory();
	Player* player = new Player(inventory);
	while (creatingGame)
	{
	// Create Locations
		if (foundLastLocation != true)
		{
			 locationData = FindLocation(locationID); //this could probably be easier AND faster with rfind instead of find :)
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
			
			// For loop where you create the locations,
			for (int i = 1; i < locationID; i++)
			{
				Location* tempLocation = CreateLocation(i);
				locationMap.push_back(tempLocation);
			}
			createdLastLocation = true;
			player->SetLocation(locationMap[0]);
			
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
					AllDesc = AllDesc.substr(13);
					for (auto&d : AllDesc) // remove everything after end of line. NOTE TO SELF, YOU CAN REPLACE THIS WITH A FUNCTION 
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
					if (AllDesc.find("Contents:") != std::string::npos) // If it's a container, store all the contents, then the key
					{
						AllDesc = AllDesc.substr(AllDesc.find("Contents: "));
						AllDesc = AllDesc.substr(10);
						for (auto& n : AllDesc)
						{
							if (n != ',') // Again I really think if I had more time to spend I could make this one function
							{
								if (n != ' ' && tempItem != "")
								{
									tempItem += n;
								}
							}
							else //new std::vector<std::string> = 
							{
								tempContainerInsides.push_back(tempItem);
								containerToInsides[itemName] = tempContainerInsides;
								tempContainerInsides.clear();
								tempItem = "";
							}
						}
						//Store the keys
						AllDesc = AllDesc.substr(AllDesc.find("Keys: "));
						AllDesc = AllDesc.substr(6);
						for (auto& n : AllDesc)
						{
							if (n != ',')
							{
								if (n != ' ' && tempItem != "")
								{
									tempItem += n;
								}
							}
							else
							{
								tempKey = tempItem;
								tempItem = "";
							}
						}
						keyToContainer[tempKey] = itemName;
					}

					itemList.push_back(CreateItem(itemName, itemDesc, containers));
					if (itemName == "Letter")
					{
						player->GetInventory()->AddItem(itemList.back());
					}
					if (itemData == "" && AllDesc == "")
					{
						formattingItem = false;
					}
				}

				// Go through each item made, if any are containers, lock them up.
				for (Item* i : itemList) // Go through each item made
				{
					for (std::string k : keys) // For each key name established
					{
						if (i->GetName() == keyToContainer[k]) //if the item made has the same name as the container associated with the key
						{
							tempContainerInsides = containerToInsides[keyToContainer[k]];
							for (Item* t : itemList) // Go again through each item
							{
								if (t->GetName() == k) // If any of them match lock the container using them
								{
									i->TryLock(t);
								}
								
								for (std::string n : tempContainerInsides) // for each item inside the container found
								{
									if (t->GetName() == n) //if the current item in the second loop has the same name
									{
										i->TryAddItem(t); //add the current item in the second loop to the container (the item in the first loop)
									}
								}
							}

							break; // immediately stop searching keys if a match is found 
						}
					}

				}
				
			}
			std::string tempContentData;
			std::string actualItemName;
			int charCount = 0;
			for (int i = 1; i < locationID; i++) //make sure no item exists both on the floor and in a container
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
								
								actualItemName = tempContentData;
								//std::cout << "content data: " << contentData.length() << "\n";
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





			//Stitch the locations together.
			for (Location* loc : locationMap)
			{
				stitchingLocation = true;
				locationData = FindLocation(loc->GetID() + 1);
				FindConnections(locationData, loc, locationMap, itemList);

				for (std::string i : loc->GetDirectionNames())
				{
					std::cout << "CONNECTION MADE THIS LOOP " << i << "\n";
					std::cout << loc->GetName() << " CONNECTS TO: " << loc->GetDirections()[i]->GetName() << "\n";
				}

			}

			creatingGame = false;
		}
	
	}

	
	std::vector<std::string> verbList = {"north", "south", "west", "east", "in", "out", "up", "down", "take", "help", "drop", "open", "quit", "look", "inventory", "status"};

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
		Look(player);
		//Main game loop here
		while (gameLoop)
		{
			std::getline(std::cin, playerInput);
			// take the player's input and split between "verb" and "noun" if applicable
			std::string verb = "";
			std::string noun = "";
			bool whichHalf = false;
			bool verbFinish = false;
			bool foundCommand = false;
			bool allowNoun = false;
			std::string tempInput = "";
			count = 0;
			for (auto& c : playerInput)  // separate the input into 2 halves.
			{
				count++;
				if (c == ' ' || count == playerInput.length())
				{
					
					if (!whichHalf) 
					{
						whichHalf = true;
						verbFinish = true;
						if (count == playerInput.length())
						{
							tempInput += c;
						}
						verb = tempInput;
						tempInput = "";
						continue;
					}
					if (count == playerInput.length())
					{
						tempInput += c;
						whichHalf = false;
						noun = tempInput;
						tempInput = "";
					}

				}
				if ((c != ' ' && verbFinish == false) || verbFinish == true)
				{
					tempInput += c;
				}
				
			}
			if (verb != "")
			{
				verb = NormaliseString(verb);
				for (std::string d : verbList)
				{
					if (d == verb)
					{
						std::cout << "success!" << "\n";
						for (std::string dir : player->location->GetDirectionNames())
						{
							dir = NormaliseString(dir);
							if (dir == verb)
							{
								Location* tempCurrentLocation = player->location;
								player->PlayerMove(player->location->GetDirections()[verb], dir); //You cannot use something like PlayerMove to check as part of an if statement because it will keep any changes it does.
								if (player->location != tempCurrentLocation)
								{
									Look(player);
									tempCurrentLocation = player->location;
								}
								
								foundCommand = true;
								break;
							}
						}
						if (d == "help")
						{
							std::cout << "So here's the deal." << "\n";
							std::cout << "Controls: " << "\n";
							std::cout << "Messages you send are split like this Verb | Nouns. The first word is always a verb, everything after is counted as noun." << "\n";
							std::cout << "To move just type out the direction you want to move in, it will be treated as a verb. The full list of directions is below." << "\n";
							std::cout << "\n" << "north, south, west, east, in, out, up, down" << "\n" << "\n";
							std::cout << "Afterwards just type 'Look', to get a description of the sorrounding area.";
							std::cout << "To pick up or drop items, write 'Take/Drop [OBJECT NAME]'. Example below" << "\n";
							std::cout << "\n" << "Take Screwdriver" << "\n" << "\n";
							std::cout << "To open containers you need to first pick them out, then if you have the key in your inventory you can open them like the example bellow." << "\n";
							//std::cout << "\n" << "Open Strongbox" << "\n" << "\n"; MAKE SURE THIS IS ACCURATE WHEN IT IS IMPLEMENTED
							std::cout << "Similarly, you can inspect items in your inventory to get a description of them." << "\n";

							foundCommand = true;

						}
						else if ((  d == "take") || (  d == "drop"))
						{
							allowNoun = true; // continued from line 794
							foundCommand = true;
						}
						else if (  d == "look")
						{
							Look(player);
							foundCommand = true;
						}
						else if ( d == "open")
						{
							// continued from line 794
							allowNoun = true;
							foundCommand = true;
						}
						else if (  d == "inspect")
						{
							allowNoun = true; // continued from line 794
							foundCommand = true;
						}
						else if (  d == "inventory")
						{
							player->GetInventory()->ReadInventory();
							foundCommand = true;
						}
						else if (  d == "status")
						{
							player->PrintStatus();
							foundCommand = true;
						}
						else if (  d == "quit")
						{
							gameLoop = false;
							foundCommand = true;
						}
						else
						{
							std::cout << "Invalid Command!" << '\n';
							continue;
						}
						if (foundCommand)
						{
							break;
						}
					}

						
				}
			}

			if (noun != "" && allowNoun)
			{
				noun = NormaliseString(noun);
				if (verb == "take")
				{
					for (Item* ite : player->location->GetContents())
					{
						std::string tempIte = NormaliseString(ite->GetName());
						if (tempIte == noun)
						{
							player->TakeItem(ite);
							break;
						}
					}
				}
				else if (verb == "drop")
				{
					player->DropItem(SearchInventory(noun, player));
				}
				else if (verb == "open")
				{
					player->GetInventory()->GetItem(noun)->TryOpen(player->GetInventory());//try opening with items inside the same inventory
				}
				else if (verb == "inspect")
				{
					SearchInventory(noun, player)->GetDescription();
				}
				else
				{
					std::cout << "Invalid object!" << "\n";
					continue;
				}
			}

			

		}
		


	}

}