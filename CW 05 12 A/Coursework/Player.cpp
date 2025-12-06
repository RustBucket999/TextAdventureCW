#include "Player.h"
#include <iostream>

Player::Player()
{
    Inventory* inventory = new Inventory();
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
    if (HasItem(i))
    {
        location->RemoveItem(i);
        inventory->AddItem(i);
        return true;
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

void Player::PrintStatus()
{
    std::cout << "Status :" << "\n";
    std::cout << "-------------------------------------------";
    std::cout << "Steps Taken: " << steps << "\n";
    //std::cout << inventory->ReadInventory(); Implement Inventory later
    std::cout << "Current Location: " << location->GetName() << "\n";
    
}
