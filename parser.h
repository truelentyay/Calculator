#ifndef PARSER_H
#define PARSER_H
#include "nodes.h"
#include <string>
#include "input.h"

class Parser
{
private:
    NodeBase *m_node;
    NodeBase *l_node;
    NodeBase *r_node;
public:
    NodeBase *parse(Input *input);
    char findOperation(Input *input);
    NodeBase *findLeftOperand(Input *input);
    NodeBase *findRightOperand(Input *input);
//    size_t fnd_arg_end(size_t pos, std::string str);
//    size_t fnd_next_space(size_t pos, std::string str);
//    size_t fnd_operator(std::string str);
    NodeBase* binary_operation(char op, NodeBase* left, NodeBase* right);
    ~Parser();
};

#endif // PARSER_H
