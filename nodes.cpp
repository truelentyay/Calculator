#include "nodes.h"
#include <cstddef>

double NodeBase::eval()
{

}

NodeBase::~NodeBase()
{

}

Node::Node(double v)
{
    m_value = v;
}

double Node::eval()
{
    return m_value;
}

NodeBase *Node::clone() const
{
    return new Node(m_value);
}

Node::~Node()
{
    m_value = 0;
}


NodeOperator::NodeOperator(NodeBase *left, NodeBase *right)
    : m_left(left)
    , m_right(right)
{

}

NodeBase *NodeOperator::clone() const
{

}



NodeOperator::~NodeOperator()
{
    if (m_left != NULL)
    {
        delete m_left;
        m_left = NULL;
    }
    if (m_right != NULL)
    {
        delete m_right;
        m_right = NULL;
    }
}


NodeOperatorPlus::NodeOperatorPlus(NodeBase *left, NodeBase *right) : NodeOperator(left, right)
{}

double NodeOperatorPlus::eval()
{
    return m_left->eval()+m_right->eval();
}

NodeBase *NodeOperatorPlus::clone() const
{
    return new NodeOperatorPlus(m_left->clone(), m_right->clone());
}

NodeOperatorPlus::~NodeOperatorPlus()
{}

NodeOperatorMinus::NodeOperatorMinus(NodeBase *left, NodeBase *right) : NodeOperator(left, right)
{}

double NodeOperatorMinus::eval()
{
    return m_left->eval()-m_right->eval();
}

NodeBase *NodeOperatorMinus::clone() const
{
    return new NodeOperatorMinus(m_left->clone(), m_right->clone());
}

NodeOperatorMinus::~NodeOperatorMinus()
{}

NodeOperatorTimes::NodeOperatorTimes(NodeBase *left, NodeBase *right) : NodeOperator(left, right)
{}

double NodeOperatorTimes::eval()
{
    return m_left->eval()*m_right->eval();
}

NodeBase *NodeOperatorTimes::clone() const
{
    return new NodeOperatorTimes(m_left->clone(), m_right->clone());
}

NodeOperatorTimes::~NodeOperatorTimes()
{}

NodeOperatorDivide::NodeOperatorDivide(NodeBase *left, NodeBase *right) : NodeOperator(left, right)
{}

double NodeOperatorDivide::eval()
{
    return m_left->eval()/m_right->eval();
}

NodeBase *NodeOperatorDivide::clone() const
{
    return new NodeOperatorDivide(m_left->clone(), m_right->clone());
}

NodeOperatorDivide::~NodeOperatorDivide()
{}




