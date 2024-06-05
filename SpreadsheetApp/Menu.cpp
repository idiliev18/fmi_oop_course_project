#include "Menu.h"
#include <conio.h>

Menu::Menu(const MenuOption options[], int optionCount)
    : optionCount(optionCount), selectedOption(0) 
{
    this->options = new MenuOption[optionCount];
    for (int i = 0; i < optionCount; i++) 
    {
        this->options[i] = options[i];
    }
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(consoleHandle, &csbi);
    initialCursorPosition = csbi.dwCursorPosition;
}

Menu::~Menu() 
{
    delete[] options;
}

void Menu::setOption(int index, MenuOption option) 
{
    if (index >= 0 && index < optionCount) 
    {
        options[index] = option;
    }
}

void Menu::moveTo(int x, int y) const
{
    COORD position = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(consoleHandle, position);
}

void Menu::clearLine(int line) const 
{
    moveTo(0, line);
    std::cout << std::string(80, ' ');
    moveTo(0, line);
}

void Menu::printMenu() const 
{
    system("cls"); 
    for (int i = 0; i < optionCount; i++) 
    {
        moveTo(initialCursorPosition.X, initialCursorPosition.Y + i);
        if (i == selectedOption) 
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            std::cout << "> " << options[i].getText() << std::endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else 
        {
            std::cout << "  " << options[i].getText() << std::endl;
        }
    }
}

void Menu::highlightSelectedOption() const 
{
    for (int i = 0; i < optionCount; i++) 
    {
        moveTo(initialCursorPosition.X, initialCursorPosition.Y + i);
        if (i == selectedOption)
        {
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            std::cout << "> " << options[i].getText() << std::endl;
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        } else 
        {
            std::cout << "  " << options[i].getText() << std::endl;
        }
    }
}

void Menu::handleChosenOption() const
{
    if (selectedOption >= 0 && selectedOption < optionCount)
    {
        options[selectedOption].executeAction();
    }
}

void Menu::navigateUp() 
{
    if (selectedOption > 0) 
    {
        --selectedOption;
    } else {
        selectedOption = optionCount - 1; 
    }
    highlightSelectedOption();
}

void Menu::navigateDown() 
{
    if (selectedOption < optionCount - 1) 
    {
        ++selectedOption;
    } else 
    {
        selectedOption = 0; 
    }
    highlightSelectedOption();
}



