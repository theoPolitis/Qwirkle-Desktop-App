#include "LinkedList.h"
#include <sstream>
#include "Types.h"

LinkedList::LinkedList()
{
   constructorCommon();
}

void LinkedList::constructorCommon()
{
   head = nullptr;
   tail = nullptr;
   size = 0;
}

LinkedList::~LinkedList()
{
   Node *current = head;
   Node *deleteNode = nullptr;

   while (current != nullptr)
   {
      deleteNode = current;
      current = current->next;
      delete deleteNode;
      deleteNode = nullptr;
   }

   current = nullptr;
}

LinkedList::LinkedList(const LinkedList &other)
{
   Node *temp = other.head;
   while (temp->next != nullptr)
   {
      addBack(new Node(temp->tile, temp->next));
      size++;
      temp = temp->next;
   }
}

void LinkedList::addBack(Node *node) // add node to end of linkedlist
{
   if (head == nullptr)
   {
      head = node;
      tail = node;
   }
   else
   {
      Node *oldTail = tail;
      oldTail->next = node;
      tail = node;
   }
   ++size;
}

Node *LinkedList::removeNode(int index)
{
   Node *current = getNode(index);
   Node *retNode = nullptr;
   if (current != nullptr)
   {
      retNode = new Node(*current);
      if (index < 1)
      {
         head = current->next;
      }
      else
      {
         Node *prev = getNode(index - 1);
         if (current->next != nullptr)
         {
            prev->next = current->next;
         }
         else
         {
            prev->next = nullptr;
            tail = prev;
         }
      }
      size--;
      delete current;
   }
   return retNode;
}

Node *LinkedList::getFront()
{
   return removeNode(0);
}

Node *LinkedList::getNode(int index)
{
   Node *retNode = nullptr;
   if (index >= 0 && index < size)
   {
      int count = 0;
      Node *current = head;
      while (count != index)
      {
         current = current->next;
         count++;
      }
      retNode = current;
   }
   return retNode;
}

string LinkedList::getContents()
{
   string content = "";
   if (head != nullptr)
   {
      content += head->tile->toString();
      Node *temp = head->next;
      while (temp != nullptr)
      {
         content += "," + temp->tile->toString();
         temp = temp->next;
      }
   }
   return content;
}

int LinkedList::getSize()
{
   return size;
}

Tile *LinkedList::removeTile(Tile tile)
{
   Node *current = head;
   Node *prevNode = nullptr;
   Node *deleteNode = nullptr;

   if (head->tile->equals(&tile))
   {
      deleteNode = head;
      Tile *returnNode = new Tile(*head->tile);
      head = head->next;
      delete deleteNode;
      --size;
      return returnNode;
   }

   if (tail->tile->equals(&tile))
   {
      deleteNode = tail;
      Tile *returnNode = new Tile(*tail->tile);
      tail = getNode(size - 2);
      tail->next = nullptr;
      delete deleteNode;
      --size;
      return returnNode;
   }

   while (current != nullptr)
   {
      if (tile.equals(current->tile))
      {
         Tile *returnTile = new Tile(*current->tile);
         prevNode->next = current->next;
         delete current;
         current = nullptr;
         --size;
         return returnTile;
      }

      prevNode = current;
      current = current->next;
   }
   return nullptr;
}

LinkedList::LinkedList(string serialised_ll)
{
   constructorCommon();
   if (serialised_ll.length() > 0) // Haha, hacky fix go brrrrrrr
   {
      std::stringstream sl_stream = std::stringstream(serialised_ll);
      string current_tile = "";
      while (!sl_stream.eof())
      {
         char current_char;
         sl_stream >> current_char;
         if (current_char == FILE_TILE_SEPARATOR || sl_stream.eof())
         {
            std::stringstream tile_stream = std::stringstream(current_tile);
            Colour colour;
            Shape shape;
            tile_stream >> colour;
            tile_stream >> shape;
            Tile* tile = new Tile(colour, shape);
            addBack(new Node(tile, nullptr));
            current_tile = "";
         }
         else
            current_tile += current_char;
      }
   }
}