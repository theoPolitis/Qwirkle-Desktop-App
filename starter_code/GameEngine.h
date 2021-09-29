#ifndef ASSIGN2_GAME_ENGINE_H
#define ASSIGN2_GAME_ENGINE_H
#include <iostream>
#include <memory>
#include <string>
#include "Hand.h"
#include "Board.h"
#include "TileCodes.h"
#include "Player.h"
#include "Bag.h"
#include <regex>
#include <vector>
#include <iterator>
#include <sstream>
#include <fstream>

class GameEngine
{
public:
    //CONSTRUCTOR
    GameEngine();
    //DECONTRUCTOR
    ~GameEngine();

    //call this method to run the game
    void run();

    //TESTING METHODS
    //COMMENT OUT BEFORE SUBMISSION
    void testHand();
    void testBoard();
    void testPlayer();
    void testBag();
    void testGameEnd();

    //add a new player into the game
    void addPlayer(std::string playerName);
    //used for loading players from a file into a game
    void addPlayer(std::string playerName, Hand *hand, int score, bool isPlayerTurn);

    int getPlayerSize();
    // method for starting a new game, called from the Menu class
    void startGame();

    //set the variable of isNewGame
    void setIsNewGame(bool newGame);
    //switch which players turn it is
    void switchPlayerTurnState(int index);
    //display the info for that turn
    void displayTurnInfo(int playerIndex);
    //checks to see if the game is finished
    bool isGameFinished();
    //compares string to the regex provided
    bool regexVsStringCheck(std::string name, std::string regex);
    bool validateFile(std::string fileName);
    //splits the string by whitespace
    std::vector<string> splitString(std::string response);
    std::string getTileFromResponse(std::string response);

    // Saving and loading
    void save(string filename);
    void load(string filename);

private:
    int playerCount;
    std::vector<Player *> players;
    Board *board;
    bool newGame;
    Bag *bag;
    bool gameFinished;
    bool firstMove;
    bool gameLoaded;

    //checks to see if the response from player is valid
    bool passResponse(std::string response);
    bool checkIfTileExistsInHand(std::string stringTile, Player *player);
    bool isResponseValid(std::string repsonse, Player *player);
    //check that the contents of the file are in the correct format using a regex
    bool checkFileFormat(std::string fileName);
    //simple method for checking if a file exists
    bool checkFileExists(std::string fileName);
    bool checkIfTileLocFree(Row row, Col col);
    const char splitLocOrTileCode(std::string code);
    std::string getCommand(std::string response);
    std::string getLocation(std::string response);
    std::string getFileName(std::string response);
    //players vector must have at least one element inside it
    Player *getWinningPlayer();
    string serialise();
};

#endif //ASSIGN2_GAME_ENGINE_H