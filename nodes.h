#ifndef NODES_H
#define NODES_H
#include "my_smartptr.h"

class NodeBase
{
public:
    NodeBase();

    virtual double eval() = 0;
    virtual NodeBase* clone()  = 0;
    virtual ~NodeBase();
private:
    NodeBase( NodeBase&);
};

class Node : public NodeBase
{
public:
    Node(double v);
    virtual double eval();
    virtual NodeBase* clone() ;
private:
    double m_value;
};



class NodeOperator : public NodeBase
{
public:
    NodeOperator(NodeBase* left, NodeBase* right);
    virtual double eval() = 0;
    virtual NodeBase* clone()  = 0;
protected:
    SmartPtr<NodeBase> m_left;
    SmartPtr<NodeBase> m_right;
};

class NodeOperatorPlus : public NodeOperator
{
public:
    NodeOperatorPlus(NodeBase* left, NodeBase* right);
    virtual double eval();
    virtual NodeBase* clone() ;
};

class NodeOperatorMinus : public NodeOperator
{
public:
    NodeOperatorMinus(NodeBase * left, NodeBase * right);
    virtual double eval();
    virtual NodeBase * clone() ;
};

class NodeOperatorTimes : public NodeOperator
{
public:
    NodeOperatorTimes(NodeBase * left, NodeBase * right);
    virtual double eval();
    virtual NodeBase * clone() ;
};

class NodeOperatorDivide : public NodeOperator
{
public:
    NodeOperatorDivide(NodeBase * left, NodeBase * right);
    virtual double eval();
    virtual NodeBase * clone() ;
};

#endif // NODES_H
