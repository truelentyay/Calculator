#ifndef INPUT_H
#define INPUT_H
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "token.h"


//enum token_Value { number, LP = '(', RP = ')', plus = '+', minus = '-', time = '*', diviation = '/' };

//typedef std::vector<token_Value>::const_iterator VI;

class Input
{
public:
    Input();
    Input(std::vector<Token> tokens);
    Input(std::string str);
    std::vector<Token> find_expression(size_t pos);
    Token find_operation(size_t pos);
    Token find_number(size_t pos);
//    void setPos(size_t &pos);
//    size_t getPos();
    std::string getStr();
    Token nextToken(size_t pos);
    //token_Value getTokenFrom(size_t pos);
   // std::string getNumberFrom(size_t pos);
   // VI begin();
    void splitIntoTokens();
    bool isValid();
    size_t findFirstOfAny(std::vector<token_Value>, size_t pos);

private:
    std::string m_str;
    std::vector<Token> m_tokens;
//    size_t pos;
    bool m_Valid;
};

#endif // INPUT_H
