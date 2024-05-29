#include "Table.h"
#include "IntValue.h"
#include "DoubleValue.h"
#include "StringValue.h"

int main() 
{
    Table table(6, 10);

    table.getCell(0, 0).cellValue = new IntValue(42);
    table.getCell(0, 1).cellValue = new DoubleValue(3.14159);
    table.getCell(0, 2).cellValue = new StringValue("PRESLAVAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");

    table.handleInput();
}
