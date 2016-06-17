#include "parser.h"
#include <cstddef>
#include <string>
#include <cstdlib>

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





    m_node = NULL;
    //size_t i = fnd_begin(str);
    size_t i = 1, j = -1, k = -1;
    std::string left = "";
    std::string right = "";
    if (i+2 == '(')
    {
        j = fnd_arg_end(i+2, str);
        left = str.substr(i+2,j-(i+2)-1);
        if (j+2 == '(')
        {
        right = str.substr(j+2,str.length()-(j+2)-3);
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
        left = str.substr(i+2,k-(i+2)-1);
        l_node = new Node(atof(left.c_str()));
        if (k+1 == '(')
        {
        right = str.substr(k+1,str.length()-(k+1)-3);
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
    int f;
    size_t i = 0;
    for (i = pos; i < str.length() && f != 0; i++)
    {
        f = 0;
        if (str[i]=='(')
        {
            f++;
        }
        else if (str[i]==')')
        {
            f--;
        }
        i++;
    }
    return i;

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
        return -1;
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
