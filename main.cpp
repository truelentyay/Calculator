// Task.cpp: Task from CQG, Mishkina Elena.

#include <string>
#include <cmath>
#include <cctype>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cassert>
#include <cstddef>
#include "nodes.h"
#include "parser.h"
#include "process.h"

void iAssert(bool expression, const std::string& description)
{
    if (expression)
    {
        std::cout << "[V]";
    }
    else
    {
        std::cout << "[-]";
    }

    std::cout << " " << description << std::endl;
}

void test_nodes()
{
    //Node *n1(5), *n2(7), *n3(6);
    Node *n1 = new Node(5);
    Node *n2 = new Node(7);
    Node *n3 = new Node(6);
    NodeOperatorPlus* plus;
    plus = new NodeOperatorPlus(n1, n2);
    assert(plus->eval() == 12);

    NodeOperatorMinus* minus = new NodeOperatorMinus(plus, n3);
    assert(minus->eval() == 6);

    NodeOperatorTimes* tim = new NodeOperatorTimes(minus, minus);
    assert(tim->eval() == 36);

    NodeOperatorDivide* divi = new NodeOperatorDivide(plus, minus);
    assert(divi->eval() == 2);

    std::cout << "Done!" << std::endl;
    delete n1;
    delete n2;
    delete n3;
    delete plus;
    delete minus;
    delete tim;
    delete divi;
}

void test_Parser()
{
    Parser parser;
    std::string str = "(+ 1 1)";
    NodeBase* exp1 = parser.parse(str);
    iAssert(exp1->eval() == 2, "Test 1");

    str = "(- 1 (+ 1 1))";
    NodeBase* exp2 = parser.parse(str);
    iAssert(exp2->eval() == -1, "Test 2");

    size_t pos1 = parser.fnd_operator(str);
    iAssert(pos1 == 1, "Test fnd_operator");

    size_t pos2 = parser.fnd_arg_end(5, str);
    iAssert(pos2 == 11, "Test fnd_arg_end");

    size_t pos3 = parser.fnd_next_space(3, str);
    iAssert(pos3 == 4, "Test fnd_nxt_space");

    str = "(* (- 1 (+ 1 1)) (+ 1 1))";
    NodeBase* exp3 = parser.parse(str);
    iAssert(exp3->eval() == -2, "Test 3");

    str = "(/ 15 15)";
    NodeBase* exp4 = parser.parse(str);
    iAssert(exp4->eval() == 1, "Test 4");

    str = "(+ 1 1)";
    iAssert(parser.parse("") == NULL, "Test 5");

//    str = "55";
//    NodeBase* exp5 = parser.parse(str);
//    iAssert(exp5->eval() == 55, "Test 6");

//    str = "(55)";
//    NodeBase* exp6 = parser.parse(str);
//    iAssert(exp6->eval() == 55, "Test 7");

    str = "( )";
    iAssert(parser.parse(str) == NULL, "Test 8");

    str = "(+)";
    iAssert(parser.parse(str) == NULL, "Test 9");

    str = "abc";
    iAssert(parser.parse(str) == NULL, "Test 10");

    str = "(- (+ (* 3 5) (/ 4 2)) 1)";
    NodeBase *expression = parser.parse(str);  //3*5+4/2-1");
    iAssert(expression->eval() == 16, "Test 11");

}


void performTests()
{
    test_nodes();
    test_Parser();
}


#include <cstdio>
const int ESC = 27;

int main(){


    try
    {
        performTests();
        Process process;
        return process.run();
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Some exception" << std::endl;
    }

    return -1;
}

