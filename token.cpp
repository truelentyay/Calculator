#include "token.h"

Token::Token()
{

}

Token::Token(token_Value type, std::string value)
{
   m_type = type;
   m_value = value;
}

Token::Token(token_Value type, char value)
{
   m_type = type;
   m_value = value;
}

std::string Token::getValue()
{
   return m_value;
}

char Token::getValue()
{
   return m_value;
}

token_Value Token::getType()
{
   return m_type;
}


