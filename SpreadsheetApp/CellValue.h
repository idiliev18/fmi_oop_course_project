#pragma once
#include "enums.h"
#include <iostream>

class CellValue
{
public:
    virtual ~CellValue() {}
    virtual std::string toString() const = 0;
    virtual CellValue* clone() const = 0;
    virtual ValueType getType() const = 0;
};
