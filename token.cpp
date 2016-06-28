#include "token.h"

Token::Token()
{

}

Token::Token(token_Value type, std::string value)
{
   m_type = type;
   m_value = value;
}


template<class C>
C Token::getValue()
{
    return m_value;
}

template<>
std::string Token::getValue<std::string>()
{
   return m_value;
}

template<>
double Token::getValue<double>()
{
    return atof(m_value.c_str());
}

token_Value Token::getType()
{
   return m_type;
}


