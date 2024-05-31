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

    table.setCellValue("R2C1", "2");
    table.setCellValue("R3C1", "3");
    table.setCellValue("R4C1", "4.455");
    Sleep(1000);
    table.setCellValue("R5C1", "Azis");
    table.setCellValue("R6C1", "Galena");

    table.setCellValue("R1C1", "=R2C1+R3C1");
    table.setCellValue("R2C2", "=R2C1*R4C1");
    table.setCellValue("R3C2", "=R1C1-R2C1");
    table.setCellValue("R4C2", "=R1C1/R3C1");
    table.setCellValue("R5C2", "=R2C1^R3C1");

    table.handleInput();
}


