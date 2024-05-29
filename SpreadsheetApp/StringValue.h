#pragma once
#include <iostream>
#include "CellValue.h"

class StringValue : public CellValue 
{
private:
    std::string value;
public:
    StringValue(std::string value);
    std::string toString() const override;
    CellValue* clone() const override;
    ValueType getType() const override;
};

