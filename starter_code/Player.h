#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H
#include "Hand.h"
#include <string>

using std::string;

class Player {
    public:
        //constructor for a player in a new game
        Player(string name);
        //constructor for a player when eading from a file
        Player(string name, Hand* hand, int score, bool isPlayerTurn);
        //DECONSTRUCTOR
        ~Player();
        //returns the player score
        int getScore();
        //increments the score of the player
        void incrementScore(int amount);
        //sets the score of the player
        void setScore(int score);
        //returns the hand of the player
        Hand* getHand();
        //sets the hand of the player
        void setHand(Hand* hand);
        //returns the name of the player
        string getName();
        //set the name of the player
        void setName(string name);
        //boolean representation if its the player turn or not
        void setPlayerTurn(bool playerTurn);
        //returns if its the players turn or not
        bool getIsPlayerTurn();
        //string representation of the player for writing to a file
        string serialise();
        //returns if the name passed is the name of this player
        bool isName(std::string name);
    private:
        Hand* hand;
        string name;
        int score;
        bool isPlayerTurn;
};


#endif //ASSIGN2_PLAYER_H