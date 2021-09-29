#ifndef ASSIGN2_MENU_H
#define ASSIGN2_MENU_H
#include "GameEngine.h"
#include <regex>
#include "Exceptions.h"

// This is the menu

class Menu
{
public:
    Menu();
    ~Menu();

    void run();

private:
    // Display the welcome message
    void displayWelcome();

    // Display the prompts
    void displayPrompts();

    // Grab input from user
    int getInput();

    // Display the menu options
    void printMenu();

    // Create a new game
    void newGame();

    // Load an existing game from file
    void loadGame();

    // Format the student info
    void formatStudentInfo(std::string name, std::string studentId, std::string email);

    // Display the credits
    void printCredits();

    // Display exiting of the game
    void quitGame();

    // Display EOF character and quit
    void printEOF();

    // Display goodbye message
    void printGoodbye();

    bool validateName(std::string name);
    GameEngine *gameEngine;

    // My version
    void handleTest();
};

#endif //ASSIGN2_MENU_H