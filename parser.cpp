#include "parser.h"
#include <cstddef>
#include <string>
#include <cstdlib>
#include <iostream>



NodeBase* Parser::parse(Input *input)
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

    if (input->getStr() == "")
    {
       //throw std::runtime_error("String is emty!");
       return NULL;
    }
    char operation = findOperation(input);
    if (operation == '0')
    {
        return NULL;
    }
    NodeBase* left = findLeftOperand(input);
    NodeBase* right = findRightOperand(input);
    if (left == NULL || right == NULL)
    {
        return NULL;
    }
    return m_node = binary_operation(operation, left, right);
}

char Parser::findOperation(Input *input)
{
    input->setPos(0);
    char Operation = input->takeOperationFromPos();
    input->setPos(input->getPos()+2);
    return Operation;
}

NodeBase *Parser::findLeftOperand(Input *input)
{
    Input *leftOperand = new Input(input->takeExpressionFromPos());
    NodeBase *node;
    switch (input->getFormat())
    {
    case 'E':
        node = parse(leftOperand);
        input->setPos(input->getPos()+2);
        break;
    case 'N':
        node = new Node(atof(leftOperand->getStr().c_str()));
        input->setPos(input->getPos()+1);
        break;
    default:
        node = NULL;
        break;
    }
    delete leftOperand;
    return node;
}

NodeBase *Parser::findRightOperand(Input *input)
{
    Input *rightOperand = new Input(input->takeExpressionFromPos());
    NodeBase *node;
    switch (input->getFormat())
    {
    case 'E':
        node = parse(rightOperand);
        input->setPos(input->getPos());
        break;
    case 'N':
        node = new Node(atof(rightOperand->getStr().c_str()));
        input->setPos(input->getPos());
        break;
    default:
        node = NULL;
        break;
    }
    delete rightOperand;
    return node;
}

NodeBase* Parser::binary_operation(char op, NodeBase* left, NodeBase* right)
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
}
