#pragma once
#include <iostream>
#include "CellValue.h"

class DoubleValue : public CellValue 
{
private:
    double value;
public:
    DoubleValue(double value);
    std::string toString() const override;
    CellValue* clone() const override;
    ValueType getType() const override;
};
