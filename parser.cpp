#include "parser.h"
#include <cstddef>
#include <string>
#include <cstdlib>
#include <iostream>

NodeBase* Parser::parse(std::string string)
{
    if (string.empty())
    {
        return NULL;
    }
    Input input(string);
    if (!input.getStr().empty())
    {
       input.splitIntoTokens();
    }

    size_t pos = input.find_operation();
    if (pos == -1)
    {
        return NULL;
    }
    Token operation = input.getToken(pos);
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


NodeBase *Parser::findLeftOperand(Input &input)
{  
    NodeBase *node;
    Token curr_token = input.getToken();
    switch (curr_token.getType())
    {
    case LP:
    {
       // std::cout << "left LP " << " " << curr_token.getValue<std::string>() << std::endl;
        std::vector<Token> exp = input.find_expression();
        Input leftOperand(exp);
        leftOperand.convertIntoString();
//        if (!input.isValid())
//        {
//            node = NULL;
//            break;
//        }
        node = parse(leftOperand.getStr());
        break;
    }
    case number:
    {
     //   std::cout << "left number " << " " << curr_token.getValue<std::string>()  << std::endl;
        if (!input.isValid())
        {
            return NULL;
        }
        node = new Node(input.find_number().getValue<double>());
        break;
    }
    default:
    //    std::cout << "left defoult " << " " << curr_token.getValue<std::string>()  << std::endl;
        node = NULL;
        break;
    }
    return node;
}

NodeBase *Parser::findRightOperand(Input &input)
{ 
    NodeBase *node;
    Token curr_token = input.getToken();
    switch (curr_token.getType())
    {
    case LP:
    {
   //     std::cout << "right LP " << " " << curr_token.getValue<std::string>() << std::endl;
        std::vector<Token> exp = input.find_expression();
        Input rightOperand(exp);
        rightOperand.convertIntoString();
//        if (!input.isValid())
//        {
//            return NULL;
//        }
        node = parse(rightOperand.getStr());
        break;
    }
    case number:
    {
   //     std::cout << "right number " << " " << curr_token.getValue<std::string>() << std::endl;
        if (!input.isValid())
        {
            return NULL;
        }
        node = new Node(input.find_number().getValue<double>());
        break;
    }
    default:
 //       std::cout << "right default " << " " << curr_token.getValue<std::string>() << std::endl;
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

