#ifndef PARSER_H
#define PARSER_H
#include "nodes.h"
#include <string>
#include "input.h"

class Parser
{
public:
    NodeBase *parse(Input &input);
//    token_Value findOperation(Input &input);
    NodeBase *findLeftOperand(Input &input);
    NodeBase *findRightOperand(Input &input);
    NodeBase* binary_operation(token_Value op, NodeBase* left, NodeBase* right);
};

#endif // PARSER_H
