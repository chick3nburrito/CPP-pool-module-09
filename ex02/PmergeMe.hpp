#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <deque>
#include <iostream>
#include <vector>
#include <cstddef>

size_t	jacobsthal(size_t n);

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();

	void	sortVector(std::vector<int> &vec);
	void	sortDeque(std::deque<int> &deq);

	static void	printSequence(const std::vector<int> &vec, const std::string &label);
};

#endif
