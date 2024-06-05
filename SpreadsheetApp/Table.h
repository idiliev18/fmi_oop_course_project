#include "Cell.h"
#include <windows.h>
#include <string>
#include <fstream>

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
    void init();
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    bool isFileLoaded() const;
    void setFileLoaded(bool loaded);
    const std::string& getCurrentFilePath() const;
    void setCurrentFilePath(const std::string& path);
    void clear();
    std::pair<int, int> parseAddress(const std::string& address) const; 

private:
    int width;
    int height;
    Cell** cells;
    int currentRow;
    int currentCol;
    bool inEditMode;
    bool fileLoaded;
    std::string currentFilePath;

    void resizeTable(int newWidth, int newHeight);
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
};

