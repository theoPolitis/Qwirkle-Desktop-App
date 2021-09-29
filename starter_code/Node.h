#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node
{
public:
   Node(Tile *tile, Node *next);
   ~Node();
   Node(Node &other);
   //data that the node is storing
   Tile *tile;
   //a pointer to the next tile in the linked list
   Node *next;
};

#endif // ASSIGN2_NODE_H