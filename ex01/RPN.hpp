#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RPN
{
	private:
		std::stack<int> stack;
		std::string		line;

		int	pops();
		void	calculate(char op);

	public:
		RPN();
		RPN(const std::string& line);
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		void	evaluate();
};

#endif
