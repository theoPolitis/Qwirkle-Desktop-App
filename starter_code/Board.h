#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <iostream>
#include <vector>
#include "Tile.h"
#include "Types.h"
#include <algorithm>

#define MAX_LINE_LENGTH 6
#define ASCII_OFFSET 65

using std::cout;
using std::endl;
using std::string;
using std::vector;

typedef char Row;
typedef int Col;

class Board
{
public:
    Board();
    Board(std::string serialised_board);
    ~Board();
    //Row in the range [A-Z]
    //0 <= Col <= 25
    void addTile(Row row, Col col, Colour colour, Shape shape);
    //string representaion of the board
    std::string toString();
    //save method
    std::string serialise();
    //simple method for checking if the location on the board is free
    bool emptyLocation(Row row, Col col);
    bool emptyLocation(int row, int col);
    //converts the row char to an int we can use
    int convertRowString(Row row);
    bool validTile(Row row, Col col, Colour colour, Shape shape);
    bool validFirstTile(Row row, Col col, Colour colour, Shape shape);
    int getScore();
    void resetScore();

private:
    //vectore of vectors for holding the state of the board
    vector<vector<Tile>> board;

    // the scores will be set and be retrived by the GE
    int currentScore;
    //initializes the board to a game state
    void initializeBoard();
    char convertIntToASCII(int value);
    bool sameShape(vector<Tile *> tiles, Shape shape);
    bool sameColour(vector<Tile *> tiles, Colour colour);
    bool noDuplicates(vector<Tile *> tiles);
    //0 >= position <= 25
    bool checkBound(int position);
    bool validateColumn(Row row, Col col, Shape shape, Colour colour);
    bool validateRow(Row row, Col col, Shape shape, Colour colour);
    bool validateNorthTiles(Row row, Col col, Shape shape, Colour colour);
    bool validateSouthTiles(Row row, Col col, Shape shape, Colour colour);
    bool validateEastTiles(Row row, Col col, Shape shape, Colour colour);
    bool validateWestTiles(Row row, Col col, Shape shape, Colour colour);
};

#endif //ASSIGN2_BOARD_H