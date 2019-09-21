#pragma once

#include <exprtk.hpp>

namespace epi
{

class Expression final
{
public:
    epiBool Parse(const std::string& raw);
    void AddVariable(const std::string& name, epiFloat& variable);

    epiFloat Value() const;

protected:
    // TODO: make it possible to change to another types
    exprtk::expression<epiFloat> m_Expression;
    exprtk::symbol_table<epiFloat> m_SymbolTable;
};

}
