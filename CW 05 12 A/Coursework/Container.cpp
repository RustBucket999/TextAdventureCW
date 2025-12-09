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

Item* Container::GetKey()
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

bool Container::TryOpen()
{
	return true;
}

std::list<Item*> Container::GetContents()
{
	return contents;
}
