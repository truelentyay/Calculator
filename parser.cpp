#include "parser.h"
#include <cstddef>
#include <string>
#include <cstdlib>
#include <iostream>

NodeBase* Parser::parse(std::string str)
{
    /*
    * if (str.empty())
    * {
    *   say error
    * }
    *
    * Operation opertation = getOperation( str );
    * if ( !operation.isValid() )
    * {
    *   say invalid operation
    * }
    *
    *
    * NodeBase* left = getLeftOperand(str);
    * NodeBase* right = getRightOperand(str);
    *
    * if (!left.isValid() || !right.isValid())
    * {
    *  say error
    * }
    *
    * return makeNode( operation, left, right );
    *
    *
    *
    * NodeBase* Parser::getLeftOperand(const std::string& str )
    * {
    *   std::string exp = findExp( str );
    *   NodeBase* doub = findDouble( str );
    *   if (  )
    *
    * }
    *
    */


    if (str == "")
    {
        return m_node = NULL;
    }


    m_node = NULL;
    //size_t i = fnd_begin(str);
    size_t j = std::string::npos, k = std::string::npos;
    size_t i = fnd_operator(str);
    if (i == std::string::npos)
    {
        return m_node = NULL;
    }
    std::string left = "";
    std::string right = "";
    if (str[i+2] == '(')
    {
        j = fnd_arg_end(i+2, str);
        if (j == 0)
        {
            return m_node = NULL;
        }
        left = str.substr(i+2,j-(i+1));
        right = str.substr(j+2,str.length()-(j+2)-1);
        if (right[0] == '(')
        {
            //right = str.substr(j+2,str.length()-(j+2)-1);
            m_node = binary_operation(parse(left),  parse(right), str[i]);
        }
        else
        {
            r_node = new Node(atof(right.c_str()));
            m_node = binary_operation(parse(left),  r_node, str[i]);
        }
    }
    else
    {
        k = fnd_next_space(i+2, str);
        left = str.substr(i+2,k-(i+2));
        if (left == "")
        {
            return m_node = NULL;
        }
        double d = atof(left.c_str());
        l_node = new Node(d);
        right = str.substr(k+1,str.length()-(k+1)-1);
        if (right[0] == '(')
        {
            if (right == "")
            {
                return m_node = NULL;
            }
            m_node = binary_operation(l_node,  parse(right), str[i]);
        }
        else
        {
            r_node = new Node(atof(right.c_str()));
            m_node = binary_operation(l_node,  r_node, str[i]);
        }

    }
    return m_node;
}

size_t Parser::fnd_arg_end(size_t pos, std::string str)
{
    int f = 0;
    size_t i;
    for (i = pos; i < str.length(); i++)
    {
        if (str[i]=='(')
        {
            f++;
        }
        else if (str[i]==')')
        {
            f--;
        }
        if (f == 0)
        {
            return i;
        }

    }
    return 0;

}


size_t Parser::fnd_next_space(size_t pos, std::string str)
{
    pos = str.find_first_of(" ", pos);
    if (pos != std::string::npos)
    {
        return pos;
    }
    else
    {
        return std::string::npos;
    }

}

size_t Parser::fnd_operator(std::string str)
{
    if (str.find_first_of("+") == std::string::npos && str.find_first_of("-") == std::string::npos && str.find_first_of("*") == std::string::npos && str.find_first_of("/") == std::string::npos)
    {
        return std::string::npos;
    }
    else
    {
        return 1;
    }

}

NodeBase* Parser::binary_operation(NodeBase* left, NodeBase* right, char op)
{
    m_node = NULL;
    switch (op)
    {
    case '+':
        m_node = new NodeOperatorPlus(left, right);
        break;
    case '-':
        m_node = new NodeOperatorMinus(left, right);
        break;
    case '*':
        m_node = new NodeOperatorTimes(left, right);
        break;
    case '/':
        m_node = new NodeOperatorDivide(left, right);
        break;
    }
    return m_node;
}

Parser::~Parser()
{
    delete m_node;
    delete l_node;
    delete r_node;
}
