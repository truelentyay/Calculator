#ifndef PARSER_H
#define PARSER_H
#include "nodes.h"
#include <string>
#include "input.h"

class Parser
{
private:
    NodeBase *m_node;
public:
    NodeBase *parse(Input *input);
    char findOperation(Input *input);
    NodeBase *findLeftOperand(Input *input);
    NodeBase *findRightOperand(Input *input);
    NodeBase* binary_operation(char op, NodeBase* left, NodeBase* right);
    ~Parser();
};

#endif // PARSER_H
