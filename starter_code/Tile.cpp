#include "Tile.h"
//SHAPE == int
//COLOUR == char
Tile::Tile(){
    this->shape = 0;
    this->colour = ' ';
    this->isUsed = false;
}

Tile::Tile(Colour colour, Shape shape){
    this->shape = shape;
    this->colour = colour;
    this->isUsed = true;
}

Tile::Tile(Tile& other){
    shape = other.shape;
    colour = other.colour;
    isUsed = other.isUsed;
}

Tile::~Tile(){

}

Colour Tile::getColour(){
    return colour;
}

Shape Tile::getShape(){
    return shape;
}

bool Tile::getIsUsed(){
    return isUsed;
}

void Tile::setShape(Shape shape){
    this->shape = shape;
}

void Tile::setColour(Colour colour){
    this->colour = colour;
}

void Tile::setIsUsed(bool isUsed){
    this->isUsed = isUsed;
}

bool Tile::equals(Tile* tile){
    bool equals = false;
    if(this->colour == tile->colour && this->shape == tile->shape){
        equals = true;
    }
    return equals;
}

std::string Tile::toString(){
    string thisTile = "  ";

    if(isUsed){
        thisTile = colour + std::to_string(shape);
    }

    return thisTile;
}


