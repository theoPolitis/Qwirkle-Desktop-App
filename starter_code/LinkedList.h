#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <iostream>

class LinkedList
{
public:
   LinkedList();
   LinkedList(std::string serialised_ll);
   ~LinkedList();

   LinkedList(const LinkedList &other); // copy constructor

   void addBack(Node *node); // add a node to the back of the linkedlist

   Node *removeNode(int index); // remove the node at index

   Tile *removeTile(Tile tile); //remove by giving the tile we want to remove

   Node *getFront(); // returns the node at the front of the linkedlist

   Node *getNode(int index); // returns the node at index

   string getContents(); // gets the content of the linkedlist as a string

   int getSize(); // returns length

private:
   Node *head;
   Node *tail;
   int size;

   void constructorCommon();
};

#endif // ASSIGN2_LINKEDLIST_H
