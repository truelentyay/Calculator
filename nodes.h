#ifndef NODES_H
#define NODES_H


class NodeBase
{
public:
    virtual double eval() = 0;
};

class Node : public NodeBase
{
public:

    Node(double v);
    virtual double eval();

private:
    double m_value;
};



class NodeOperator : public NodeBase
{
public:

    NodeOperator(NodeBase& left, NodeBase& right);

    virtual double eval() = 0;


protected:
    NodeBase& m_left;
    NodeBase& m_right;
};

class NodeOperatorPlus : public NodeOperator
{
public:
    NodeOperatorPlus(NodeBase& left, NodeBase& right);
    virtual double eval();
};

class NodeOperatorMinus : public NodeOperator
{
public:
    NodeOperatorMinus(NodeBase& left, NodeBase& right);
    virtual double eval();
};

class NodeOperatorTimes : public NodeOperator
{
public:
    NodeOperatorTimes(NodeBase& left, NodeBase& right);
    virtual double eval();
};

class NodeOperatorDivide : public NodeOperator
{
public:
    NodeOperatorDivide(NodeBase& left, NodeBase& right);
    virtual double eval();
};

#endif // NODES_H
