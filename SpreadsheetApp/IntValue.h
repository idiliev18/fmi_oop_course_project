#pragma once
#include <iostream>
#include "CellValue.h"

class IntValue : public CellValue 
{
private:
    int value;
public:
    IntValue(int value);
    std::string toString() const override;
    CellValue* clone() const override;
    ValueType getType() const override;
};

