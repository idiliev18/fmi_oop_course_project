#pragma once
#include <iostream>
#include <string>
#include "..\SpreadsheetApp\CellValue.h"
#include "Date.h"

class Cell 
{
public:
    CellValue* cellValue;  
    std::string address;   
    Date lastModifiedDate;

    Cell();
    ~Cell();
    Cell(const Cell& other);
    Cell& operator=(const Cell& other);
};

