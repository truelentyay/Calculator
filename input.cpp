#include "input.h"


//typedef std::map<int, std::string>::const_iterator MI;
//typedef std::string::const_iterator SI;
//typedef std::vector<token_Value>::const_iterator VI;

Input::Input()
    : m_Valid(true)
    , m_pos(0)
{
    m_tokens.reserve(100);
}

Input::Input(std::vector<Token> tokens)
    : m_tokens(tokens)
    , m_Valid(true)
    , m_pos(0)
{
    m_tokens.reserve(100);
}

Input::Input(std::string str)
    : m_str(str)
    , m_Valid(true)
    , m_pos(0)
{
   // m_tokens.reserve(100);
}

size_t Input::find_operation()
{
    m_pos = 0;
    token_Value t[4] = {plus, minus, times, divide};
    std::vector<token_Value> opers(t, t+4);
    size_t p;
    p = findFirstOfAny(opers, m_pos);
    m_pos = p+1;
    return p;
}

Token Input::find_number()
{  
//    if (pos >= m_tokens.size())
//    {
//        std::cerr << "Position is out of range!" << std::endl;
//        m_Valid = false;
//        return m_tokens[0];
//        //throw std::runtime_error("Position is out of range!");
//    }
    for (size_t i = m_pos; i < m_tokens.size(); ++i)
    {
        Token curr_token = m_tokens[i];
        if (curr_token.getType() == number)
        {
            m_pos = i+1;
            return curr_token;
        }
    }
    std::cerr << "There is no numbers!" << std::endl;
    m_Valid = false;
    return m_tokens[0];
}

std::vector<Token> Input::find_expression()
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
    for (size_t i = m_pos; i < m_tokens.size(); ++i)
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
                m_pos = i+1;
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
    if (0 != f)
    {
        //throw std::runtime_error("Wrong expression!");
        std::cerr << "Wrong expression!" << std::endl;
        m_Valid = false;
    }
    return tokens;
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

Token Input::getToken(size_t pos)
{
    if (pos >= m_tokens.size())
    {
        std::cerr << "Position is out of range!" << std::endl;
        m_Valid = false;
        return m_tokens[0];
        //throw std::runtime_error("Position is out of range!");
    }
    return m_tokens[pos];
}

Token Input::getToken()
{
    return m_tokens[m_pos];
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

void Input::convertIntoString()
{
    for (size_t i = 0; i < m_tokens.size(); ++i)
    {
        Token curr_token = m_tokens[i];
        //std::string curr_value = curr_token.getValue<std::string>();
        m_str = m_str + curr_token.getValue<std::string>() + " ";
      //  m_str.push_back(curr_value.c_str());
    }
}

bool Input::isValid()
{
    return m_Valid;
}

size_t Input::findFirstOfAny(std::vector<token_Value> tok, size_t pos)
{
    int count = 0;
    size_t min = m_tokens.size();
    for (size_t i = 0; i < tok.size(); ++i)
    {
        for (size_t j = pos; j < m_tokens.size(); j++)
        {
            Token curr_token = m_tokens[j];
            if (tok[i] == curr_token.getType())
            {
//                if (count == 0)
//                {
//                    min = j;
//                    return j;
//                }
                if (min > j)
                {
                    min = j;
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
    return min;
}

