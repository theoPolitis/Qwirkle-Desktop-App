#include "Menu.h"

#include <iostream>

//CONSTRUCTOR
Menu::Menu()
{
    gameEngine = new GameEngine();
}

Menu::~Menu()
{
    delete gameEngine;
}

void Menu::run()
{
    // Display text welcome and show the prompts
    displayWelcome();
    displayPrompts();
}

void Menu::displayPrompts()
{
    std::string input = "";
    bool quit = false;

    printMenu();
    while (!quit)
    {

        std::cout << "> ";
        std::getline(std::cin, input);

        // if (input.substr(0,1) == "1" && input.length() == 2)
        if (input == "1")
        { // New game
            newGame();
            quit = true;
        }
        else if (input == "2")
        { // Load game
            loadGame();
            quit = true;
        }
        else if (input == "3")
        { // Load credits
            printCredits();
            printMenu();
        }
        else if (input == "4")
        {
            quitGame();
            quit = true;
        }
        else if (std::cin.eof())
        {
            printEOF();
            quit = true;
        }
        else
        {
            std::cout << "Invalid Input" << std::endl;
            std::cout << input << std::endl;
            std::cout << "Input length: " << input.length() << std::endl;
        }
    }
}

// Create a new game with 2 players
void Menu::newGame()
{

    std::string name;

    std::cout << "Starting a New Game" << std::endl;
    std::cout << std::endl;

    // Get info for up to MAX_PLAYERS
    while (gameEngine->getPlayerSize() < MAX_PLAYERS && !std::cin.eof())
    {
        std::string playerName;
        std::cout << "Enter a name for player " << gameEngine->getPlayerSize() + 1 << " (uppercase charcters only)" << std::endl;

        while (!validateName(playerName) && !std::cin.eof())
        {
            std::cout << "> ";
            std::getline(std::cin, playerName);
            if (!validateName(playerName) && !std::cin.eof()){
                std::cout << "Invalid input" << std::endl;
            }
        }
        gameEngine->addPlayer(playerName);
    }
    if (!std::cin.eof())
    {
        std::cout << std::endl;
        std::cout << "Let's play!" << std::endl;
        gameEngine->setIsNewGame(true);
        gameEngine->run();
    }
    else
    {
        printEOF();
    }
}

void Menu::loadGame()
{
    std::string fileName = string();

    std::cout << "Enter the filename from which load a game" << std::endl;
    std::cout << "> ";

    std::getline(std::cin, fileName);

    while (!gameEngine->validateFile(fileName) && !std::cin.eof())
    {
        std::cout << "Invalid Input" << std::endl;
        std::cout << "> ";
        std::getline(std::cin, fileName);
    }

    if (std::cin.eof())
    {
        printEOF();
    }
    else
    {
        gameEngine->load(fileName);
        gameEngine->run();
    }
}

bool Menu::validateName(std::string name)
{
    bool validName = false;
    std::regex reg(NAME_REGEX);
    if (std::regex_match(name, reg))
    {
        validName = true;
    }

    return validName;
}

void Menu::displayWelcome()
{
    std::cout << "Welcome to Qwirkle!" << std::endl;
    std::cout << "-------------------" << std::endl;
}

void Menu::printCredits()
{
    std::cout << "-----------------------------------" << std::endl;
    formatStudentInfo("Jason Song", "s3744335",
                      "s3744335@student.rmit.edu.au");
    formatStudentInfo("Jared Song", "s3857657",
                      "s3857657@student.rmit.edu.au");
    formatStudentInfo("Theodore Politis", "s3661671",
                      "s3661671@student.rmit.edu.au");
    formatStudentInfo("Jonathon Tripodi", "s3784782",
                      "s3784782@student.rmit.edu.au");
    std::cout << "-----------------------------------" << std::endl;
}

void Menu::formatStudentInfo(std::string name, std::string studentId, std::string email)
{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Student ID: " << studentId << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << std::endl;
}

void Menu::quitGame()
{
    printGoodbye();
}

void Menu::printMenu()
{
    std::cout << "Menu" << std::endl;
    std::cout << "----" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Credits (Show student information)" << std::endl;
    std::cout << "4. Quit" << std::endl;
}


void Menu::printEOF() 
{
    std::cout << "^D" << std::endl;
    printGoodbye();
}

void Menu::printGoodbye() 
{
    std::cout << std::endl;
    std::cout << "Goodbye" << std::endl;
}