#include "EpiLib/pch.h"
#include "Expression.h"

namespace epi
{

epiBool Expression::Parse(const std::string& raw)
{
    assert(m_SymbolTable.variable_count() > 0);

    m_Expression.register_symbol_table(m_SymbolTable);

    exprtk::parser<float> parser;
    const epiBool status = parser.compile(raw, m_Expression);
    if (!status)
    {
        return false;
    }

    return true;
}

void Expression::AddVariable(const std::string& name, float& variable)
{
    const epiBool status = m_SymbolTable.add_variable(name, variable);
    assert(status);
}

float Expression::Value() const
{
    return m_Expression.value();
}

}
