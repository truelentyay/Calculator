#ifndef PARSER_H
#define PARSER_H
#include "nodes.h"
#include <string>


class Parser
{
private:
    NodeBase *m_node;
    NodeBase *l_node;
    NodeBase *r_node;
public:
    NodeBase* parse(std::string str);
    size_t fnd_arg_end(size_t pos, std::string str);
    size_t fnd_next_space(size_t pos, std::string str);
    NodeBase* binary_operation(NodeBase* left, NodeBase* right, char op);
    ~Parser();
};

#endif // PARSER_H
