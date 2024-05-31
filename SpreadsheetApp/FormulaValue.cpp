#pragma once
#include "FormulaValue.h"
#include "Table.h"
#include <string>


FormulaValue::FormulaValue(const std::string& formula, Table* table)
{
    this->cellValue = formula;
    this->table = table;
}

std::string FormulaValue::toString() const 
{
    double result = evaluate();
    return std::to_string(result);
}

CellValue* FormulaValue::clone() const 
{
    return new FormulaValue(*this);
}

ValueType FormulaValue::getType() const
{
    return ValueType::FORMULA;
}

double FormulaValue::evaluate() const
{
    return parseAndEvaluate(cellValue.substr(1));
}

double FormulaValue::parseAndEvaluate(const std::string& formula) const {
    std::vector<double> values;
    std::vector<char> operators;
    size_t pos = 0;

    while (pos < formula.size()) 
    {
        while (pos < formula.size() && formula[pos] == ' ') 
        {
            ++pos;
        }

        size_t start = pos;
        while (pos < formula.size() && (std::isalnum(formula[pos]) || formula[pos] == 'R' || formula[pos] == 'C' || formula[pos] == '.'))
        {
            pos++;
        }
        std::string term = formula.substr(start, pos - start);
        double value = parseTerm(term);
        values.push_back(value);


        while (pos < formula.size() && formula[pos] == ' ') 
        {
            pos++;
        }
        if (pos < formula.size() && (formula[pos] == '+' || formula[pos] == '-' || formula[pos] == '*' || formula[pos] == '/' || formula[pos] == '^')) 
        {
            operators.push_back(formula[pos]);
            pos++;
        }
    }

    for (size_t i = 0; i < operators.size(); ++i)
    {
        if (operators[i] == '^') 
        {
            values[i] = std::pow(values[i], values[i + 1]);
            values.erase(values.begin() + i + 1);
            operators.erase(operators.begin() + i);
            --i;
        }
    }

    for (size_t i = 0; i < operators.size(); ++i) 
    {
        if (operators[i] == '*' || operators[i] == '/') 
        {
            values[i] = operators[i] == '*' ? values[i] * values[i + 1] : values[i] / values[i + 1];
            values.erase(values.begin() + i + 1);
            operators.erase(operators.begin() + i);
            --i;
        }
    }

    for (size_t i = 0; i < operators.size(); ++i) 
    {
        if (operators[i] == '+' || operators[i] == '-') 
        {
            values[i] = operators[i] == '+' ? values[i] + values[i + 1] : values[i] - values[i + 1];
            values.erase(values.begin() + i + 1);
            operators.erase(operators.begin() + i);
            --i;
        }
    }

    return values[0];
}


double FormulaValue::parseTerm(const std::string& term) const
{
    if (term[0] == 'R') 
    {
        std::pair<int, int> cellPos = parseCellAddress(term);
        const Cell& cell = table->getCell(cellPos.first, cellPos.second);
        if (cell.cellValue)
        {
            return std::stod(cell.cellValue->toString());
        }
        else 
        {
            throw std::runtime_error("Referenced cell is empty");
        }
    }
    else 
    {
        char* end;
        double value = std::strtod(term.c_str(), &end);
        if (*end == '\0') 
        {
            return value;
        }
        else 
        {
            throw std::runtime_error("Invalid term: " + term);
        }
    }
}


std::string FormulaValue::getFormula() const 
{
    return cellValue;
}


std::pair<int, int> FormulaValue::parseCellAddress(const std::string& address) const 
{
    if (address.size() < 4 || address[0] != 'R' || address.find('C') == std::string::npos) 
    {
        // error
    }
    size_t cPos = address.find('C');
    int row = std::atoi(address.substr(1, cPos - 1).c_str()) - 1;
    int col = std::atoi(address.substr(cPos + 1).c_str()) - 1;
    return { row, col };
}
