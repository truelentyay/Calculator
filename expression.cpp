#include "expression.h"



Expression::Expression()
{
    m_tokens.reserve(100);
    m_tokens.reserve(100);
}

bool Expression::containsAnyOf(std::vector<token_Value> tok)
{
    int count = 0;
    for (VI i = tok.begin(); i != tok.end(); ++i)
    {
        VI it = std::find(m_tokens.begin(), m_tokens.end(), *i/*str[i]*/);
        //VI it = m_expression.m_numbers.find(token_Value(*i)/*str[i]*/)->first;
        if (it != m_tokens.end())
        {
            ++count;
        }
    }
    if (count == 0)
    {
        return false;
    }
    return true;
}
