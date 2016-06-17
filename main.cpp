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
    Parser *parser;

    NodeBase* exp1 = parser->parse("(+ 1 1)");
    assert(exp1->eval() == 2);

    NodeBase* exp2 = parser->parse("(- 1 (+ 1 1))");
    assert(exp2->eval() == 1);

    NodeBase* exp3 = parser->parse("(* (- 1 (+ 1 1)) (+ 1 1))");
    assert(exp3->eval() == 2);

    NodeBase* exp4 = parser->parse("(/ 15 15)");
    assert(exp4->eval() == 2);

    assert(parser->parse("") == NULL);

    NodeBase* exp5 = parser->parse("55");
    assert(exp5->eval() == 55);

    NodeBase* exp6 = parser->parse("(55)");
    assert(exp6->eval() == 55);

    assert(parser->parse("( )") == NULL);

    assert(parser->parse("(+)") == NULL);

    assert(parser->parse("abc") == NULL);




    NodeBase *expression = parser->parse("(- (+ (* 3 5) (/ 4 2)) 1)");  //3*5+4/2-1");
    assert(expression->eval() == 16);


}




#include <cstdio>
const int ESC = 27;

int main(){
	std::cout << " ----------------------------------------------------------\n";
	std::cout << "|                          Hello!                          |\n";
	std::cout << "|    This is a program for addition, substraction,         |\n";
	std::cout << "|            multiplication and division                   |\n";
	std::cout << "|             written by Mishkina Elena.                   |\n";
	std::cout << " ----------------------------------------------------------\n\n";

    test_Parser();
//    std::string input;
//    std::cout << "Enter an expression: ";
//    std::getline(std::cin ,input); //read line
//    Parser *parser;
//    NodeBase *expression = parser->parse(input);  //3*5+4/2-1");
//    std::cout << input << " = " << expression->eval() << std::endl;

//	while (true){
//		std::string input, dummy;
//		double result = 0.0;
//        NodeOperator* plus();
                
//		std::cout << "Enter an expression: ";
//		std::getline(std::cin ,input); //read line
//		try{

//			std::cout << input << " = " << result << "\n";
//		}
//		catch (std::exception& e) {
//			std::cout << input << " : exception: " << e.what() << '\n';
//		}
//		std::cout << "Press ESC to exit or any other key to continue: ";
//		if (std::cin.get() == ESC)
//			break;
//                std::getline(std::cin, dummy); //clean stream
//	}
	return 0;
}

