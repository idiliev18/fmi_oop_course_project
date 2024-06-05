#pragma once

#include "CellValue.h"
#include <string>
#include <stdexcept>

class Table;

class FormulaValue : public CellValue
{
public:
    FormulaValue(const std::string& formula, const Table* table);
    std::string toString() const override;
    CellValue* clone() const override;
    ValueType getType() const override;
    const std::string& getFormula() const;

private:
    std::string formula;
    const Table* table;
    mutable bool hasError;

    double evaluate() const;
    double getCellValue(const std::string& cellAddress) const;
};
