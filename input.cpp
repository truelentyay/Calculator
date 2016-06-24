#include "input.h"

typedef std::map<int, std::string>::const_iterator CI;
typedef std::string::const_iterator SI;
//typedef std::vector<token_Value>::const_iterator VI;

Input::Input()
    : isValid(true)
{
    m_expression.m_tokens.reserve(100);
}

Input::Input(Expression exp)
    : m_expression(exp)
    , isValid(true)
{
    m_expression.m_tokens.reserve(100);
}

Input::Input(std::string str)
    : m_str(str)
{
    m_expression.m_tokens.reserve(100);
}

token_Value Input::find_operation_from(VI pos)
{
    if (this->containsAnyOf("+-*/"))
    {
        std::cerr << "There is no operations!" << std::endl;
        return null_tok;
    }
    else
    {
        pos = m_expression.m_tokens.begin()+1;
        return *(m_expression.m_tokens.begin()+1);
    }
}

Expression Input::find_expression_from(VI pos)
{
    std::vector<token_Value>& curr_tok = m_expression.m_tokens;
    isValid = true;
    Expression exp;
    if (pos >= curr_tok.end())
    {
        std::cerr << "Position is out of range!" << std::endl;
        isValid = false;
    }
    int f = 0;
    if (LP == *pos)
    {
        for (VI i = pos; i < curr_tok.end(); ++i)
        {
            switch (*i/*curr_tok[i]*/) {
            case LP:
                exp.m_tokens.push_back(*i/*curr_tok[i]*/);
                ++f;
                break;
            case RP:
                exp.m_tokens.push_back(*i/*curr_tok[i]*/);
                --f;
                break;
            case number:
                exp.m_tokens.push_back(*i/*curr_tok[i]*/);
                CI curr_number = m_expression.m_numbers.find(*i/*curr_tok[i]*/);
                exp.m_numbers.insert(exp.m_tokens.end()-1, curr_number->second );
            default:
                exp.m_tokens.push_back(*i/*curr_tok[i]*/);
                break;
            }
            if (0 == f)
            {
                break;
            }
        }
        pos = i+1;
    }
    else if (number == *pos/*curr_tok[pos]*/)
    {
        exp.m_tokens.push_back(*pos/*curr_tok[pos]*/);
        CI curr_number = m_expression.m_numbers.find(*pos/*curr_tok[pos]*/);
        exp.m_numbers.insert(exp.m_tokens.end()-1, curr_number->second );
        ++pos;
    }
    else
    {
        std::cerr << "Wrong input!" << std::endl;
        isValid = false;
    }
    return exp;
}

//void Input::setPos(size_t pos)
//{
//   m_pos = pos;
//}

//size_t Input::getPos()
//{
//   return m_pos;
//}

std::string Input::getStr()
{
    return m_str;
}

token_Value Input::getTokenFrom(VI pos)
{
    return *pos/*m_expression.m_tokens[pos]*/;
}

std::string Input::getNumberFrom(VI pos)
{
    CI curr_number = m_expression.m_numbers.find(*pos/*m_expression.m_tokens[pos]*/);
    return curr_number->second;
}

VI Input::begin()
{
    return m_expression.m_tokens.begin();
}


//char Input::getFormat()
//{
//    return m_format;
//}

void Input::splitIntoTokens()
{
    isValid = true;
    std::vector<token_Value>& curr_tok = m_expression.m_tokens;
    std::string numStr = "";
    for (std::string::const_iterator i = m_str.begin(); i != m_str.end(); ++i)
    {
        char ch = *i/*m_str[i]*/;
        switch (ch) {
        case ' ':
            if (!numStr.empty())
            {
                curr_tok.push_back(number);
                m_expression.m_numbers[numStr] = curr_tok.end()-1;
                numStr = "";
            }
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
            if (!numStr.empty())
            {
                curr_tok.push_back(number);
                m_expression.m_numbers[numStr] = curr_tok.end()-1;
                numStr = "";
            }
            curr_tok.push_back(token_Value(ch));
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': case '0':
        case '.':
            numStr.push_back(ch);
        default:
            std::cerr << "Wrong token!" << std::endl;
            isValid = false;
            break;
        }

    }
}

bool Input::containsAnyOf(std::string str)
{
    std::vector<token_Value>& curr_tok = m_expression.m_tokens;
    int count = 0;
    for (SI i = str.begin(); i != str.end(); ++i)
    {
        VI it = std::find(curr_tok.begin(), curr_tok.end(), *i/*str[i]*/);
        if (it != curr_tok.end())
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

