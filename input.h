#ifndef INPUT_H
#define INPUT_H
#include <cctype>
#include <string>
#include "expression.h"
#include <iostream>
#include <map>
#include <cstdlib>

//enum token_Value { number, LP = '(', RP = ')', plus = '+', minus = '-', time = '*', diviation = '/' };

typedef std::vector<token_Value>::const_iterator VI;

class Input
{
public:
    Input();
    Input(Expression exp);
    Input(std::string str);
    Expression find_expression_from(VI pos);
    token_Value find_operation_from(VI pos);
//    void setPos(size_t pos);
//    size_t getPos();
    std::string getStr();
    token_Value getTokenFrom(VI pos);
    std::string getNumberFrom(VI pos);
    VI begin();
//    char getFormat();
    void splitIntoTokens();
    bool containsAnyOf(std::string str);

private:
    std::string m_str;
    Expression m_expression;
//    size_t m_pos;
//    char m_format;
    bool isValid;
};

#endif // INPUT_H
