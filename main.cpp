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

    NodeOperatorMinus* minus = new NodeOperatorMinus(plus->clone(), n3);
    assert(minus->eval() == 6);

    NodeOperatorTimes* tim = new NodeOperatorTimes(minus->clone(), minus->clone());
    assert(tim->eval() == 36);

    NodeOperatorDivide* divi = new NodeOperatorDivide(plus->clone(), minus->clone());
    assert(divi->eval() == 2);

    std::cout << "Done!" << std::endl;
    //delete n1;
    //n1 = NULL;
    //delete n2;
    //n2 = NULL;
    //delete n3;
    //n3 = NULL;
    delete plus;
    plus = NULL;
    delete minus;
    minus = NULL;
    delete tim;
    tim = NULL;
    delete divi;
    divi = NULL;
}

void test_Parser()
{
    Parser parser;
    std::string str = "(+ 5 (+ 10 1))";
    Input input2(str); //= new Input(str);
    size_t pos1 = parser.findOperation(input2);
    iAssert(pos1 == '+', "Test findOperation");
    iAssert(input2.getPos() == 3, "Test getPos findOperation");


    parser.findLeftOperand(input2);
    iAssert(input2.getPos() == 5, "Test getPos findLeftOperand");

    NodeBase* exp2 = parser.parse(input2);
    iAssert(exp2->eval() == 16, "Test 2");

    str = "(+ 1 1)";
    Input input1(str);// = new Input(str);
    NodeBase* exp1 = parser.parse(input1);
    iAssert(exp1->eval() == 2, "Test 1");

    str = str = "(* (- 1 (+ 1 1)) (+ 1 1))";
    Input input3(str);// = new Input(str);
    NodeBase* exp3 = parser.parse(input3);
    iAssert(exp3->eval() == -2, "Test 3");

    str = "(/ 15 15)";
    Input input4(str);// = new Input(str);
    NodeBase* exp4 = parser.parse(input4);
    iAssert(exp4->eval() == 1, "Test 4");

    Input input5("");// = new Input("");
    iAssert(parser.parse(input5) == NULL, "Test 5");

//    str = "55";
//    NodeBase* exp5 = parser.parse(str);
//    iAssert(exp5->eval() == 55, "Test 6");

//    str = "(55)";
//    NodeBase* exp6 = parser.parse(str);
//    iAssert(exp6->eval() == 55, "Test 7");

    str = "( )";
    Input input8(str);// = new Input(str);
    iAssert(parser.parse(input8) == NULL, "Test 8");

    str = "(+)";
    Input input9(str);// = new Input(str);
    iAssert(parser.parse(input9) == NULL, "Test 9");

    str = "abc";
    Input input10(str);// = new Input(str);
    iAssert(parser.parse(input10) == NULL, "Test 10");

    str = "(- (+ (* 3 5) (/ 4 2)) 1)";
    Input input11(str);// = new Input(str);
    NodeBase *expression = parser.parse(input11);  //3*5+4/2-1");
    iAssert(expression->eval() == 16, "Test 11");

    delete exp1;
    exp1 = NULL;
    delete exp2;
    exp2 = NULL;
    delete exp3;
    exp3 = NULL;
    delete exp4;
    exp4 = NULL;
    delete expression;
    expression = NULL;
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
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Some exception" << std::endl;
    }

    return -1;
}

