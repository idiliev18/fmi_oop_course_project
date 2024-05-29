#include "IntValue.h"
#include <iostream>
#include <string>


IntValue::IntValue(int value)
{
    this->value = value;
}

std::string IntValue::toString() const 
{
    return std::to_string(value);
}

CellValue* IntValue::clone() const 
{
    return new IntValue(*this);
}

ValueType IntValue::getType() const
{
    return ValueType::INT;
}

