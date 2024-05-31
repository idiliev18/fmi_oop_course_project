#include "Table.h"
#include "IntValue.h"
#include "DoubleValue.h"
#include "StringValue.h"
#include "Date.h"

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <conio.h>
#include <sstream>
#include <cctype>

const int MAX_CELL_DISPLAY_WIDTH = 13;

Table::Table(int width, int height) : width(width), height(height), currentRow(0), currentCol(0), inEditMode(false)
{
    cells = new Cell * [height];
    for (int i = 0; i < height; i++)
    {
        cells[i] = new Cell[width];
    }
}

Table::~Table()
{
    for (int i = 0; i < height; i++)
    {
        delete[] cells[i];
    }
    delete[] cells;
}

int Table::getWidth() const
{
    return width;
}

int Table::getHeight() const
{
    return height;
}

Cell& Table::getCell(int row, int col)
{
    if (row < 0 || row >= height || col < 0 || col >= width)
    {
        throw std::out_of_range("Cell index out of range");
    }
    return cells[row][col];
}

const Cell& Table::getCell(int row, int col) const {
    if (row < 0 || row >= height || col < 0 || col >= width)
    {
        throw std::out_of_range("Cell index out of range");
    }
    return cells[row][col];
}

int Table::calculateMaxCellWidth() const
{
    int maxWidth = 0;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            const Cell& cell = cells[row][col];
            std::string valueStr = cell.cellValue ? cell.cellValue->toString() : "";
            if (valueStr.length() > MAX_CELL_DISPLAY_WIDTH)
            {
                valueStr = valueStr.substr(0, 12) + "...";
            }
            maxWidth = std::max<int>(maxWidth, static_cast<int>(valueStr.length()));
        }
    }
    return maxWidth;
}

int Table::getMaxCellValueLength() const 
{
    int maxLength = 0;
    for (int row = 0; row < height; row++) 
    {
        for (int col = 0; col < width; col++) 
        {
            const Cell& cell = cells[row][col];
            if (cell.cellValue)
            {
                maxLength = std::max<int>(maxLength, static_cast<int>(cell.cellValue->toString().length()));
            }
        }
    }
    return maxLength;
}

void Table::print() const 
{
    clearScreen();
    int cellWidth = calculateMaxCellWidth() + 2;

    std::cout << "     ";
    for (int col = 0; col < width; col++) 
    {
        std::string colHeader = "C" + std::to_string(col + 1);
        int paddingLeft = (cellWidth - colHeader.length()) / 2;
        int paddingRight = cellWidth - colHeader.length() - paddingLeft;
        std::cout << "|" << std::string(paddingLeft, ' ') << colHeader << std::string(paddingRight, ' ');
    }
    std::cout << "|" << std::endl;

    std::cout << "     "; 
    for (int col = 0; col < width; col++) {
        std::cout << "+" << std::setw(cellWidth) << std::setfill('-') << "-";
    }
    std::cout << "+" << std::setfill(' ') << std::endl;

    for (int row = 0; row < height; row++) 
    {
        std::string rowHeader = "R" + std::to_string(row + 1);
        std::cout << std::setw(4) << std::right << rowHeader << " "; 

        for (int col = 0; col < width; col++) {
            printCell(row, col, row == currentRow && col == currentCol);
        }
        std::cout << "|" << std::endl;
       
        std::cout << "     ";
        for (int col = 0; col < width; col++) {
            std::cout << "+" << std::setw(cellWidth) << std::setfill('-') << "-";
        }
        std::cout << "+" << std::setfill(' ') << std::endl;
    }
}

void Table::handleInput()
{
    print();
    printSelectedCellValue();
    while (true)
    {
        int key = _getch();

        if (key == 224)
        {
            if (!inEditMode)
            {
                int arrowKey = _getch();
                int prevRow = currentRow;
                int prevCol = currentCol;
                switch (arrowKey)
                {
                case 72:  // Up arrow
                    moveUp();
                    break;
                case 80:  // Down arrow
                    moveDown();
                    break;
                case 75:  // Left arrow
                    moveLeft();
                    break;
                case 77:  // Right arrow
                    moveRight();
                    break;
                }

                updateCell(prevRow, prevCol, false);
                updateCell(currentRow, currentCol, true);
                printSelectedCellValue();
            }
        }
        else if (key == 27)
        {
            break;
        }
        else if (key == 5)
        {  // Ctrl + E
            toggleMode();
        }
        else if (inEditMode)
        {
            handleEditMode();
        }
    }
}

void Table::moveUp()
{
    if (currentRow > 0) currentRow--;
}

void Table::moveDown()
{
    if (currentRow < height - 1) currentRow++;
}

void Table::moveLeft()
{
    if (currentCol > 0) currentCol--;
}

void Table::moveRight()
{
    if (currentCol < width - 1) currentCol++;
}

void Table::gotoXY(int x, int y) const 
{
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Table::printSelectedCellValue() const 
{
    int x = 0;
    int y = height * 2 + 2;

    const Cell& cell = getCell(currentRow, currentCol);
    std::string valueStr = cell.cellValue ? cell.cellValue->toString() : "......";
    std::string typeStr;
    switch (cell.cellValue ? cell.cellValue->getType() : ValueType::NONE) {
    case ValueType::INT:
        typeStr = "INT";
        break;
    case ValueType::DOUBLE:
        typeStr = "DOUBLE";
        break;
    case ValueType::STRING:
        typeStr = "STRING";
        break;
    case ValueType::FORMULA:
        typeStr = "FORMULA";
        break;
    default:
        typeStr = "......";
        break;
    }
    std::string dateStr = cell.lastModifiedDate.toString();

    int maxCellWidth = getMaxCellValueLength();
    int cellDetailWidth = std::max<int>({ maxCellWidth, static_cast<int>(valueStr.length()), static_cast<int>(typeStr.length()), static_cast<int>(dateStr.length()) }) + 12; // Add padding for labels and spaces

    gotoXY(x, y);
    std::cout << "                             ---Cell R" << (currentRow + 1) << "C" << (currentCol + 1) << "---      \n";
    gotoXY(x, y + 1);
    std::cout << "     | Value        : " << std::setw(cellDetailWidth) << std::left << valueStr << "|\n";
    gotoXY(x, y + 2);
    std::cout << "     | Type         : " << std::setw(cellDetailWidth) << std::left << typeStr << "|\n";
    gotoXY(x, y + 3);
    std::cout << "     | LastModified : " << std::setw(cellDetailWidth) << std::left << dateStr << "|\n";
    gotoXY(x, y + 4);
    std::cout << "      " << std::string(cellDetailWidth + 17, '-') << "      \n";
}

void Table::printCell(int row, int col, bool highlight) const
{
    const Cell& cell = getCell(row, col);
    
    std::string valueStr = cell.cellValue ? cell.cellValue->toString() : "";
    if (valueStr.length() > MAX_CELL_DISPLAY_WIDTH)
    {
        valueStr = valueStr.substr(0, 12) + "...";
    }

    int cellWidth = calculateMaxCellWidth() + 2;
    int paddingLeft = (cellWidth - valueStr.length()) / 2;
    int paddingRight = cellWidth - valueStr.length() - paddingLeft;

    if (highlight)
    {
        std::cout << "\033[7m";
    }
    std::cout << "|" << std::string(paddingLeft, ' ') << valueStr << std::string(paddingRight, ' ');

    if (highlight)
    {
        std::cout << "\033[0m";
    }
}

void Table::toggleMode()
{
    inEditMode = !inEditMode;
    int editLineY = height * 2 + 7;
    if (inEditMode)
    {
        clearLine(editLineY);
        gotoXY(0, editLineY);
        std::cout << "Edit mode: ";
        gotoXY(11, editLineY);
    }
    else
    {
        clearLine(editLineY);
        print();
        printSelectedCellValue();
    }
}

void Table::clearCellValue(const std::string& address)
{
    std::pair<int, int> addressPair = parseAddress(address);
    int row = addressPair.first;
    int col = addressPair.second;

    if (row < 0 || row >= height || col < 0 || col >= width)
    {
        throw std::out_of_range("Cell index out of range");
    }

    Cell& cell = cells[row][col];
    delete cell.cellValue;
    cell.cellValue = nullptr;
    cell.lastModifiedDate = Date();
}


void Table::handleEditMode()
{
    int editLineY = height * 2 + 7;

    while (true) 
    {
        gotoXY(11, editLineY);
        std::cout.flush();

        std::string input;
        std::getline(std::cin, input);
 
        clearLine(editLineY);
        gotoXY(0, editLineY);
        std::cout << "Edit mode: ";
        gotoXY(11, editLineY);

        std::istringstream iss(input);
        std::string command, cellAddress, value;

        iss >> command >> cellAddress;
        std::getline(iss, value);
        if (!value.empty() && value[0] == ' ') 
        {
            value.erase(0, 1);
        }

        bool commandSuccess = false;

        if (command == "Edit" && !cellAddress.empty() && !value.empty()) {
            try {
                setCellValue(cellAddress, value);
                commandSuccess = true;
            }
            catch (const std::exception& e) 
            {
                gotoXY(0, editLineY + 1);
                std::cout << "\033[41m" << "Error: " << e.what() << "\033[0m" << std::endl;
            }
        }
        else if (command == "Clear" && !cellAddress.empty()) 
        {
            try 
            {
                clearCellValue(cellAddress);
                commandSuccess = true;
            }
            catch (const std::exception& e) 
            {
                gotoXY(0, editLineY + 1); 
                std::cout << "\033[41m" << "Error: " << e.what() << "\033[0m" << std::endl; 
            }
        }
        else 
        {
            gotoXY(0, editLineY + 1);
            std::cout << "\033[41m" << "Invalid command format. Use: Edit <cellAddress> <value> or Clear <cellAddress>" << "\033[0m" << std::endl; // Red background
        }


        if (commandSuccess)
        {
            break;
        }

    }
    
    inEditMode = false;
    print();
    printSelectedCellValue();
}


void Table::updateCell(int row, int col, bool highlight) const 
{
    int cellWidth = calculateMaxCellWidth() + 2;

    int x = col * (cellWidth + 1) + 5; 
    int y = row * 2 + 2;

    gotoXY(x, y);
    printCell(row, col, highlight);

    gotoXY(x + cellWidth, y);
}

void Table::clearLine(int y) const
{
    gotoXY(0, y);
    std::cout << std::string(80, ' ');
    gotoXY(0, y);
}

void Table::clearScreen() const
{
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    DWORD consoleSize = screen.dwSize.X * screen.dwSize.Y;

    FillConsoleOutputCharacterA(console, ' ', consoleSize, topLeft, &written);
    FillConsoleOutputAttribute(console, screen.wAttributes, consoleSize, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

bool Table::isInteger(const std::string& str) const 
{
    std::istringstream iss(str);
    int val;
    iss >> std::noskipws >> val;
    return iss.eof() && !iss.fail();
}

bool Table::isDouble(const std::string& str) const 
{
    std::istringstream iss(str);
    double val;
    iss >> std::noskipws >> val;
    return iss.eof() && !iss.fail();
}

std::pair<int, int> Table::parseAddress(const std::string& address) const 
{
    if (address.size() < 4 || address[0] != 'R' || address[2] != 'C' || !std::isdigit(address[1]) || !std::isdigit(address[3])) 
    {
        // error
    }
    int row = std::stoi(address.substr(1, address.find('C') - 1)) - 1;
    int col = std::stoi(address.substr(address.find('C') + 1)) - 1;
    return { row, col };
}

void Table::setCellValue(const std::string& address, const std::string& value)
{
    std::pair<int, int> addressPair = parseAddress(address);
    int row = addressPair.first;
    int col = addressPair.second;

    if (row < 0 || row >= height || col < 0 || col >= width)
    {
        throw std::out_of_range("Cell index out of range");
    }

    Cell& cell = cells[row][col];

    delete cell.cellValue;

    
    if (isInteger(value))
    {
        cell.cellValue = new IntValue(std::stoi(value));
    }
    else if (isDouble(value))
    {
        cell.cellValue = new DoubleValue(std::stod(value));
    }
    else
    {
        cell.cellValue = new StringValue(value);
    }

    cell.lastModifiedDate = Date();
}
