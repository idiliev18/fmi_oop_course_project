#include "Table.h"
#include "IntValue.h"
#include "DoubleValue.h"
#include "StringValue.h"
#include <iostream>
#include <windows.h>
using namespace std;

int main() 
{
    Table table(6, 10);

    table.setCellValue("R2C1", "Kondidddddddddddddddddddddddddo");
    table.setCellValue("R3C1", "2");
    table.setCellValue("R4C1", "4.455");
    Sleep(1000);
    table.setCellValue("R5C1", "Azis");
    table.setCellValue("R6C1", "Galena");

    table.handleInput();
}

