#include "input.h"


//typedef std::map<int, std::string>::const_iterator MI;
//typedef std::string::const_iterator SI;
//typedef std::vector<token_Value>::const_iterator VI;

Input::Input()
    : m_Valid(true)
    , m_pos(0)
{
    //m_tokens.reserve(100);
}

Input::Input(std::vector<Token> tokens)
    : m_tokens(tokens)
    , m_Valid(true)
    , m_pos(0)
{
    //m_tokens.reserve(100);
}

Input::Input(std::string str)
    : m_str(str)
    , m_pos(0)
{
   // m_tokens.reserve(100);
}

Token Input::find_operation()
{
    token_Value t[4] = {plus, minus, times, divide};
    std::vector<token_Value> opers(t, t+4);
    ++m_pos;
    if (this->containsAnyOf(opers))
    {
        return m_tokens[m_pos];
    }
    else
    {
        std::cerr << "There is no operations!" << std::endl;
        m_Valid = false;
    }
}

Token Input::find_number()
{
    ++m_pos;
    if (m_pos <= m_tokens.size())
    {
        return m_tokens[m_pos];
    }
    else
    {
        std::cerr << "Position is out of range!" << std::endl;
        m_Valid = false;
    }
}

std::vector<Token> Input::find_expression()
{
    m_Valid = true;
    ++m_pos;
    std::vector<Token> tokens;
    //    if (m_pos >= curr_tok.end())
    //    {
    //        std::cerr << "Position is out of range!" << std::endl;
    //        m_Valid = false;
    //    }
    int f = 0;
    for (m_pos; m_pos < m_tokens.size(); ++m_pos)
    {
        Token curr_token = m_tokens[m_pos];
        switch (curr_token.getType()) {
        case LP:
            tokens.push_back(curr_token);
            ++f;
            break;
        case RP:
            tokens.push_back(curr_token);
            --f;
            break;
        default:
            tokens.push_back(curr_token);
            break;
        }
        if (0 == f)
        {
            break;
        }
    }
    return tokens;
}

void Input::setPos(size_t pos)
{
    if (m_pos >= m_tokens.size())
    {
        std::cerr << "Position is out of range!" << std::endl;
    }
    else
    {
        m_pos = pos;
    }
}

size_t Input::getPos()
{
   return m_pos;
}

std::string Input::getStr()
{
    return m_str;
}

Token Input::nextToken()
{
    return m_tokens[m_pos+1];
}

//token_Value Input::getTokenFrom(size_t pos)
//{
//    return *pos/*m_expression.m_tokens[pos]*/;
//}

//std::string Input::getNumberFrom(size_t pos)
//{
//    //MI curr_number = m_expression.m_numbers.find(*pos/*m_expression.m_tokens[pos]*/);
//    return m_expression.m_numbers.find(pos)->second;
//}

//VI Input::begin()
//{
//    return m_expression.m_tokens.begin();
//}


//char Input::getFormat()
//{
//    return m_format;
//}

void Input::splitIntoTokens()
{
    m_Valid = true;
    std::string strNum = "";
    for (size_t i = 0; i < m_str.size(); ++i)
    {
        char ch = m_str[i];
        switch (ch) {
        case ' ':
            if (!strNum.empty())
            {
                Token token(number, strNum);
                strNum = "";
                m_tokens.push_back(token);
            }
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
            if (!strNum.empty())
            {
                Token token(number, strNum);
                strNum = "";
                m_tokens.push_back(token);
                break;
            }
            else
            {
                Token token(token_Value(ch), ch);
                m_tokens.push_back(token);
                break;
            }
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': case '0':
        case '.':
            strNum.push_back(ch);
            break;
        default:
            std::cerr << "Wrong token!" << std::endl;
            m_Valid = false;
            break;
        }

    }
}

bool Input::isValid()
{
    return m_Valid;
}

bool Input::containsAnyOf(std::vector<token_Value> tok)
{
    int count = 0;
    for (size_t i = 0; i < tok.size(); ++i)
    {
        for (size_t j = 0; j < m_tokens.size(); j++)
        {
            Token curr_token = m_tokens[j];
            if (tok[i] == curr_token.getType())
            {
                ++count;
            }
        }
//        //VI it = std::find(m_tokens.begin(), m_tokens.end(), tok[i]);
//        if (m_tokens.end() != std::find(m_tokens.begin(), m_tokens.end(), tok[i]))
//        {
//            ++count;
//        }
    }
    if (count == 0)
    {
        return false;
    }
    return true;
}

