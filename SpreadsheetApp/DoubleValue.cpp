#include "DoubleValue.h"
#include <string>

DoubleValue::DoubleValue(double value)
{
    this->value = value;
}

std::string DoubleValue::toString() const
{
    return std::to_string(value);
}

CellValue* DoubleValue::clone() const
{
    return new DoubleValue(*this);
}

ValueType DoubleValue::getType() const
{
    return ValueType::DOUBLE;
}

double DoubleValue::getValue() const 
{
    return value;
}
