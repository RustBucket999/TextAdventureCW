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
    //std::cout << inventory->ReadInventory(); Implement Inventory later
    std::cout << "Current Location: " << location->GetName() << "\n";
    
}

bool Player::PlayerMove(Location* t)
{
    location = t;
    steps++;
    return (true);
    return false;
}

Inventory* Player::GetInventory()
{
    return inventory;
}
