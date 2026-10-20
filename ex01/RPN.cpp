#include "RPN.hpp"

#include <cctype>
#include <iostream>
#include <stdexcept>

RPN::RPN()
{
}

RPN::RPN(const std::string& line) : line(line)
{
}

RPN::RPN(const RPN& other) : stack(other.stack), line(other.line)
{
}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
	{
		stack = other.stack;
		line = other.line;
	}
	return (*this);
}

RPN::~RPN()
{
}

int RPN::pops()
{
	int value = stack.top();
	stack.pop();
	return (value);
}

void RPN::calculate(char op)
{
	if (stack.size() < 2)
		throw std::runtime_error("Error");

	int a = pops();
	int b = pops();

	switch (op)
	{
		case '+':
			stack.push(b + a);
			break;
		case '-':
			stack.push(b - a);
			break;
		case '*':
			stack.push(b * a);
			break;
		case '/':
			if (a == 0)
				throw std::runtime_error("Error: divide 0");
			stack.push(b / a);
			break;
		default:
			throw std::runtime_error("Error");
	}
}

void RPN::evaluate()
{
	if (line.empty())
		throw std::runtime_error("Error");

	for (size_t i = 0; i < line.size(); i++)
	{
		if (line[i] == ' ')
			continue;
		if (line[i] == '-' && i + 1 < line.size()
			&& std::isdigit(static_cast<unsigned char>(line[i + 1])))
			stack.push((line[++i] - '0') * -1);
		else if (std::isdigit(static_cast<unsigned char>(line[i])))
			stack.push(line[i] - '0');
		else
			calculate(line[i]);
	}
	if (stack.size() != 1)
		throw std::runtime_error("Error");
	std::cout << stack.top() << std::endl;
}
