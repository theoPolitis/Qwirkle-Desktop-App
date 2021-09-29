#include "Player.h"

Player::Player(string name){
    this->name = name;
    hand = new Hand();
    score = 0;
    isPlayerTurn = false;
}

Player::Player(string name, Hand* hand, int score, bool isPlayerTurn){
    this->name = name;
    this->hand = hand;
    this->score = score;
    this->isPlayerTurn = isPlayerTurn;
}

Player::~Player(){
    delete hand;
    hand = nullptr;
}

int Player::getScore(){
    return this->score;
}

void Player::incrementScore(int amount){
    this->score += amount;
}

void Player::setScore(int score){
    this->score = score;
}

Hand* Player::getHand(){
    return hand;
}

void Player::setHand(Hand* hand){
    this->hand = hand;
}

string Player::getName(){
    return name;
}

void Player::setName(string name){
    this->name = name;
}

void Player::setPlayerTurn(bool playerTurn){
    this->isPlayerTurn = playerTurn;
}

bool Player::getIsPlayerTurn(){
    return isPlayerTurn;
}

string Player::serialise() {
    string serialised_hand = hand->getContents();
    string retVal = name + "\n";
    retVal += std::to_string(score);
    retVal += '\n';
    retVal += serialised_hand + "\n";
    return retVal;
}

bool Player::isName(string name)
{
    bool retVal = false;
    if (name.size() == this->name.size())
    {
        retVal = true;
        for (size_t i = 0; i < name.size(); ++i)
            if (name[i] != this->name[i])
                retVal = false;
    }
    return retVal;
}