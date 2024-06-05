#pragma once
#include "MenuOption.h"
#include <windows.h> 
#include <iostream>

class Menu
{
private:
    MenuOption* options;
    int optionCount;
    int selectedOption;
    HANDLE consoleHandle;
    COORD initialCursorPosition;

    void moveTo(int x, int y) const;
    void clearLine(int line) const;


public:
    Menu(const MenuOption options[], int optionCount);
    ~Menu();

    void setOption(int index, MenuOption option);
    void printMenu() const;
    void highlightSelectedOption() const;
    void handleChosenOption() const;
    void navigateUp();
    void navigateDown();
};
