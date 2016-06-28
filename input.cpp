#include "input.h"


//typedef std::map<int, std::string>::const_iterator MI;
//typedef std::string::const_iterator SI;
//typedef std::vector<token_Value>::const_iterator VI;

Input::Input()
    : m_Valid(true)
//    , pos(0)
{
    m_tokens.reserve(100);
}

Input::Input(std::vector<Token> tokens)
    : m_tokens(tokens)
    , m_Valid(true)
//    , pos(0)
{
    m_tokens.reserve(100);
}

Input::Input(std::string str)
    : m_str(str)
//    , pos(0)
{
   // m_tokens.reserve(100);
}

Token Input::find_operation(size_t pos)
{
    token_Value t[4] = {plus, minus, times, divide};
    std::vector<token_Value> opers(t, t+4);
    size_t p;
    p = findFirstOfAny(opers, pos);
    if (p != -1)
    {
       // ++pos;
        return m_tokens[p];
    }
    else
    {
//        std::cerr << "There is no operations!" << std::endl;
//        m_Valid = false;
        throw std::runtime_error("There is no operations!");
    }
}

Token Input::find_number(size_t pos)
{  
    if (pos >= m_tokens.size())
    {
//        std::cerr << "Position is out of range!" << std::endl;
//        m_Valid = false;
        throw std::runtime_error("Position is out of range!");
    }
    for (size_t i = pos; i < m_tokens.size(); ++i)
    {
        Token curr_token = m_tokens[i];
        if (curr_token.getType() == number)
        {
            return curr_token;
        }
    }
//    if (pos <= m_tokens.size())
//    {
//        ++pos;
//        return m_tokens[pos];
//    }
//    else
//    {
//        std::cerr << "Position is out of range!" << std::endl;
//        m_Valid = false;
//    }
}

std::vector<Token> Input::find_expression(size_t pos)
{
    m_Valid = true;

    std::vector<Token> tokens;
    //    if (m_pos >= curr_tok.end())
    //    {
    //        std::cerr << "Position is out of range!" << std::endl;
    //        m_Valid = false;
    //    }
    int f = 0;
    bool expressionBegan = false;
    for (size_t i = pos; i < m_tokens.size(); ++i)
    {
        Token curr_token = m_tokens[i];
        switch (curr_token.getType()) {
        case LP:
            if (!expressionBegan)
            {
                expressionBegan = true;
            }
            tokens.push_back(curr_token);
            ++f;
            break;
        case RP:
            if (!expressionBegan)
            {
                break;
            }
            tokens.push_back(curr_token);
            --f;
            if (0 == f)
            {
               // ++pos;
                return tokens;
            }
            break;
        default:
            if (!expressionBegan)
            {
                break;
            }
            tokens.push_back(curr_token);
            break;
        }

    }
    throw std::runtime_error("Wrong expression!");
    //return tokens;
}

//void Input::setPos(size_t pos)
//{
//    if (pos >= m_tokens.size())
//    {
//        std::cerr << "Position is out of range!" << std::endl;
//    }
//    else
//    {
//        pos = pos;
//    }
//}

//size_t Input::getPos()
//{
//   return pos;
//}

std::string Input::getStr()
{
    return m_str;
}

Token Input::nextToken(size_t pos)
{
    return m_tokens[pos+1];
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
    std::string str;
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
        {
            if (!strNum.empty())
            {
                Token tokenNum(number, strNum);
                strNum = "";
                m_tokens.push_back(tokenNum);
//                ss << ch;
//                ss >> str;
//                Token token(token_Value(ch), str);
//                m_tokens.push_back(token);
//                break;
            }

                str.push_back(ch);
                Token token(token_Value(ch), str);
                str = "";
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

size_t Input::findFirstOfAny(std::vector<token_Value> tok, size_t pos)
{
    int count = 0;
    for (size_t i = 0; i < tok.size(); ++i)
    {
        for (size_t j = pos; j < m_tokens.size(); j++)
        {
            Token curr_token = m_tokens[j];
            if (tok[i] == curr_token.getType())
            {
                if (count == 0)
                {
                    return j;
                }
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
        return -1;
    }
}

