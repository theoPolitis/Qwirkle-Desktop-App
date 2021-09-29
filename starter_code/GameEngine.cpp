#include "GameEngine.h"
#include "SerialisedData.h"
#include <cstring>
#include <sstream>

using std::stringstream;

//CONSTRUCTOR
GameEngine::GameEngine()
{
    board = new Board();
    //keps tracks of how may players are in the game
    playerCount = 0;
    //determines if the game is new or finished
    newGame = false;
    gameFinished = false;
    gameLoaded = false;
}

//DECONSTRUCTOR
GameEngine::~GameEngine()
{
    for (int i = playerCount - 1; i > 0; --i)
    {
        delete players[i];
        players[i] = nullptr;
    }

    delete board;
    delete bag;
}

// Should call methods on the view,
// i.e player.setScore, view.printBoard() etc
void GameEngine::run()
{
    std::string response = "";
    bool isError = false;

    if (newGame)
    {
        startGame();
    }

    while (!gameFinished && !isError)
    {
        for (int i = 0; i < MAX_PLAYERS && !gameFinished && !isError; ++i)
        {
            //std::cout << "players turn " << players[i]->getIsPlayerTurn() << std::endl;
            if (players[i]->getIsPlayerTurn() && !isError)
            {

                // check hand can place valid move on board

                //display the current information for the player
                displayTurnInfo(i);
                //gets the respons of user input to perform action and validates
                std::cout << std::endl;
                std::cout << "> ";
                std::getline(std::cin, response);

                //validate response
                while (!isError && !isResponseValid(response, players[i]) && !std::cin.eof())
                {
                    if (regexVsStringCheck(response, SAVE_REGEX) && getCommand(response) == "save")
                    {
                        try
                        {
                            save(getFileName(response) + FILE_EXTENSION);
                            std::cout << std::endl;
                            std::cout << "Game successfully saved" << std::endl;
                            std::cout << std::endl;
                        }
                        catch (std::exception &e)
                        {
                            std::cout << std::endl;
                            std::cout << "Save Failed" << std::endl;
                            std::cout << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "Invalid input" << std::endl;
                    }

                    std::cout << "> ";
                    std::getline(std::cin, response);
                }

                if (std::cin.eof())
                {
                    isError = true;
                    std::cout << "^D" << std::endl
                              << std::endl;
                    std::cout << "Goodbye" << std::endl;
                }
                //GAMEPLAY STARTS HERE
                //use this to place a tile in the grid
                // Checking is already done above
                if (getCommand(response) == "place")
                {

                    //methods that retrieve useful information for adding a tile to the grid
                    std::string tileString = getTileFromResponse(response);
                    std::string locationString = getLocation(response);

                    //create the needed varuiables from user input
                    const char colour = splitLocOrTileCode(tileString);
                    const Shape shape = std::stoi(tileString.substr(1));

                    Row row = splitLocOrTileCode(locationString);
                    Col col = std::stoi(locationString.substr(1));
                    if (gameLoaded)
                    {
                        board->resetScore();
                    }

                    //remove the tile from the hand
                    //add a new tile from the bag to the hand
                    //add the removed tile from the hand into the board at the given position
                    Tile tile(colour, shape);
                    players[i]->getHand()->removeTile(tile);
                    players[i]->getHand()->addTile(bag->getFront());
                    board->addTile(row, col, colour, shape);
                    players[i]->setScore(players[i]->getScore() + board->getScore());
                    board->resetScore();

                    gameLoaded = false;
                    //REPLACE FUNCTION
                }
                else if (getCommand(response) == "replace")
                {
                    if (bag->getBagSize() > 0)
                    {
                        //method that returns the information needed
                        std::string tileString = getTileFromResponse(response);

                        //breaks the user input string into colour and sha[e]
                        const char colour = splitLocOrTileCode(tileString);
                        const Shape shape = std::stoi(tileString.substr(1));

                        Tile *tile = new Tile(colour, shape);

                        //remove tile from player hand
                        //place tile that was removed from hand back in the bag
                        //put a new tile from bag into the hand
                        //set tile to nullptr because its a reference to a tile in the bag now
                        players[i]->getHand()->removeTile(*tile);
                        Tile *bagTile = bag->replace(tile);
                        players[i]->getHand()->addTile(bagTile);
                        tile = nullptr;
                    }
                }
                else if (getCommand(response) == "save")
                {
                    save(getFileName(response));
                    std::cout << std::endl;
                    std::cout << "Goodbye" << std::endl;
                    isError = true;
                }
                else if (getCommand(response) == "quit")
                {
                    std::cout << std::endl;
                    std::cout << "Goodbye" << std::endl;
                    isError = true;
                }

                //EXIT STATEMENT
                if (this->isGameFinished())
                {
                    std::cout << "Game over" << std::endl;
                    for (int i = 0; i < (int)players.size(); ++i)
                    {
                        std::cout << "Score for " << players.at(i)->getName() << ": " << players.at(i)->getScore() << std::endl;
                    }

                    std::cout << "Player " << getWinningPlayer()->getName() << " won!" << std::endl;
                    std::cout << std::endl;
                    std::cout << "Goodbye" << std::endl;

                    gameFinished = true;
                }

                //switches which players turn it is
                switchPlayerTurnState(i);
            }
        }
    }

    // std::cout << "PlayerOne: " << players[0]->getName() << std::endl;
    // std::cout << "PlayerOneHand: " << players[0]->getHand()->getContents() << std::endl;
    // std::cout << "PlayerTwo: " << players[1]->getName() << std::endl;
    // std::cout << "PlayerTwoHand: " << players[1]->getHand()->getContents() << std::endl;

    bool activateTests = false;

    if (activateTests == true)
    {
        testHand();
        testBoard();
        testPlayer();
        testBag();
    }
}

const char GameEngine::splitLocOrTileCode(std::string code)
{
    return *code.substr(0).c_str();
}

Player *GameEngine::getWinningPlayer()
{
    Player *player = players.at(0);
    int maxScore = players.at(0)->getScore();
    for (int i = 0; i < (int)players.size(); ++i)
    {
        if (players.at(i)->getScore() > maxScore)
        {
            maxScore = players.at(i)->getScore();
            player = players.at(i);
        }
    }

    return player;
}

std::string GameEngine::getCommand(std::string response)
{
    std::vector<string> words(splitString(response));

    return words[0];
}

std::string GameEngine::getLocation(std::string response)
{
    std::vector<string> words(splitString(response));

    return words[3];
}
std::string GameEngine::getFileName(std::string fileName)
{
    std::vector<string> words(splitString(fileName));

    return words[1];
}

bool GameEngine::isResponseValid(std::string response, Player *player)
{
    bool isValid = false;
    //checks to see that the text matches a regex
    if (passResponse(response))
    {
        // If response is quit or save, valid input
        if (getCommand(response) == "quit" || getCommand(response) == "save")
        {
            isValid = true;
        }
        else if (getCommand(response) != "quit" && getCommand(response) != "save")
        {
            //checks to see if the tile exists in the hand
            if (checkIfTileExistsInHand(getTileFromResponse(response), player))
            {
                //from here check the location that the user wants is free on the board
                if (getCommand(response) == "place")
                {
                    //create the variables that we need for checking the location
                    std::string location = getLocation(response);
                    std::string tileString = getTileFromResponse(response);

                    //create the needed varuiables from user input
                    Row row = splitLocOrTileCode(location);
                    Col col = std::stoi(location.substr(1));
                    const char colour = splitLocOrTileCode(tileString);
                    const Shape shape = std::stoi(tileString.substr(1));

                    // First check if it's the first move; can be placed anywhere
                    if (board->validFirstTile(row, col, colour, shape))
                    {
                        isValid = true;
                    }
                    else
                    {
                        // Not the first move
                        // Do normal validation on the tile, set isValid to the result
                        isValid = board->validTile(row, col, colour, shape);
                    }
                }
                if (getCommand(response) == "replace")
                {
                    //method that returns the information needed
                    std::string tileString = getTileFromResponse(response);

                    //breaks the user input string into colour and sha[e]
                    const char colour = splitLocOrTileCode(tileString);
                    const Shape shape = std::stoi(tileString.substr(1));

                    Tile *tile = new Tile(colour, shape);

                    //remove tile from player hand
                    //place tile that was removed from hand back in the bag
                    //put a new tile from bag into the hand
                    //set tile to nullptr because its a reference to a tile in the bag now
                    isValid = player->getHand()->hasTile(*tile);
                }
            }
        }
    }
    return isValid;
}

std::string GameEngine::getTileFromResponse(std::string response)
{
    std::vector<string> words = splitString(response);
    return words[1];
}

bool GameEngine::checkIfTileExistsInHand(std::string stringTile, Player *player)
{
    const char colour = *stringTile.substr(0).c_str();
    Shape shape = std::stoi(stringTile.substr(1));
    Tile *tile = new Tile(colour, shape);
    bool exists = false;

    for (int i = 0; i < player->getHand()->getHandSize(); ++i)
    {
        if (tile->equals(player->getHand()->getTileByIndex(i)))
        {
            exists = true;
        }
    }

    delete tile;
    tile = nullptr;
    return exists;
}
std::vector<string> GameEngine::splitString(std::string response)
{
    std::vector<string> words;
    std::istringstream stream(response);
    while (!stream.eof())
    {
        std::string word = " ";
        stream >> word;
        words.push_back(word);
    }

    return words;
}

bool GameEngine::passResponse(std::string response)
{
    bool matches = false;
    std::regex placeRegex(PLACE_REGEX);
    std::regex replaceRegex(REPLACE_REGEX);
    std::regex saveRegex(SAVE_REGEX);
    if (std::regex_match(response, placeRegex) || std::regex_match(response, replaceRegex) || response == "quit")
    {
        matches = true;
    }

    return matches;
}

void GameEngine::displayTurnInfo(int playerIndex)
{
    //print playerInfo
    std::cout << players[playerIndex]->getName() << ", it's your turn" << std::endl;
    std::cout << "Score for " << players[0]->getName() << ": " << players[0]->getScore() << std::endl;
    std::cout << "Score for " << players[1]->getName() << ": " << players[1]->getScore() << std::endl;

    //print the board
    std::cout << board->toString() << std::endl;
    std::cout << std::endl;

    //print current player hand
    std::cout << "Your hand is" << std::endl;
    std::cout << players[playerIndex]->getHand()->getContents() << std::endl;
}

void GameEngine::switchPlayerTurnState(int playerIndex)
{
    if (playerIndex == 0)
    {
        if (players[1]->getHand()->getHandSize() != 0)
        {
            players[0]->setPlayerTurn(false);
            players[1]->setPlayerTurn(true);
        }
        else if (players[1]->getHand()->getHandSize() == 0)
        {
            players[0]->setPlayerTurn(true);
            players[1]->setPlayerTurn(false);
        }
    }

    if (playerIndex == 1)
    {
        if (players[0]->getHand()->getHandSize() != 0)
        {
            players[0]->setPlayerTurn(true);
            players[1]->setPlayerTurn(false);
        }
        else if (players[0]->getHand()->getHandSize() == 0)
        {
            players[0]->setPlayerTurn(false);
            players[1]->setPlayerTurn(true);
        }
    }
}

bool GameEngine::isGameFinished()
{
    bool finished = false;
    if ((players[0]->getHand()->getHandSize() == 0 || players[1]->getHand()->getHandSize() == 0) && bag->getBagSize() == 0)
    {
        finished = true;
    }

    return finished;
}

void GameEngine::addPlayer(std::string playerName)
{
    if (playerCount == 0)
    {
        players.push_back(new Player(playerName));
        players[0]->setPlayerTurn(true);
        ++playerCount;
    }
    else
    {
        players.push_back(new Player(playerName));
        ++playerCount;
    }
}

void GameEngine::addPlayer(std::string playerName, Hand *hand, int score, bool isPlayerTurn)
{
    players.push_back(new Player(playerName, hand, score, isPlayerTurn));
    ++playerCount;
}

bool GameEngine::regexVsStringCheck(std::string name, std::string regex)
{
    bool check = false;
    std::regex reg(regex);
    if (std::regex_match(name, reg))
    {
        check = true;
    }

    return check;
}

void GameEngine::setIsNewGame(bool newGame)
{
    this->newGame = newGame;
}

string GameEngine::serialise()
{
    string retVal = string();

    Player *active_player = nullptr;
    for (size_t i = 0; i < players.size(); ++i)
    {
        Player *player = players[i];
        if (player->getIsPlayerTurn())
            active_player = player;
        retVal += player->serialise();
    }

    retVal += board->serialise() + '\n' + bag->getTiles() + '\n' + active_player->getName();
    return retVal;
}

void GameEngine::save(string filename)
{
    SerialisedData save_file = SerialisedData(filename,
                                              SerialisedData::Mode::WRITE);

    string save_contents = serialise();
    char *sc_converted = new char[save_contents.length() + 1];
    std::strcpy(sc_converted, save_contents.c_str());

    save_file.Write(sc_converted, save_contents.length());
    save_file.Flush();
    delete[] sc_converted;
}

void GameEngine::load(string filename)
{
    SerialisedData *save_file = new SerialisedData(filename,
                                                   SerialisedData::Mode::READ);
    save_file->Read();
    stringstream save_stream = stringstream(string(save_file->getData(),
                                                   save_file->getLength()));

    std::vector<Player *> players;
    for (int i = 0; i < 2; ++i)
    {
        string name;
        string points_str;
        string hand_str;
        getline(save_stream, name);
        getline(save_stream, points_str);
        getline(save_stream, hand_str);

        int score = 0;
        stringstream(points_str) >> score;
        Hand *hand = new Hand(hand_str);
        Player *player = new Player(name, hand, score, false);
        players.push_back(player);
    }

    string board_dimensions;
    string board_tiles;
    getline(save_stream, board_dimensions);
    getline(save_stream, board_tiles);
    Board *board = new Board(board_tiles);
    this->board = board;

    string bag_str;
    getline(save_stream, bag_str);
    Bag *bag = new Bag(bag_str);
    this->bag = bag;

    string current_player;
    getline(save_stream, current_player);

    for (size_t i = 0; i < players.size(); ++i)
    {
        Player *player = players[i];
        if (player->isName(current_player))
            player->setPlayerTurn(true);
    }
    this->players = players;
    gameLoaded = true;
    delete save_file;
}

bool GameEngine::validateFile(std::string fileName)
{
    //return value
    bool valid = false;

    if (checkFileExists(fileName) && checkFileFormat(fileName))
    {
        valid = true;
    }

    return valid;
}

bool GameEngine::checkFileExists(std::string fileName)
{
    bool exists = false;
    std::ifstream file;
    file.open(fileName);
    //if the file exists this will return true due to the way ifstream works
    if (file)
    {
        exists = true;
    }

    file.close();
    return exists;
}

bool GameEngine::checkFileFormat(std::string fileName)
{
    //RETURN VALUE
    bool correctFormat = false;
    //regex used for checking the format of the file
    std::regex fileRegex(FILE_FORMAT_REGEX);
    //string used for reading from the file
    std::string fileRead = string();
    //the final string
    std::string format = string();
    //file we are reading from
    std::ifstream file(fileName);

    //reads each line of the file and puts it into a string
    while (std::getline(file, fileRead))
    {
        format += fileRead + "\n";
    }

    //cleans up the string by removing \n from the last line
    format.erase(std::remove(format.end() - 1, format.end(), '\n'), format.end());

    //simple check for making sure the fileformat matches the spec
    if (std::regex_match(format, fileRegex))
    {
        correctFormat = true;
    }

    file.close();

    return correctFormat;
}

void GameEngine::startGame()
{
    bag = new Bag();
    bag->initializeTiles();
    for (int i = 0; i < MAX_PLAYERS; ++i)
    {
        for (int m = 0; m < MAX_HAND_SIZE; ++m)
        {
            players[i]->getHand()->addTile(bag->getFront());
        }
    }
}

int GameEngine::getPlayerSize()
{
    return players.size();
}