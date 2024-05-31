#include "CellValue.h"
#include "Table.h"
#include <string>
#include <vector>

class FormulaValue : public CellValue 
{
private:
    std::string cellValue;
    Table* table; 

public:
    FormulaValue(const std::string& formula, Table* table);
    std::string toString() const override;
    std::string getFormula() const;
    CellValue* clone() const override;
    ValueType getType() const override;
    double evaluate() const;

private:
    double parseAndEvaluate(const std::string& formula) const;
    std::pair<int, int> parseCellAddress(const std::string& address) const;
    double parseTerm(const std::string& term) const;
};

