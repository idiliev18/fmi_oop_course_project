
#include "Cell.h"
#include <windows.h>

class Table {
public:
    Table(int width, int height);
    ~Table();

    int getWidth() const;
    int getHeight() const;
    Cell& getCell(int row, int col);
    const Cell& getCell(int row, int col) const;

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
};

