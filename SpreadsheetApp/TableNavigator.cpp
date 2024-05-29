#include "TableNavigator.h"
#include <iostream>
#include <conio.h>

const int MAX_CELL_DISPLAY_WIDTH = 13;
const int DEFAULT_COLOR = 7;
const int HIGHLIGHT_COLOR = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

void displayTable(const Table& table, int currentRow, int currentCol) {
    system("cls");  // Clear the console
    for (int row = 0; row < table.getHeight(); ++row) {
        for (int col = 0; col < table.getWidth(); ++col) {
            printCell(table, row, col, row == currentRow && col == currentCol);
        }
        std::cout << "|" << std::endl;
        for (int col = 0; col < table.getWidth(); ++col) {
            std::cout << "+----------"; // Match the width set above
        }
        std::cout << "+" << std::endl;
    }
    gotoXY(0, table.getHeight() * 2 + 2); // Position below the table
    std::cout << "Selected Cell [" << currentRow << "][" << currentCol << "]: ";
    if (table.getCell(currentRow, currentCol).cellValue) {
        std::cout << table.getCell(currentRow, currentCol).cellValue->toString() << "          "; // Extra spaces to clear previous content
    }
    else {
        std::cout << "Empty                "; // Extra spaces to clear previous content
    }
}

void handleInput(Table& table, int& currentRow, int& currentCol) {
    displayTable(table, currentRow, currentCol);
    while (true) {
        int key = _getch();  // Get the key pressed

        if (key == 224) {  // Special keys (arrows, function keys, etc.)
            switch (_getch()) {
            case 72:  // Up arrow
                if (currentRow > 0) currentRow--;
                break;
            case 80:  // Down arrow
                if (currentRow < table.getHeight() - 1) currentRow++;
                break;
            case 75:  // Left arrow
                if (currentCol > 0) currentCol--;
                break;
            case 77:  // Right arrow
                if (currentCol < table.getWidth() - 1) currentCol++;
                break;
            }
        }
        else if (key == 27) {  // Escape key
            break;  // Exit the loop
        }
        displayTable(table, currentRow, currentCol);
    }
}

void gotoXY(int x, int y) {
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_COLOR); // 7 is the default console color
}

void printCell(const Table& table, int row, int col, bool highlight) {
    const Cell& cell = table.getCell(row, col);
    std::string valueStr = cell.cellValue ? cell.cellValue->toString() : "";
    if (valueStr.length() > MAX_CELL_DISPLAY_WIDTH) {
        valueStr = valueStr.substr(0, 12) + "...";
    }

    int paddingLeft = (10 - valueStr.length()) / 2;
    int paddingRight = 10 - valueStr.length() - paddingLeft;

    std::cout << "|";
    if (highlight) {
        setColor(HIGHLIGHT_COLOR);
    }
    std::cout << std::string(paddingLeft, ' ') << valueStr << std::string(paddingRight, ' ');
    if (highlight) {
        resetColor();
    }
}
