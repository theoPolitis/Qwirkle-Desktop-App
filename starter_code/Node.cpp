#include "Node.h"

Node::Node(Tile *tile, Node *next) : tile(tile), next(next)
{
}

Node::~Node()
{
    delete tile;
}

Node::Node(Node &other)
{
    tile = new Tile(*other.tile);
    next = other.next;
}