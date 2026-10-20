#include "PmergeMe.hpp"

#include <cstdlib>
#include <cctype>
#include <ctime>
#include <iostream>
#include <string>

bool parse_num(std::string str)
{
	if (str.empty())
		return false;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(static_cast<unsigned char>(str[i])))
			return false;
	}
	return true;
}

void print_sequence(const std::vector<int> &vec, const std::string &label)
{
	std::cout << label;
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
	{
		std::cout << *it;
		if (it + 1 != vec.end())
			std::cout << ' ';
	}
	std::cout << std::endl;
}

void print_deque(const std::deque<int> &d, const std::string &label)
{
    std::cout << label;
    for (std::deque<int>::const_iterator it = d.begin(); it != d.end(); ++it)
    {
        std::cout << *it;
        if (it + 1 != d.end())
            std::cout << ' ';
    }
    std::cout << std::endl;
}

int main(int arc, char **arv)
{
	if (arc == 1)
	{
		std::cerr << "Error: You must input a sequence of num\n";
		return 1;
	}

	std::vector<int> vec;
	std::deque<int> deq;
	for (int i = 1; i < arc; i++)
	{
		if (!parse_num(arv[i]))
		{
			std::cerr << "Error: You must input valid num\n";
			return 1;
		}
		int out = std::atoi(arv[i]);
		vec.push_back(out);
		deq.push_back(out);
	}

	PmergeMe process;
	print_sequence(vec, "Before: ");

	clock_t start = clock();
	process.sortVector(vec);
	clock_t end = clock();
	double vec_time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;

	start = clock();
	process.sortDeque(deq);
	end = clock();
	double deq_time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;

	print_deque(deq, "After: ");
	std::cout << "Time to process a range of " << vec.size()
		<< " elements with std::vector : " << vec_time << " us" << std::endl;
	std::cout << "Time to process a range of " << deq.size()
		<< " elements with std::deque : " << deq_time << " us" << std::endl;
	return 0;
}
