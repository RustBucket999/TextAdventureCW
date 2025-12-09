#include "Container.h"

Container::Container(std::string a, std::string b)
{
	name = a;
	description = b;
}

Container::~Container()
{
}

bool Container::Open()
{
	return false;
}

void Container::AddItem(Item* item)
{
	contents.push_back(item);
}

void Container::RemoveItem(Item* item)
{
	for (Item* i : contents)
	{
		if (i == item)
		{
			contents.remove(i);
		}
	}
}

Item* Container::GetKey(Item* item)
{
	return containerKey;
}

bool Container::TryAddItem(Item* item)
{

	AddItem(item);
	return true;
}

bool Container::TryLock(Item* item)
{
	containerKey = item;
	return true;
}

bool Container::TryOpen(Inventory* inv)
{
	//if (inv->GetItem(containerKey->GetName()) && !opened)
	//{
	//	containerKey = nullptr;
	//	opened = true;
	//	for (Item* i : contents)
	//	{
	//		inv->AddItem(i);
	//	}
	//	contents.clear();
	//}
	
}
