#include "Container.h"

Container::Container()
{

}

Container::~Container()
{
}

bool Container::Open()
{
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
