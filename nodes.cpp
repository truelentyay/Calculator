#include "nodes.h"
#include <cstddef>



Node::Node(double v)
{
    m_value = v;
}

double Node::eval()
{
    return m_value;
}

NodeBase* Node::clone()
{
    return new Node(m_value);
}



NodeOperator::NodeOperator(NodeBase* left, NodeBase* right)
    : m_left(left)
    , m_right(right)
{

}

NodeOperatorPlus::NodeOperatorPlus(NodeBase* left, NodeBase* right) : NodeOperator(left, right)
{}

double NodeOperatorPlus::eval()
{
    return m_left->eval()+m_right->eval();
}

NodeBase * NodeOperatorPlus::clone()
{
    return new NodeOperatorPlus(m_left->clone(), m_right->clone());
}

NodeOperatorMinus::NodeOperatorMinus(NodeBase* left, NodeBase* right) :
    NodeOperator(left, right)
{}

double NodeOperatorMinus::eval()
{
    return m_left->eval()-m_right->eval();
}

NodeBase * NodeOperatorMinus::clone()
{
    return new NodeOperatorMinus(m_left->clone(), m_right->clone());
}

NodeOperatorTimes::NodeOperatorTimes(NodeBase* left, NodeBase* right) : NodeOperator(left, right)
{}

double NodeOperatorTimes::eval()
{
    return m_left->eval()*m_right->eval();
}

NodeBase * NodeOperatorTimes::clone()
{
    return new NodeOperatorTimes(m_left->clone(), m_right->clone());
}

NodeOperatorDivide::NodeOperatorDivide(NodeBase* left, NodeBase* right) : NodeOperator(left, right)
{}

double NodeOperatorDivide::eval()
{
    return m_left->eval()/m_right->eval();
}

NodeBase * NodeOperatorDivide::clone()
{
    return new NodeOperatorDivide(m_left->clone(), m_right->clone());
}






NodeBase::NodeBase()
{
}

NodeBase::~NodeBase()
{

}
