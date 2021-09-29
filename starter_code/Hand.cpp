#include "Hand.h"

//CONSTRUCTOR
Hand::Hand()
{
    hand = new LinkedList();
}

//DECONSTRUCTOR
Hand::~Hand()
{
    delete hand;
}

bool Hand::hasTile(Tile tile)
{
    bool success = false;
    for (int i = 0; i < getHandSize(); i++)
    {
        Tile *temp = new Tile(*getTileByIndex(i));
        if (temp->toString() == tile.toString())
        {
            success = true;
        }
    }
    return success;
}

//removes a tile and frees the memory associeted with that tile in the vector
bool Hand::removeTile(Tile tile)
{
    bool success = false;
    if (hand->getSize() != 0)
    {
        Tile *returnTile = hand->removeTile(tile);
        if (returnTile != nullptr)
        {
            success = true;
        }
        delete returnTile;
    }

    return success;
}

//
//adds a tile to the vector
//checks that the amount of tiles is < 6
//adds a tile to the end of the vector
void Hand::addTile(Tile *tile)
{
    if (hand->getSize() < MAX_HAND_SIZE && tile != nullptr)
    {
        hand->addBack(new Node(tile, nullptr));
    }
}

//index < 6
Tile *Hand::getTileByIndex(int index)
{
    assert(index < hand->getSize());
    return hand->getNode(index)->tile;
}

//returns the current size of the vector
int Hand::getHandSize()
{
    return hand->getSize();
}

string Hand::getContents()
{
    return hand->getContents();
}

Hand::Hand(string serialised_hand)
{
    hand = new LinkedList(serialised_hand);
}