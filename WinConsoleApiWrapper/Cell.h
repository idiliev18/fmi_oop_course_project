#pragma once
#include <iostream>
#include <string>

enum class ValueType {
    INT,
    DOUBLE,
    STRING,
    FORMULA,
    NONE
};

class CellValue {
public:
    virtual ~CellValue() {}
    virtual std::string toString() const = 0;
    virtual CellValue* clone() const = 0;
    virtual ValueType getType() const = 0;
};

class IntValue : public CellValue {
    int value;
public:

    IntValue(int value) 
    {
        this->value = value;
    }

    std::string toString() const override 
    {
        return std::to_string(value);
    }

    CellValue* clone() const override
    {
        return new IntValue(*this);
    }

    ValueType getType() const override 
    {
        return ValueType::INT;
    }
};

class DoubleValue : public CellValue {
    double value;
public:

    DoubleValue(double value)
    {
        this->value = value;
    }

    std::string toString() const override
    {
        return std::to_string(value);
    }

    CellValue* clone() const override
    {
        return new DoubleValue(*this);
    }

    ValueType getType() const override
    {
        return ValueType::DOUBLE;
    }
};

//TODO - Formula value


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

