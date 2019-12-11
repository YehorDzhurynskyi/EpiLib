#pragma once

#include <exprtk.hpp>

namespace epi
{

class Expression final
{
public:
    epiBool Parse(const std::string& raw);
    void AddVariable(const std::string& name, float& variable);

    float Value() const;

protected:
    // TODO: make it possible to change to another types
    exprtk::expression<float> m_Expression;
    exprtk::symbol_table<float> m_SymbolTable;
};

}
