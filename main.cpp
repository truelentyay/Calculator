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
        std::cout << "  Sorry! " << description << " is failed!" << std::endl;
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

    Input input(str);
    input.splitIntoTokens();
    Token first = input.find_expression(0)[0];
    Token sixth = input.find_expression(0)[6];
    iAssert(tokens[0] == first.getType(), "Split[0]");
    iAssert(tokens[6] == sixth.getType(), "Split[6]");

    Token token = input.find_operation(0);
    iAssert(token.getType() == plus, "Found operation");

    token = input.nextToken(1);
    iAssert(token.getValue<double>() == 5, "Next token");

    std::vector<Token> right = input.find_expression(2);
    token = right[2];
    iAssert(token.getValue<double>() == 10, "Found number");

    Input right_input(right);
    iAssert(right_input.nextToken(3).getType() == RP, "Found expression[3]");
    iAssert(right_input.nextToken(4).getType() == RP, "Found expression[4]");
    std::cout << right_input.nextToken(4).getType() << std::endl;
    iAssert(right_input.nextToken(0).getType() == plus, "Found expression[0]");
    iAssert(right_input.findFirstOfAny(tokens, 1) == 1, "Found tokens");
}

void test_Parser()
{
    Parser parser;
    std::string str = "(+ 5 (+ 10 1))";
    Input input2(str); //= new Input(str);
    input2.splitIntoTokens();
    //parser.findOperation(input2);
    size_t pos1 = 0;
    Token op = input2.find_operation(pos1);
    iAssert(op.getType() == plus, "Test findOperation");
   // iAssert(input2.getPos() == 3, "Test getPos findOperation");
    Token n_token = input2.nextToken(pos1);
    iAssert(n_token.getType() == number, "Test getType");
    iAssert(n_token.getValue<double>() == 5, "Test getValue");



    ++pos1;
    Input r_input2 = input2.find_expression(pos1);
    SmartPtr<NodeBase> exp2_1(parser.parse(r_input2));
    iAssert(exp2_1.isValid(), "root node is not null");
    iAssert(exp2_1->eval() == 11, "Test 2");


 //   parser.findLeftOperand(input2);
   // iAssert(input2.getPos() == 5, "Test getPos findLeftOperand");
    {
        SmartPtr<NodeBase> exp(parser.parse(input2));
        std::cout << exp->eval();
        iAssert(exp->eval() == 16, "Test 2");
    }

    {
        str = "(+ 1 1)";
        Input input1(str);// = new Input(str);
        SmartPtr<NodeBase> exp1(parser.parse(input1));
        iAssert(exp1->eval() == 2, "Test 1");

    }

    str = str = "(* (- 1 (+ 1 1)) (+ 1 1))";
    Input input3(str);// = new Input(str);
    SmartPtr<NodeBase> exp3(parser.parse(input3));
    iAssert(exp3->eval() == -2, "Test 3");

    str = "(/ 15 15)";
    Input input4(str);// = new Input(str);
    SmartPtr<NodeBase> exp4(parser.parse(input4));
    iAssert(exp4->eval() == 1, "Test 4");

    Input input5("");// = new Input("");
    iAssert(parser.parse(input5) == NULL, "Test 5");

//    str = "55";
//    SmartPtr<NodeBase> exp5 = parser.parse(str);
//    iAssert(exp5->eval() == 55, "Test 6");

//    str = "(55)";
//    SmartPtr<NodeBase> exp6 = parser.parse(str);
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
    SmartPtr<NodeBase> expression(parser.parse(input11));  //3*5+4/2-1");
    iAssert(expression->eval() == 16, "Test 11");
}


void performTests()
{
    test_nodes();
    test_Input();
   // test_Parser();
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

