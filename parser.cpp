#include "parser.h"
#include <cstddef>
#include <string>
#include <cstdlib>
#include <iostream>

const char EXPRESSION = 'E';
const char NUMBER = 'N';
const size_t toCharAfterSpace = 1;


NodeBase* Parser::parse(Input &input)
{
    if (input.getStr().empty())
    {
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
    return binary_operation(operation, left, right);
}

char Parser::findOperation(Input &input)
{
    input.setPos(0);
    char Operation = input.takeOperationFromPos();
    input.setPos(input.getPos()+2);
    return Operation;
}

NodeBase *Parser::findLeftOperand(Input &input)
{
    Input leftOperand(input.takeExpressionFromPos());
    NodeBase *node;
    switch (input.getFormat())
    {
    case EXPRESSION:
        node = parse(leftOperand);
        input.setPos(input.getPos()+toCharAfterSpace);
        break;
    case NUMBER:
        node = new Node(atof(leftOperand.getStr().c_str()));
        input.setPos(input.getPos()+toCharAfterSpace);
        break;
    default:
        node = NULL;
        break;
    }
    return node;
}

NodeBase *Parser::findRightOperand(Input &input)
{
    Input rightOperand(input.takeExpressionFromPos());
    NodeBase *node;
    switch (input.getFormat())
    {
    case EXPRESSION:
        node = parse(rightOperand);
        input.setPos(input.getPos());
        break;
    case NUMBER:
        node = new Node(atof(rightOperand.getStr().c_str()));
        input.setPos(input.getPos());
        break;
    default:
        node = NULL;
        break;
    }
    return node;
}

NodeBase* Parser::binary_operation(char op, NodeBase* left, NodeBase* right)
{
    NodeBase *node = NULL;
    switch (op)
    {
    case '+':
        node = new NodeOperatorPlus(left, right);
        break;
    case '-':
        node = new NodeOperatorMinus(left, right);
        break;
    case '*':
        node = new NodeOperatorTimes(left, right);
        break;
    case '/':
        node = new NodeOperatorDivide(left, right);
        break;
    }
    return node;
}

