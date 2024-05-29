#pragma once
#include <windows.h>

class WinConsoleApi 
{
public:
    static void gotoXY(int x, int y);

private:
    static const int DEFAULT_COLOR = 7;
};

