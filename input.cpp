#include "input.h"
#include <stdexcept>
#include <cctype>

const char EXPRESSION = 'E';
const char NUMBER = 'N';
const size_t posOfOperation = 1;

Input::Input(std::string str)
{
   m_str = str;
   m_pos = 0;
}

char Input::takeOperationFromPos()
{

       if (m_str.find_first_of("+") == std::string::npos && m_str.find_first_of("-") == std::string::npos && m_str.find_first_of("*") == std::string::npos && m_str.find_first_of("/") == std::string::npos)
       {
          //throw std::runtime_error("Tere's no operations!");
           return '0';
       }
       else
       {
          m_pos = posOfOperation;
          return m_str[posOfOperation];
       }
}

std::string Input::takeExpressionFromPos()
{
   if (m_pos >= m_str.length())
   {
       m_format = '0';
       return "";
   }
   std::string input;
   size_t i;
   int f = 0;
   if (m_str[m_pos] == '(')
   {
      m_format = EXPRESSION;
      for (i = m_pos; i < m_str.length(); ++i)
      {
         if (m_str[i]=='(')
         {
            ++f;
         }
         else if (m_str[i]==')')
         {
            --f;
         }
         if (f == 0)
         {
             ++i;
             break;
         }
      }
      input = m_str.substr(m_pos, i - m_pos);
      m_pos = i;
   }
   else if (std::isdigit(m_str[m_pos]))
   {
      m_format = NUMBER;
      i = m_pos;
      while (m_str[i] != ' ' && i < m_str.length())
      {
          ++i;
      }
      input = m_str.substr(m_pos, i - m_pos);
      m_pos = i;
   }
   else
   {
      //throw std::runtime_error("Wrong input!");
       m_format = '0';
       return "";
   }
   return input;
}

void Input::setPos(size_t pos)
{
   m_pos = pos;
}

size_t Input::getPos()
{
   return m_pos;
}

std::string Input::getStr()
{
    return m_str;
}


char Input::getFormat()
{
   return m_format;
}

