#include "Table.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <conio.h>

const int MAX_CELL_DISPLAY_WIDTH = 13;

Table::Table(int width, int height) : width(width), height(height), currentRow(0), currentCol(0)
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
        // error
    }
    return cells[row][col];
}

const Cell& Table::getCell(int row, int col) const {
    if (row < 0 || row >= height || col < 0 || col >= width) 
    {
       // error
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

void Table::print() const 
{
    int cellWidth = calculateMaxCellWidth() + 2;

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
            int paddingLeft = (cellWidth - valueStr.length()) / 2;
            int paddingRight = cellWidth - valueStr.length() - paddingLeft;
            std::cout << "|" << std::string(paddingLeft, ' ') << valueStr << std::string(paddingRight, ' ');
        }
        std::cout << "|" << std::endl;
        for (int col = 0; col < width; col++) 
        {
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
            switch (_getch()) 
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
        }
        else if (key == 27)
        {  // Escape key
            break; 
        }
        printSelectedCellValue();
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

    gotoXY(x, y);
    std::cout << "Selected Cell [" << currentRow << "][" << currentCol << "]: ";
    if (getCell(currentRow, currentCol).cellValue) 
    {
        std::cout << getCell(currentRow, currentCol).cellValue->toString() << "                                        ";
    }
    else 
    {
        std::cout << "Empty                                               "; 
    }
}
