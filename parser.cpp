#include "parser.h"
#include <cstddef>
#include <string>
#include <cstdlib>
#include <iostream>

//const char EXPRESSION = 'E';
//const char NUMBER = 'N';
const size_t toCharAfterSpace = 1;
VI position;

NodeBase* Parser::parse(Input &input)
{
    if (input.getStr().empty())
    {
       return NULL;
    }
    input.splitIntoTokens();
    position = input.begin();
    token_Value operation = input.find_operation_from(position);
    if (operation == null_tok)
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

//token_Value Parser::findOperation(Input &input)
//{
//    //input.setPos(0);
//    char Operation = input.find_operation_from(position);
//    //input.setPos(input.getPos()+2);
//    return Operation;
//}

NodeBase *Parser::findLeftOperand(Input &input)
{
    Input leftOperand(input.find_expression_from(position));
    NodeBase *node;
    switch (leftOperand.getTokenFrom(0))
    {
    case LP:
        node = parse(leftOperand);
        //input.setPos(input.getPos()+toCharAfterSpace);
        break;
    case number:
        node = new Node(atof(leftOperand.getNumberFrom(0).c_str()));
        //input.setPos(input.getPos()+toCharAfterSpace);
        break;
    default:
        node = NULL;
        break;
    }
    return node;
}

NodeBase *Parser::findRightOperand(Input &input)
{
    Input rightOperand(input.find_expression_from(position));
    NodeBase *node;
    switch (input.getTokenFrom(0))
    {
    case LP:
        node = parse(rightOperand);
        //input.setPos(input.getPos());
        break;
    case number:
        node = new Node(atof(rightOperand.getNumberFrom(0).c_str()));
        //input.setPos(input.getPos());
        break;
    default:
        node = NULL;
        break;
    }
    return node;
}

NodeBase* Parser::binary_operation(token_Value op, NodeBase* left, NodeBase* right)
{
    NodeBase *node = NULL;
    switch (op)
    {
    case plus:
        node = new NodeOperatorPlus(left, right);
        break;
    case minus:
        node = new NodeOperatorMinus(left, right);
        break;
    case times:
        node = new NodeOperatorTimes(left, right);
        break;
    case divide:
        node = new NodeOperatorDivide(left, right);
        break;
    }
    return node;
}

