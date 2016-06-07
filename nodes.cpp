#include "nodes.h"
#include <cstddef>

double NodeBase::eval()
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

NodeOperator::NodeOperator(NodeBase &left, NodeBase &right)
    : m_left(left)
    , m_right(right)
{
}

//NodeOperator::NodeOperator()
//    : m_left(NULL)
//    , m_right(NULL)
//{
//}

NodeOperatorPlus::NodeOperatorPlus(NodeBase &left, NodeBase &right) : NodeOperator(left, right)
{}

double NodeOperatorPlus::eval()
{
   return m_left.eval()+m_right.eval();
}

NodeOperatorMinus::NodeOperatorMinus(NodeBase &left, NodeBase &right) : NodeOperator(left, right)
{}

double NodeOperatorMinus::eval()
{
   return m_left.eval()-m_right.eval();
}

NodeOperatorTimes::NodeOperatorTimes(NodeBase &left, NodeBase &right) : NodeOperator(left, right)
{}

double NodeOperatorTimes::eval()
{
   return m_left.eval()*m_right.eval();
}

NodeOperatorDivide::NodeOperatorDivide(NodeBase &left, NodeBase &right) : NodeOperator(left, right)
{}

double NodeOperatorDivide::eval()
{
   return m_left.eval()/m_right.eval();
}



