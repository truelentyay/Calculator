#include "parser.h"
#include <cstddef>
#include <string>
#include <cstdlib>
#include <iostream>

//const char EXPRESSION = 'E';
//const char NUMBER = 'N';
//const size_t toCharAfterSpace = 1;

NodeBase* Parser::parse(Input &input)
{
    if (input.getStr().empty())
    {
       return NULL;
    }
    input.splitIntoTokens();
    Token operation = input.find_operation();
    if (!input.isValid())
    {
        return NULL;
    }
    NodeBase* left = findLeftOperand(input);
    NodeBase* right = findRightOperand(input);
    if (left == NULL || right == NULL)
    {
        return NULL;
    }
    return binary_operation(operation.getType(), left, right);
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
    NodeBase *node;
    Token next_token = input.nextToken();
    switch (next_token.getType())
    {
    case LP:
    {
        Input leftOperand(input.find_expression());
        if (!input.isValid())
        {
            node = NULL;
            break;
        }
        node = parse(leftOperand);
        break;
    }
    case number:
    {
        if (!input.isValid())
        {
            node = NULL;
            break;
        }
        node = new Node(atof(input.find_number().getValue().c_str()));
        break;
    }
    default:
        node = NULL;
        break;
    }
    return node;
}

NodeBase *Parser::findRightOperand(Input &input)
{ 
    NodeBase *node;
    Token next_token = input.nextToken();
    switch (next_token.getType())
    {
    case LP:
    {
        Input rightOperand(input.find_expression());
        if (!input.isValid())
        {
            return NULL;
        }
        node = parse(rightOperand);
        break;
    }
    case number:
    {
        if (!input.isValid())
        {
            return NULL;
        }
        node = new Node(atof(input.find_number().getValue().c_str()));
        break;
    }
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

