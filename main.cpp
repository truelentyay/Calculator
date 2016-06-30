// Task.cpp: Task from CQG, Mishkina Elena.

#include <string>
#include <cmath>
#include <cctype>
#include <cstring>

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cassert>
#include <cstddef>
#include "nodes.h"
#include "parser.h"
#include "process.h"
#include "my_smartptr.h"

void iAssert(bool expression, const std::string& description)
{
    if (expression)
    {
        std::cout << "[V]";
        std::cout << "  Congrats! " << description << " is good!" << std::endl;
    }
    else
    {
        std::cout << "[-]";
        std::cout << "  Sorry! " << description << " is bad!" << std::endl;
    }

   // std::cout << " " << description << std::endl;
}

void test_nodes()
{
    SmartPtr<Node> pNode1(new Node(5));
    SmartPtr<Node> pNode2(new Node(7));
    SmartPtr<Node> pNode3(new Node(6));

    SmartPtr<NodeOperatorPlus> pPlus(new NodeOperatorPlus(pNode1->clone(), pNode2->clone()));
    assert(pPlus->eval() == 12);

    SmartPtr<NodeOperatorMinus> pMinus(new NodeOperatorMinus(pPlus->clone(), pNode3->clone()));
    assert(pMinus->eval() == 6);

    SmartPtr<NodeOperatorTimes> pTim(new NodeOperatorTimes(pMinus->clone(), pMinus->clone()));
    assert(pTim->eval() == 36);

    SmartPtr<NodeOperatorDivide> pDivi(new NodeOperatorDivide(pPlus->clone(), pMinus->clone()));
    assert(pDivi->eval() == 2);

    std::cout << "Done!" << std::endl;
}

void test_Input()
{
    std::string str = "(+ 5 (+ 10 1))";
    token_Value t[9] = {LP, plus, number, LP, plus, number, number, RP, RP};
    std::vector<token_Value> tokens(t, t+9);

    {
        Input input(str);
        input.splitIntoTokens();
        Token first = input.find_expression()[0];
        iAssert(tokens[0] == first.getType(), "Split[0]");
    }

    Input input(str);
    input.splitIntoTokens();
    Token eighth = input.find_expression()[8];
    iAssert(tokens[8] == eighth.getType(), "Split[8]");

    size_t operation = input.find_operation();
    iAssert(operation == 1, "Found operation");

    Token token = input.getToken();
    iAssert(token.getValue<double>() == 5, "Next token");

    std::vector<Token> right = input.find_expression();
    token = right[2];
    iAssert(token.getValue<double>() == 10, "Found number");

    Input right_input(right);
    iAssert(right_input.getToken(3).getType() == number, "Found expression[3]");
    iAssert(right_input.getToken(4).getType() == RP, "Found expression[4]");
    iAssert(right_input.getToken(1).getType() == plus, "Found expression[1]");
    iAssert(right_input.findFirstOfAny(tokens, 1) == 1, "Found tokens");
}

void test_Parser()
{
    Parser parser;
    std::string str;

    {
        str = "(+ 5 (+ 10 1))";
        SmartPtr<NodeBase> exp(parser.parse(str));
        iAssert(exp.isValid(), "Root node");
        iAssert(exp->eval() == 16, "Parse(+ 5 (+ 10 1))");
    }

//    {
//        str = "(+ 5 (+ 10 1))";
//        SmartPtr<NodeBase> exp(parser.parse(str));
//        //std::cout << exp->eval();
//        iAssert(exp->eval() == 16, "Test 2");
//    }

    {
        str = "(+ 1 1)";
    //    Input input1(str);// = new Input(str);
        SmartPtr<NodeBase> exp(parser.parse(str));
        iAssert(exp->eval() == 2, "Parse(+ 1 1)");

    }

    {
        str = str = "(* (- 1 (+ 1 1)) (+ 1 1))";
        //Input input3(str);// = new Input(str);
        SmartPtr<NodeBase> exp(parser.parse(str));
        iAssert(exp->eval() == -2, "Parse(* (- 1 (+ 1 1)) (+ 1 1))");
    }

    {
        str = "(/ 15 15)";
     //   Input input4(str);// = new Input(str);
        SmartPtr<NodeBase> exp(parser.parse(str));
        iAssert(exp->eval() == 1, "Parse(/ 15 15)");
    }

    {
       // Input input5("");// = new Input("");
        iAssert(parser.parse("") == NULL, "Parse()");
    }

//    str = "55";
//    SmartPtr<NodeBase> exp5 = parser.parse(str);
//    iAssert(exp5->eval() == 55, "Test 6");

//    str = "(55)";
//    SmartPtr<NodeBase> exp6 = parser.parse(str);
//    iAssert(exp6->eval() == 55, "Test 7");

    {
        str = "( )";
        //  Input input8(str);// = new Input(str);
        iAssert(parser.parse(str) == NULL, "Parse( )");
    }


    {
        str = "(+)";
       // Input input9(str);// = new Input(str);
        iAssert(parser.parse(str) == NULL, "Parse(+)");
    }

    {
        str = "abc";
        //  Input input10(str);// = new Input(str);
        iAssert(parser.parse(str) == NULL, "Parse(abc)");
    }

    {
        str = "(- (+ (* 3 5) (/ 4 2)) 1)";
        //   Input input11(str);// = new Input(str);
        SmartPtr<NodeBase> exp(parser.parse(str));  //3*5+4/2-1");
        iAssert(exp->eval() == 16, "Parse(- (+ (* 3 5) (/ 4 2)) 1)");
    }
}


void performTests()
{
    test_nodes();
    test_Input();
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

