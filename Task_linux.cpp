// Task.cpp: Task from CQG, Mishkina Elena.

#include <string>
#include <cmath>
#include <cctype>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <sstream>

// Correct operations
const std::string add = "+";
const std::string sub = "-";
const std::string mul = "*";
const std::string divi = "/";

// To make to_str in linux
template <typename T>
std::string ToString(T val)
{
   std::stringstream stream;
   stream << val;
   return stream.str();
}

// A function to calculate operation
std::string binary_operation(std::string op1, std::string op2, std::string operation){
	std::string res;
	bool flag = false; // true - operation is correct
	double res_number = 0.0;
	double op1_number = 0.0;
	op1_number = atof(op1.c_str()); //string to double number
	double op2_number = 0.0;
	op2_number = atof(op2.c_str());
	if (operation == add){
		res_number = op1_number + op2_number; flag = true;
	}
	if (operation == sub){
		res_number = op1_number - op2_number; flag = true;
	}
	if (operation == mul){
		res_number = op1_number*op2_number; flag = true;
	}
	if (operation == divi){
		if (op2_number != 0)
			res_number = op1_number / op2_number; 
		else
			throw std::runtime_error("Result is not a number!");
		flag = true;
	}
	if (!flag) throw std::runtime_error("Expression is not found!");;
	res = ToString(res_number); 
	return res;
}

// A function to find left argument
std::string take_left_number(size_t pos, std::string expression){
	std::string left_number = "";
	if (!std::isdigit(expression[pos - 1]))  //invalid argument
		throw std::runtime_error("Wrong expression!");
	if (pos != 0 && std::isdigit(expression[pos - 1]))
		while (pos != 0 && (std::isdigit(expression[pos-1]) || expression[pos-1] == '.')){
			left_number = expression[pos-1] + left_number;
			pos--;
		}
	if (pos != 0 && expression[pos-1] == '-' && std::isdigit(expression[pos]) && !std::isdigit(expression[pos-2])){ //negative number
		left_number = expression[pos-1];
		while ((std::isdigit(expression[pos]) || expression[pos] == '.')){
			left_number = left_number + expression[pos];
			pos++;
		}
	}
	return std::string(left_number);
}

// A function to find right argument
std::string take_right_number(size_t pos, std::string expression){
	std::string right_number = "";
	size_t old_pos = pos;
	if (expression[pos + 1] != '-' && std::isdigit(expression[pos + 1]))
		while (  (std::isdigit(expression[pos+1]) || expression[pos+1] == '.')){
			right_number = right_number + expression[pos+1];
			pos++;
		}
	if (expression[old_pos + 1] == '-' && std::isdigit(expression[old_pos + 2])){ //negative number
		pos = old_pos;
		right_number = expression[pos + 1];
		while ((std::isdigit(expression[pos + 2]) || expression[pos + 2] == '.')){
			right_number = right_number + expression[pos + 2];
			pos++;
		}
	}
	if (!std::isdigit(expression[old_pos + 1]) && expression[old_pos + 1] != '-') //invalid argument
		throw std::runtime_error("Wrong expression!");
	return std::string(right_number);
}

// A function to find an expresion and a result of operation
std::string find_expression(std::string input, std::string operation1, std::string operation2){
	std::string res, op1, op2, expression, output = "";
	size_t pos1, pos2, min_pos = 0, pos_of_exp;
	std::string operation;
	while (output != input){
		output = input;
		pos1 = output.find_first_of(operation1, 1); //find needed operations
		pos2 = output.find_first_of(operation2, 1);
		if (pos1 != std::string::npos || pos2 != std::string::npos){
			if (pos1 < pos2){ //right order
				min_pos = pos1;
				operation = operation1;
			}
			else{
				min_pos = pos2;
				operation = operation2;
			}
				op1 = take_left_number(min_pos, output);
				op2 = take_right_number(min_pos, output);
				res = binary_operation(op1, op2, operation);
				expression = op1 + std::string(operation) + op2;
				pos_of_exp = output.find(expression);
				output = output.replace(pos_of_exp, expression.length(), res); //replace expression on result
				input = output;
				output = "";
		} //do while there's no more needed operations
	}
	return output;
}

// A function to find an expression in brackets
std::string find_brackets(std::string input){
	std::string res, expression, output = "";
	size_t begin_pos, end_pos;
	while (output != input){
		output = input;
		begin_pos = output.find_last_of("(");
		end_pos = output.find_first_of(")", begin_pos);
		if (begin_pos != std::string::npos && end_pos != std::string::npos){
			if (begin_pos < end_pos){
				expression = output.substr(begin_pos + 1, end_pos - begin_pos - 1);
				res = expression;
				res = find_expression(res, mul, divi);
				res = find_expression(res, sub, add);
				output = output.replace(begin_pos, expression.length()+2, res);
				input = output;
				output = "";
			}
			else
				throw std::runtime_error("Wrong expression!");
		}
		if ((begin_pos == std::string::npos && end_pos != std::string::npos) || (begin_pos != std::string::npos && end_pos == std::string::npos))
			throw std::runtime_error("Expected '(' or ')'");
	}
	return output;
}

// Check a result
std::string is_number(std::string input){
	bool f = false;
	std::string res = input;
	if (std::isdigit(input[0]) || input[0] == '-')
		for (unsigned int i = 1; i < input.length(); i++)
			if (std::isdigit(input[i]) || input[i] == '.')
				f = true;
			else{
				f = false;
				res = "";
				break;
			}
	else{
		f = false;
		res = "";
	}
	size_t pos;
	pos = input.find_first_of(".");
	if (f && pos != std::string::npos && (pos+4)<input.length())
		res = input.substr(0, pos+4); //take 3 signs after a dot
	return res;
}

// Calculate a result
double find_result(std::string input){
	std::string output;
	double result = 0.0;
	for (std::string::iterator it = input.begin(); it<input.end(); ++it) {
		if (*it == ' ') input.erase(it); //cut spaces
	}
	output = input;
	output = find_brackets(output); //priority = 1
	output = find_expression(output, mul, divi); //priority = 2
	output = find_expression(output, sub, add); //priority = 3
	output = is_number(output);
	if (output != "")
		result = atof(output.c_str()); //take result
	else
		throw std::runtime_error("Wrong expression!");
	return result;
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
	while (true){
		std::string input, dummy;
		double result = 0.0;
                
		std::cout << "Enter an expression: ";
		std::getline(std::cin ,input); //read line
		try{
			result = find_result(input);
			std::cout << input << " = " << result << "\n"; 
		}
		catch (std::exception& e) {
			std::cout << input << " : exception: " << e.what() << '\n';
		}
		std::cout << "Press ESC to exit or any other key to continue: ";
		if (std::cin.get() == ESC)
			break;
                std::getline(std::cin, dummy); //clean stream
	} 
	return 0;
}

