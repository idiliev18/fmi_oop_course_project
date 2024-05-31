#ifndef TABLE_H
#define TABLE_H

#include "Cell.h"
#include <windows.h>
#include <string>
#include <utility>

class Table {
public:
    Table(int width, int height);
    ~Table();

    int getWidth() const;
    int getHeight() const;
    Cell& getCell(int row, int col);
    const Cell& getCell(int row, int col) const;
    void setCellValue(const std::string& address, const std::string& value);
    void clearCellValue(const std::string& address);
    bool isInteger(const std::string& str) const;
    bool isDouble(const std::string& str) const;
    void print() const;
    void handleInput();

private:
    int width;
    int height;
    Cell** cells;
    int currentRow;
    int currentCol;
    bool inEditMode;

    int calculateMaxCellWidth() const;
    int getMaxCellValueLength() const;
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void gotoXY(int x, int y) const;
    void printSelectedCellValue() const;
    void printCell(int row, int col, bool highlight) const;
    void toggleMode();
    void handleEditMode();
    void updateCell(int row, int col, bool highlight) const;
    void clearLine(int y) const;
    void clearScreen() const;

    
    std::pair<int, int> parseAddress(const std::string& address) const;
};

#endif // TABLE_H
