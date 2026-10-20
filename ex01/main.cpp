#include "RPN.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>

int main(int arc, char **arv)
{
	try
	{
		if (arc != 2)
			throw std::runtime_error("Error: You must provide args");
		RPN rpn(arv[1]);
		rpn.evaluate();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
