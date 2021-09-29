#include "Board.h"
#include <sstream>
#include "Types.h"
using std::string;
using std::stringstream;

Board::Board()
{
    initializeBoard();
    currentScore = 0;
}

Board::~Board()
{
    board.clear();
}

bool Board::validFirstTile(Row row, Col col, Colour colour, Shape shape)
{
    bool validTile = true;
    //convert Ascii charcter to integer
    int rowConverted = convertRowString(row);

    int currentRow;
    int currentCol;

    //  1. Tile location must be available/empty
    if (emptyLocation(row, col))
    {
        //      2. Tile must be placed within bounds
        if (checkBound(rowConverted) && checkBound(col))
        {
            //      3. Scan through the whole board, make sure it's completely empty
            for (currentRow = 0; currentRow < BOARD_MAX_SIZE; ++currentRow)
            {
                for (currentCol = 0; currentCol < BOARD_MAX_SIZE; ++currentCol)
                {
                    // Not the first tile (other tiles exist) - namely when loading
                    if (!emptyLocation(currentRow, currentCol))
                    {
                        validTile = false;
                    }
                }
            }
        }
        // Not in bounds
        else
        {
            validTile = false;
        }
    }
    // Not empty
    else
    {
        validTile = false;
    }

    if (validTile)
    {
        currentScore += 1;
    }

    return validTile;
}

// Rules for valid tile placement:

//      1. Tile location must be available/empty
//      2. Tile must be placed within bounds
//      3. Tile must be beside another existing tile
//      4. Tile horizontal/vertical check for valid tile
//      5. Tile is valid, return true
bool Board::validTile(Row row, Col col, Colour colour, Shape shape)
{
    bool validTile = false;

    //  1. Tile location must be available/empty
    if (emptyLocation(row, col))
    {
        char rowAbove = row - 1;
        char rowBelow = row + 1;
        int colLeft = col - 1;
        int colRight = col + 1;

        bool horizontalTilesExist = false;
        bool verticalTilesExist = false;

        //      2. Tile must be placed within bounds
        //      3. Tile must be beside another existing tile

        if (!emptyLocation(rowAbove, col) && checkBound(convertRowString(rowAbove)))
        {
            verticalTilesExist = true;
        }
        if (!emptyLocation(rowBelow, col) && checkBound(convertRowString(rowBelow)))
        {
            verticalTilesExist = true;
        }
        if (!emptyLocation(row, colRight) && checkBound(colRight))
        {
            horizontalTilesExist = true;
        }
        if (!emptyLocation(row, colLeft) && checkBound(colLeft))
        {
            horizontalTilesExist = true;
        }

        // If only horizontal tiles
        if (horizontalTilesExist && !verticalTilesExist)
        {
            validTile = validateRow(row, col, shape, colour);
        }

        // If only vertical tiles
        if (!horizontalTilesExist && verticalTilesExist)
        {
            validTile = validateColumn(row, col, shape, colour);
        }

        // if there are both horizontal and vertical tiles
        if (horizontalTilesExist && verticalTilesExist)
        {
            validTile = (validateColumn(row, col, shape, colour) && validateRow(row, col, shape, colour));
        }
    }
    return validTile;
}

bool Board::validateRow(Row row, Col col, Shape shape, Colour colour)
{
    bool isValid = false;
    bool allSameShape = false;
    bool allSameColour = false;
    bool duplicates = false;
    int lengthOfTiles = 0;
    int westStart = col;
    int eastStart = col;

    // can't have vector larger than 6 including the tile you want to place
    std::vector<Tile *> rowTiles;
    Tile *tile = nullptr;

    // reate a vector, push_back into it the tiles from north and south
    // Add the tile you want to place into the vector for comparison
    rowTiles.push_back(new Tile(colour, shape));
    ++lengthOfTiles;
    // Add west tiles into the rowTiles vector
    while (checkBound(westStart - 1) && !emptyLocation(convertRowString(row), westStart - 1))
    {
        // Create tile and add to rowTiles array
        tile = new Tile(board[convertRowString(row)][westStart - 1]);
        rowTiles.push_back(tile);
        --westStart;
        ++lengthOfTiles;
    }
    while (checkBound(eastStart + 1) && !emptyLocation(convertRowString(row), eastStart + 1))
    {
        // Create tile and add to rowTiles array.
        tile = new Tile(board[convertRowString(row)][eastStart + 1]);
        rowTiles.push_back(tile);
        ++eastStart;
        ++lengthOfTiles;
    }

    allSameShape = sameShape(rowTiles, shape);
    allSameColour = sameColour(rowTiles, colour);
    // check the vector to see if there are repeats inside north vs south (i.e, cannot have same shapes,
    // but then multiple of the same coloured circle) - vector check for duplicate

    for (unsigned int j = 0; j < rowTiles.size(); ++j)
    {
        for (unsigned int k = j + 1; k < rowTiles.size(); ++k)
        {
            if (k != j && (rowTiles[k]->getColour() == rowTiles[j]->getColour()) &&
                rowTiles[k]->getShape() == rowTiles[j]->getShape())
            {
                duplicates = true;
            }
        }
    }

    // check sameshape OR samecolour on the entire (including placed tile) column
    if ((allSameColour || allSameShape) && !duplicates)
    {
        isValid = true;
        // Handle scoring
        if (lengthOfTiles == QWIRKLE_POINTS)
        {
            std::cout << "\n\nQwirkle!!!\n"
                      << std::endl;
            currentScore += QWIRKLE_POINTS;
        }
        currentScore += lengthOfTiles;
    }

    //clean up
    for (int i = 0; i < (int)rowTiles.size(); ++i)
    {
        delete rowTiles[i];
        rowTiles[i] = nullptr;
    }
    return isValid;
}

bool Board::validateColumn(Row row, Col col, Shape shape, Colour colour)
{
    bool isValid = false;
    bool allSameShape = false;
    bool allSameColour = false;
    bool duplicates = false;
    int lengthOfTiles = 0;
    int northStart = convertRowString(row);
    int southStart = convertRowString(row);

    // can't have vector larger than 6 including the tile you want to place
    std::vector<Tile *> columnTiles;
    Tile *tile = nullptr;

    // reate a vector, push_back into it the tiles from north and south
    // Add the tile you want to place into the vector for comparison
    columnTiles.push_back(new Tile(colour, shape));
    ++lengthOfTiles;
    // Add north tiles into the columnTiles vector
    while (checkBound(northStart - 1) && !emptyLocation(northStart - 1, col))
    {
        // Create tile and add to columnTiles array
        tile = new Tile(board[northStart - 1][col]);
        columnTiles.push_back(tile);
        --northStart;
        ++lengthOfTiles;
    }
    while (checkBound(southStart + 1) && !emptyLocation(southStart + 1, col))
    {
        // Create tile and add to columnTiles array
        tile = new Tile(board[southStart + 1][col]);
        columnTiles.push_back(tile);
        ++southStart;
        ++lengthOfTiles;
    }

    allSameShape = sameShape(columnTiles, shape);
    allSameColour = sameColour(columnTiles, colour);
    // check the vector to see if there are repeats inside north vs south (i.e, cannot have same shapes,
    // but then multiple of the same coloured circle) - vector check for duplicate

    for (unsigned int j = 0; j < columnTiles.size(); ++j)
    {
        for (unsigned int k = j + 1; k < columnTiles.size(); ++k)
        {
            if (k != j && (columnTiles[k]->getColour() == columnTiles[j]->getColour()) &&
                columnTiles[k]->getShape() == columnTiles[j]->getShape())
            {
                duplicates = true;
            }
        }
    }

    // check sameshape OR samecolour on the entire (including placed tile) column
    if ((allSameColour || allSameShape) && !duplicates)
    {
        isValid = true;
        // Handle scoring
        if (lengthOfTiles == QWIRKLE_POINTS)
        {
            std::cout << "\n\nQwirkle!!!\n"
                      << std::endl;
            currentScore += QWIRKLE_POINTS;
        }
        currentScore += lengthOfTiles;
    }

    //clean up
    for (int i = 0; i < (int)columnTiles.size(); ++i)
    {
        delete columnTiles[i];
        columnTiles[i] = nullptr;
    }
    return isValid;
}

// This method won't be called in GE if invalid
void Board::addTile(Row row, Col col, Colour colour, Shape shape)
{
    //convert Ascii charcter to integer
    int rowConverted = convertRowString(row);
    {
        board[rowConverted].at(col).setColour(colour);
        board[rowConverted].at(col).setShape(shape);
        board[rowConverted].at(col).setIsUsed(true);
    }
}

// Takes int row input
bool Board::emptyLocation(int row, int col)
{
    bool free = false;
    if (checkBound(row) && checkBound(col))
    {
        if (!board[row].at(col).getIsUsed())
        {
            free = true;
        }
    }
    return free;
}

// Takes char/Row row input
bool Board::emptyLocation(Row row, Col col)
{
    //return value
    bool free = false;
    //converts the row Letter to an int that we can use
    int rowConverted = convertRowString(row);

    //checks that the row and col are within the parameters
    if (checkBound(rowConverted) && checkBound(col))
    {
        if (!board[rowConverted].at(col).getIsUsed())
        {
            free = true;
        }
    }

    return free;
}

bool Board::sameColour(vector<Tile *> tiles, Colour colour)
{
    bool sameColour = true;
    for (int i = 0; i < (int)tiles.size(); ++i)
    {
        if (colour != tiles.at(i)->getColour())
        {
            sameColour = false;
        }
    }
    return sameColour;
}

bool Board::sameShape(vector<Tile *> tiles, Shape shape)
{
    bool sameShape = true;
    for (int i = 0; i < (int)tiles.size(); ++i)
    {
        if (shape != tiles.at(i)->getShape())
        {
            sameShape = false;
        }
    }
    return sameShape;
}

bool Board::checkBound(int position)
{
    //return value
    bool valid = false;
    //checks positions falls within parameters
    if (position >= COL_ROW_START && position <= COL_ROW_END)
    {
        valid = true;
    }

    return valid;
}

int Board::convertRowString(Row row)
{
    //converts the row to a useable int
    return (int)row - ASCII_OFFSET;
}

std::string Board::toString()
{
    string boardOutput = "   ";
    string ascii = " ";
    //print the column numbers;
    for (int i = 0; i < BOARD_MAX_SIZE; ++i)
    {
        boardOutput += std::to_string(i);
        if (i != 25)
        {
            boardOutput += " ";
        }

        if (i < 10)
        {
            boardOutput += " ";
        }
    }

    boardOutput += "\n  ";

    //printed doted lines under columns;
    for (int j = 0; j < BOARD_MAX_SIZE; ++j)
    {
        boardOutput += "---";
    }

    boardOutput += "-";

    //print each row and the contents of the tiles
    for (int row = 0; row < BOARD_MAX_SIZE; ++row)
    {
        boardOutput += "\n";
        ascii = (char)row + ASCII_OFFSET;
        boardOutput += ascii + " |";
        for (int col = 0; col < BOARD_MAX_SIZE; ++col)
        {
            boardOutput += board[row].at(col).toString() + "|";
        }
    }

    return boardOutput;
}

void Board::initializeBoard()
{
    //initialize a vector of vectors
    //SIZE = 26x26
    //board.resize(BOARD_MAX_SIZE, vector<Tile>(BOARD_MAX_SIZE));

    for (int i = 0; i < BOARD_MAX_SIZE; ++i)
    {
        board.push_back(vector<Tile>(BOARD_MAX_SIZE));
    }
}

std::string Board::serialise()
{
    string board_size = "0,0";
    if (board.size() > 0)
    {
        board_size = string();
        board_size += std::to_string((int)board.size());
        board_size += ',';
        board_size += std::to_string((int)board.size());
    }

    string tiles = string();
    bool first_tile = true;
    for (size_t row = 0; row < board.size(); ++row)
    {
        for (size_t col = 0; col < board[0].size(); ++col)
        {
            if (board[row].at(col).getIsUsed())
            {
                if (first_tile)
                    first_tile = false;
                else
                    tiles += ", ";
                tiles += board[row].at(col).toString() + "@";
                tiles += ((char)row + ASCII_OFFSET);
                tiles += std::to_string(col);
            }
        }
    }

    string retVal = board_size + '\n';
    retVal += tiles;
    return retVal;
}

int Board::getScore()
{
    return currentScore;
}

void Board::resetScore()
{
    currentScore = 0;
}

Board::Board(string serialised_board)
{
    initializeBoard();
    if (serialised_board.length() > 0)
    {
        stringstream sb_stream = stringstream(serialised_board);
        string current_tile = "";
        string current_tile_position = "";
        string *current_string = &current_tile;
        while (!sb_stream.eof())
        {
            char current_char;
            sb_stream >> current_char;
            if (current_char == FILE_TILE_SEPARATOR || sb_stream.eof())
            {
                stringstream stream = stringstream(current_tile);
                Colour colour;
                Shape shape;
                Col col;
                Row row;
                stream >> colour;
                stream >> shape;
                stream = stringstream(current_tile_position);
                stream >> row;
                stream >> col;
                addTile(row, col, colour, shape);
                current_tile = "";
                current_tile_position = "";
                current_string = &current_tile;
            }
            else if (current_char == FILE_TILE_POSITION_SEPARATOR)
                current_string = &current_tile_position;
            else
                (*current_string) += current_char;
        }
    }
}