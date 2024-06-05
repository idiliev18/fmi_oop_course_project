#include <iostream>
#include <fstream>
#include <conio.h> 
#include "Menu.h"
#include "MenuOption.h"
#include "Table.h"

void openAction(Table& table) 
{
    std::cout << "Enter filename to open: ";
    std::string filename;
    std::cin >> filename;

    std::ifstream infile(filename);
    if (!infile) 
    {
        std::ofstream outfile(filename);
        if (!outfile) 
        {
            std::cout << "Error creating file: " << filename << std::endl;
            return;
        }
        std::cout << "Created new file: " << filename << std::endl;
        outfile.close();
    }
    else 
    {
        try 
        {
            table.loadFromFile(filename);
            std::cout << "Successfully opened " << filename << std::endl;
        }
        catch (const std::exception& e) 
        {
            std::cout << "Error loading file: " << e.what() << std::endl;
        }
    }

    table.setFileLoaded(true);
    table.setCurrentFilePath(filename);
}

void closeAction(Table& table)
{
    if (!table.isFileLoaded()) 
    {
        std::cout << "No file is loaded. Please open a file first." << std::endl;
        return;
    }
    table.clear();
    table.setFileLoaded(false);
    std::cout << "Successfully closed " << table.getCurrentFilePath() << std::endl;
}

void saveAction(Table& table)
{
    if (!table.isFileLoaded()) 
    {
        std::cout << "No file is loaded. Please open a file first." << std::endl;
        return;
    }
    try 
    {
        table.saveToFile(table.getCurrentFilePath());
        std::cout << "File saved successfully!" << std::endl;
    }
    catch (const std::exception& e) 
    {
        std::cout << "Error saving file: " << e.what() << std::endl;
    }
}

void saveAsAction(Table& table) 
{
    if (!table.isFileLoaded())
    {
        std::cout << "No file is loaded. Please open a file first." << std::endl;
        return;
    }
    std::cout << "Enter filename to save as: ";
    std::string filename;
    std::cin >> filename;
    try 
    {
        table.saveToFile(filename);
        std::cout << "File saved successfully!" << std::endl;
    }
    catch (const std::exception& e) 
    {
        std::cout << "Error saving file: " << e.what() << std::endl;
    }
}

void helpAction() 
{
    std::cout << "The following commands are supported:\n";
    std::cout << "1. open <file>\t\tOpens <file>. If the file doesn't exist, a new file with the specified name is created.\n";
    std::cout << "2. close\t\t\tCloses the currently opened file. Clears the current table data.\n";
    std::cout << "3. save\t\t\tSaves the currently open file.\n";
    std::cout << "4. save as <file>\tSaves the currently open file with a new name specified by <file>.\n";
    std::cout << "5. print\t\t\tPrints the content of the currently loaded table.\n";
    std::cout << "6. edit\t\t\tAllows you to edit a specific cell in the table. Syntax: Edit <cellAddress> <value> (e.g., Edit R1C1 42).\n";
    std::cout << "7. clear\t\t\tClears the value of a specific cell in the table. Syntax: Clear <cellAddress> (e.g., Clear R1C1).\n";
    std::cout << "8. help\t\t\tPrints this help information.\n";
    std::cout << "9. exit\t\t\tExits the program.\n\n";

    std::cout << "Edit Mode Commands:\n";
    std::cout << "Edit <cellAddress> <value>\tEdits the cell at the specified address with the given value. (e.g., Edit R1C1 42)\n";
    std::cout << "Clear <cellAddress>\t\tClears the value of the cell at the specified address. (e.g., Clear R1C1)\n";
}

void exitAction() 
{
    std::cout << "Exiting the application..." << std::endl;
    exit(0);
}

void printAction(Table& table) 
{
    if (!table.isFileLoaded()) 
    {
        std::cout << "No file is loaded. Please open a file first." << std::endl;
        return;
    }
    table.print();
}

void editAction(Table& table)
{
    if (!table.isFileLoaded())
    {
        std::cout << "No file is loaded. Please open a file first." << std::endl;
        return;
    }
    table.print();
    table.handleInput();
}

int main()
{
    Table myTable(6, 10);

    MenuOption options[] = 
    {
        MenuOption("Open", 1, [&myTable]() { openAction(myTable); }),
        MenuOption("Close", 2, [&myTable]() { closeAction(myTable); }),
        MenuOption("Save", 3, [&myTable]() { saveAction(myTable); }),
        MenuOption("Save As", 4, [&myTable]() { saveAsAction(myTable); }),
        MenuOption("Print", 5, [&myTable]() { printAction(myTable); }),
        MenuOption("Edit", 6, [&myTable]() { editAction(myTable); }),
        MenuOption("Help", 7, helpAction),
        MenuOption("Exit", 8, exitAction)
    };

    Menu menu(options, sizeof(options) / sizeof(MenuOption));

    std::cout << "Welcome to the Application!" << std::endl;
    std::cout << "Please select an option from the menu below:" << std::endl;

    while (true) 
    {
        std::cout << "\nPress ESC to go back\n"; 
        menu.printMenu();
        int key = _getch();
        if (key == 224)
        {  
            switch (_getch()) 
            {
            case 72: 
                menu.navigateUp();
                break;
            case 80: 
                menu.navigateDown();
                break;
            }
        }
        else if (key == 13) 
        {  
            menu.handleChosenOption();
            if (key != 27) 
            { 
                std::cout << "\nPress ESC to go back\n";
                while (true) 
                {
                    if (_getch() == 27) 
                    {  
                        break;
                    }
                }
            }
        }
        else if (key == 27) 
        { 
            break;
        }
    }

    return 0;
}
