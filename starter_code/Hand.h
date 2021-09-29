#ifndef ASSIGN2_HAND_H
#define ASSIGN2_HAND_H
#include "Tile.h"
#include <iostream>
#include "LinkedList.h"
#include "Types.h"
#include <cassert>

class Hand
{
public:
    //CONSTRUCTOR
    Hand();
    Hand(std::string serialised_hand);
    //DECONSTRUCTOR
    ~Hand();
    //removes a tile that can be anywhere in the hand
    //call's delete on the pointer stored in the Hand
    bool removeTile(Tile tile);
    //adds a tile to the end of the list
    //Hand cant have more than 6 tiles in the vector
    void addTile(Tile *tile);

    // returns true if the tile is in the hand
    bool hasTile(Tile tile);

    //returns the Tile at the given index
    Tile *getTileByIndex(int i);

    //return the current size of the vector;
    int getHandSize();

    string getContents();

private:
    //Linked of tiles in the playersHand.
    LinkedList *hand;
    void cleanUp();
};

#endif //ASSIGN2_HAND_H