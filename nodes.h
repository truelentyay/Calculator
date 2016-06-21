#ifndef NODES_H
#define NODES_H


class NodeBase
{
public:
    virtual double eval() = 0;
    virtual NodeBase* clone() const = 0;
    virtual ~NodeBase();
};

class Node : public NodeBase
{
public:
    Node(double v);
    virtual double eval();
    virtual NodeBase* clone() const;
    virtual ~Node();
private:
    double m_value;
};



class NodeOperator : public NodeBase
{
public:
    NodeOperator(NodeBase *left, NodeBase *right);
    NodeOperator(const NodeOperator& other);
    virtual double eval() = 0;
    virtual NodeBase* clone() const = 0;
    virtual ~NodeOperator();
protected:
    NodeBase *m_left;
    NodeBase *m_right;
};

class NodeOperatorPlus : public NodeOperator
{
public:
    NodeOperatorPlus(NodeBase *left, NodeBase *right);
    virtual double eval();
    virtual NodeBase* clone() const;
    virtual ~NodeOperatorPlus();
};

class NodeOperatorMinus : public NodeOperator
{
public:
    NodeOperatorMinus(NodeBase *left, NodeBase *right);
    virtual double eval();
    virtual NodeBase* clone() const;
    virtual ~NodeOperatorMinus();
};

class NodeOperatorTimes : public NodeOperator
{
public:
    NodeOperatorTimes(NodeBase *left, NodeBase *right);
    virtual double eval();
    virtual NodeBase* clone() const;
    virtual ~NodeOperatorTimes();
};

class NodeOperatorDivide : public NodeOperator
{
public:
    NodeOperatorDivide(NodeBase *left, NodeBase *right);
    virtual double eval();
    virtual NodeBase* clone() const;
    virtual ~NodeOperatorDivide();
};

#endif // NODES_H
