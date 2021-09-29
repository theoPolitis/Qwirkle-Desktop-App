
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H
#include <string>
#include <iostream>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

using std::string;

class Tile {
public:
   Tile();
   Tile(Colour colour, Shape shape);
   Tile(Tile& other);
   ~Tile();
   Colour colour;
   Shape  shape;

   Colour getColour();
   Shape getShape();
   bool getIsUsed();
   void setShape(Shape shape);
   void setColour(Colour colour);
   void setIsUsed(bool isUsed);
   bool equals(Tile* tile);

   //Will print 
   std::string toString();
private:
   bool isUsed;
};


#endif // ASSIGN2_TILE_H
