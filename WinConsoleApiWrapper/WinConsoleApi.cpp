#include "WinConsoleApi.h"

void WinConsoleApi::gotoXY(int x, int y) 
{
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
