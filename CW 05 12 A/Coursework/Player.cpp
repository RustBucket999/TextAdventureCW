#include "Player.h"
#include <iostream>

Player::Player(Inventory* inv)
{
    inventory = inv;
}

Player::~Player()
{
    inventory = nullptr;
}

bool Player::HasItem(Item* i)
{
    if (inventory->GetItem(i))
    {
        return true;
    }
    return false;
}

bool Player::TakeItem(Item* i)
{
    for (Item* item : location->GetContents())
    {
        if (item = i)
        {
            location->RemoveItem(i);
            inventory->AddItem(i);
            return true;
        }
    }
    return false;
}

bool Player::DropItem(Item* i)
{
    if (HasItem(i))
    {
        location->AddItem(i);
        inventory->RemoveItem(i);
        return true;
    }
    return false;
}

bool Player::OpenItem(Item* i)
{
    return false;
}

void Player::SetLocation(Location* l)
{
    location = l;
}

void Player::PrintStatus()
{
    std::cout << "Status :" << "\n";
    std::cout << "-------------------------------------------";
    std::cout << "Steps Taken: " << steps << "\n";
    GetInventory()->ReadInventory();
    std::cout << "Current Location: " << location->GetName() << "\n";
    
}

bool Player::PlayerMove(Location* t, std::string dir)
{
    // check wether you have the correct item, and the direction is not locked

    if (location->GetLockedPaths().size() != 0)
    {
        if (HasItem(location->GetLockedPaths()[dir]))
        {
            location = t;
            steps++;
        }
        else
        {
            std::cout << "That way seems to be locked, maybe an item can help?" << "\n" << "Hint: you have not picked the item up yet." << "\n";
            return false;
        }
    }
    else
    {
        location = t;
        steps++;
        return (true);
    }


}

Inventory* Player::GetInventory()
{
    return inventory;
}
