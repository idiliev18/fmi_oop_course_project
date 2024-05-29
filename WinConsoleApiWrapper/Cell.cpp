#include "Cell.h"

Cell::Cell()
{
    cellValue = nullptr;
}

Cell::~Cell()
{
    delete cellValue;
}

Cell::Cell(const Cell& other)
{
    cellValue = other.cellValue ? other.cellValue->clone() : nullptr;
    address = other.address;
    lastModifiedDate = other.lastModifiedDate;
}

Cell& Cell::operator=(const Cell& other)
{
    if (this != &other)
    {
        delete cellValue;
        cellValue = other.cellValue ? other.cellValue->clone() : nullptr;
        address = other.address;
        lastModifiedDate = other.lastModifiedDate;
    }
    return *this;
}
