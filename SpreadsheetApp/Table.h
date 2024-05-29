#include "Cell.h"
#include <windows.h>

class Table 
{
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

    int calculateMaxCellWidth() const;
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void gotoXY(int x, int y) const;
    void printSelectedCellValue() const;
};

