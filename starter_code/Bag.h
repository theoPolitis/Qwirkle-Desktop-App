#ifndef ASSIGN2_BAG_H
#define ASSIGN2_BAG_H
#include "Tile.h"
#include <iostream>
#include "LinkedList.h"
#include "Types.h"
#include <cassert>
#include "TileCodes.h"
#include <random>

class Bag{
    public:
        // constructor
        Bag();
        Bag(std::string serialised_bag);
        // deconstructor
        ~Bag();

        // returns first tile in bag
        Tile* getFront(); 

        // replaces a player's tile with a tile from the bag
        Tile* replace(Tile* playerTile);
        
        // returns size of bag
        int getBagSize();

        // returns tiles as string for save/load data
        string getTiles();

        // adds a tile to the bag
        void addBack(Tile* tile);

        void initializeTiles();       

    private:
        LinkedList *bag;
        void shuffle();
};

#endif //ASSIGN2_BAG_H