#pragma once

#include "Table.h"
#include <windows.h>

void displayTable(const Table& table, int currentRow, int currentCol);
void handleInput(Table& table, int& currentRow, int& currentCol);
void gotoXY(int x, int y);
void setColor(int color);
void resetColor();
void printCell(const Table& table, int row, int col, bool highlight);