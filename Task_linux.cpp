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

// Correct operations
//const std::string add = "+";
//const std::string sub = "-";
//const std::string mul = "*";
//const std::string divi = "/";
/*
class node {
    std::string value, oper;
    node *l, *r;
    double res;
    std::string binary_operation();
    std::string find_first_max_priority();
    std::string left();
    std::string right();
public:
    node (std::string v = "", std::string o = ""){
            value = v;
            oper = o;
            node *l = 0;
            node *r = 0;
            res = 0;
    }

    node *lnode(){
        return l;
    }
    node *rnode(){
        return r;
    }
    std::string op(){
        return oper;
    }
    std::string val(){
        return value;
    }

    double calculate(node *&tree){
        if (tree->lnode() != 0 && tree->rnode() != 0){
            calculate(l);
            double res = 0.0;
            double arg1 = 0.0;
            double arg2 = 0.0;

            arg1 = atof(l->val().c_str()); //string to double number
            arg2 = atof(r->val().c_str());

            res = binary_operation(arg1, arg2, oper);
            calculate(r);
            return res;
        }
    }

    void add_node(std::string v, node *&new_tree){
        if (new_tree == 0){
            std::string lexp = "";
            std::string rexp = "";
            new_tree = new node;
            value = v;
            oper = find_first_max_priority(value);
            lexp = left(value, oper);
            rexp = right(value, oper);
            l = r = 0;
            if(lexp != ""){
                if (new_tree != 0) add_node(lexp, l);
                else{
                    new_tree = new node;
                    value = v;
                    oper = find_first_max_priority(value);
                    lexp = left(value, oper);
                    rexp = right(value, oper);
                    l = r = 0;
                }
            }
            if (rexp != 0){
                if (new_tree != 0) add_node(rexp, r);
                else{
                    new_tree = new node;
                    value = v;
                    oper = find_first_max_priority(value);
                    rexp = right(value, oper);
                    rexp = right(value, oper);
                    l = r = 0;
                }
            }
        }
    }
};



std::string binary_operation(double arg1, double arg2, std::string oper){
    double res;
    bool flag = false; // true - operation is correct
    if (oper == add){
        res = arg1 + arg2; flag = true;
    }
    if (oper == sub){
        res = arg1 - arg2; flag = true;
    }
    if (oper == mul){
        res = arg1*arg2; flag = true;
    }
    if (oper == divi){
        if (arg2 != 0)
            res = arg1 / arg2;
        else
            throw std::runtime_error("Result is not a number!");
        flag = true;
    }
    if (!flag) throw std::runtime_error("Expression is not found!");
    return res;
}

std::string find_first_max_priority(std::string str){
    size_t pos1, pos2, pos3, pos4;
    pos1 = str.find_first_of(mul);
    pos2 = str.find_first_of(divi);
    pos3 = str.find_first_of(add);
    pos4 = str.find_first_of(sub);
    if (pos1 != std::string::npos || pos2 != std::string::npos)
        if (pos1 < pos2)
            return mul;
        else return divi;
    else
        if (pos3 != std::string::npos || pos4 != std::string::npos)
            if (pos3 < pos4)
                return add;
            else return sub;
        else return str;
}

std::string left  (std::string str, std::string oper){
    std::string left = "";
    size_t pos;
    pos = str.find_first_of(oper);
    if (pos!=std::string::npos)
        left = str.substr(0, pos-1);
    return left;
}
std::string right  (std::string str, std::string oper){
    std::string right = "";
    size_t pos;
    pos = str.find_first_of(oper);
    if (pos!=std::string::npos)
        right = str.substr(pos);
    return right;
}*/



void test_nodes()
{
    Node n1(5), n2(7), n3(6);
    NodeOperatorPlus plus(n1, n2);
    assert(plus.eval() == 12);

    NodeOperatorMinus minus(plus, n3);
    assert(minus.eval() == 6);

    NodeOperatorTimes multiply(minus, minus);
    assert(multiply.eval() == 36);

    NodeOperatorDivide divi(plus, minus);
    assert(divi.eval() == 2);

    std::cout << "Done!" << std::endl;
}

void test_Parser()
{
    Parser parser;

    NodeBase expression = parser.parse("");
    assert(expression.eval() == ??);

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

    test_nodes();

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

