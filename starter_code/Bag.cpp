#include "Bag.h"

//CONSTRUCTOR
Bag::Bag()
{
    bag = new LinkedList();
}

//DECONSTRUCTOR
Bag::~Bag()
{
    delete bag;
}

Tile *Bag::getFront()
{
    Tile *retTile = nullptr;
    if (bag->getSize() > 0)
    {
        Node *retNode = bag->getFront();
        retTile = new Tile(*retNode->tile);
        delete retNode;
    }
    return retTile;
}

int Bag::getBagSize()
{
    return bag->getSize();
}

string Bag::getTiles()
{
    return bag->getContents();
}

Tile *Bag::replace(Tile *playerTile)
{
    Tile *bagTile = bag->getFront()->tile;
    bag->addBack(new Node(playerTile, nullptr));
    return bagTile;
}

void Bag::initializeTiles()
{
    char colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    int shapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

    for (int col = 0; col < 6; ++col)
    {
        for (int sha = 0; sha < 6; sha++)
        {
            for (int i = 0; i < DUPLICATES; ++i)
            {
                Tile *tile = new Tile(colours[col], shapes[sha]);
                Node *node = new Node(tile, nullptr);
                bag->addBack(node);
                tile = nullptr;
                node = nullptr;
            }
        }
    }
    shuffle();
}

void Bag::shuffle()
{
    std::random_device randomSeed;
    for (int i = MAXIMUM_TILES; i > 0; i--)
    {
        std::uniform_int_distribution<int> uniform_dist(0, i);
        Node *node = new Node(bag->removeNode(uniform_dist(randomSeed))->tile, nullptr);
        bag->addBack(node);
    }
}

void Bag::addBack(Tile* tile) {
    bag->addBack(new Node(tile, nullptr));
}

Bag::Bag(string serialised_bag)
{
    bag = new LinkedList(serialised_bag);
}