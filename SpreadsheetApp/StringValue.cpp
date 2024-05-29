#include "StringValue.h"

StringValue::StringValue(std::string value)
{
    this->value = value;
}

std::string StringValue::toString() const
{
    return value;
}

CellValue* StringValue::clone() const
{
    return new StringValue(*this);
}

ValueType StringValue::getType() const
{
    return ValueType::DOUBLE;
}
