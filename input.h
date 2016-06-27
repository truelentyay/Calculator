#ifndef INPUT_H
#define INPUT_H
#include <cctype>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
#include "token.h"


//enum token_Value { number, LP = '(', RP = ')', plus = '+', minus = '-', time = '*', diviation = '/' };

typedef std::vector<token_Value>::const_iterator VI;

class Input
{
public:
    Input();
    Input(std::vector<Token> tokens);
    Input(std::string str);
    std::vector<Token> find_expression();
    Token find_operation();
    Token find_number();
    void setPos(size_t m_pos);
    size_t getPos();
    std::string getStr();
    Token nextToken();
    //token_Value getTokenFrom(size_t pos);
   // std::string getNumberFrom(size_t pos);
   // VI begin();
    void splitIntoTokens();
    bool isValid();
    bool containsAnyOf(std::vector<token_Value>);

private:
    std::string m_str;
    std::vector<Token> m_tokens;
    size_t m_pos;
    bool m_Valid;
};

#endif // INPUT_H
