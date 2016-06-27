#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum token_Value { number, LP = '(', RP = ')', plus = '+', minus = '-', times = '*', divide = '/', null_tok };

class Token
{
public:
    Token();
    Token(token_Value type, std::string value);
    Token(token_Value type, char value);
    std::string getValue();
    char getValue();
    token_Value getType();

private:
    token_Value m_type;
    std::string m_value;
};

#endif // TOKEN_H
