#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <vector>
#include <map>

enum token_Value { number, LP = '(', RP = ')', plus = '+', minus = '-', times = '*', divide = '/', null_tok };
typedef std::vector<token_Value>::const_iterator VI;

class Expression
{
public:
    Expression();
    std::vector<token_Value> m_tokens;
    std::map<VI, std::string> m_numbers;
    bool isValid;
};

#endif // EXPRESSION_H
