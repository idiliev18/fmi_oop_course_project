#include "FormulaValue.h"
#include "IntValue.h"
#include "DoubleValue.h"
#include "Table.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <regex>

FormulaValue::FormulaValue(const std::string& formula, const Table* table)
    : formula(formula), table(table), hasError(false) {}

std::string FormulaValue::toString() const 
{
    try
    {
        double result = evaluate();
        if (hasError) 
        {
            return "ERROR";
        }
        std::ostringstream oss;
        oss << result;
        return oss.str();
    }
    catch (const std::exception&) 
    {
        return "ERROR";
    }
}

CellValue* FormulaValue::clone() const 
{
    return new FormulaValue(*this);
}

ValueType FormulaValue::getType() const 
{
    return ValueType::FORMULA;
}

const std::string& FormulaValue::getFormula() const 
{
    return formula;
}

double FormulaValue::evaluate() const
{
    hasError = false;
    try
    {
        std::regex regexPattern(R"((R\d+C\d+|\d+(\.\d+)?|[\+\-\*/]))");
        std::sregex_iterator it(formula.begin() + 1, formula.end(), regexPattern);
        std::sregex_iterator end;

        std::vector<std::string> tokens;
        while (it != end) 
        {
            tokens.push_back(it->str());
            ++it;
        }

        if (tokens.size() != 3) 
        {
            throw std::runtime_error("Invalid formula format");
        }

        double lhs = std::isdigit(tokens[0][0]) ? std::stod(tokens[0]) : getCellValue(tokens[0]);
        double rhs = std::isdigit(tokens[2][0]) ? std::stod(tokens[2]) : getCellValue(tokens[2]);
        char op = tokens[1][0];

        switch (op) 
        {
        case '+':
            return lhs + rhs;
        case '-':
            return lhs - rhs;
        case '*':
            return lhs * rhs;
        case '/':
            if (rhs == 0) {
                hasError = true;
                return 0;
            }
            return lhs / rhs;
        default:
            throw std::runtime_error("Invalid operator");
        }
    }
    catch (const std::exception&)
    {
        hasError = true;
        throw;
    }
}

double FormulaValue::getCellValue(const std::string& cellAddress) const 
{
    std::pair<int, int> address = table->parseAddress(cellAddress);
    const Cell& cell = table->getCell(address.first, address.second);

    if (cell.cellValue == nullptr) 
    {
        return 0.0;
    }

    switch (cell.cellValue->getType()) 
    {
    case ValueType::INT:
        return dynamic_cast<const IntValue*>(cell.cellValue)->getValue();
    case ValueType::DOUBLE:
        return dynamic_cast<const DoubleValue*>(cell.cellValue)->getValue();
    case ValueType::STRING:
    case ValueType::FORMULA:
    default:
        hasError = true;
        throw std::runtime_error("Invalid cell reference");
    }
}
