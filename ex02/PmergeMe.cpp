#include "PmergeMe.hpp"

#include <algorithm>

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	(void)other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	(void)other;
	return (*this);
}

PmergeMe::~PmergeMe()
{
}

size_t	jacobsthal(size_t n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

void	PmergeMe::sortVector(std::vector<int> &vec)
{
	std::vector<int>	win;
	std::vector<int>	pend;

	if (vec.size() <= 1)
		return ;

	bool	has_odd = (vec.size() % 2 != 0);
	int	odd = 0;
	if (has_odd)
		odd = vec.back();

	size_t	limit = vec.size();
	if (has_odd)
		limit--;

	for (size_t	i = 0; i < limit; i += 2)
	{
		if (vec[i] > vec[i + 1])
		{
			win.push_back(vec[i]);
			pend.push_back(vec[i + 1]);
		}
		else
		{
			win.push_back(vec[i + 1]);
			pend.push_back(vec[i]);
		}
	}

	std::vector<int>	old = win;
	PmergeMe::sortVector(win);

	std::vector<int>	n_pend;
	std::vector<bool>	used(old.size(), false);
	for (size_t	i = 0; i < win.size(); i++)
	{
		for (size_t	j = 0; j < old.size(); j++)
		{
			if (!used[j] && old[j] == win[i])
			{
				n_pend.push_back(pend[j]);
				used[j] = true;
				break;
			}
		}
	}
	pend = n_pend;

	if (pend.empty())
		return ;

	win.insert(win.begin(), pend[0]);
	std::vector<bool>	inserted(pend.size(), false);
	inserted[0] = true;

	size_t	k = 1;
	while (true)
	{
		size_t	index = jacobsthal(k + 1);
		if (index > pend.size())
			index = pend.size();
		for (size_t	i = index; i >= 1; i--)
		{
			size_t	pend_index = i - 1;
			if (!inserted[pend_index])
			{
				std::vector<int>::iterator	position = std::upper_bound(
					win.begin(), win.end(), pend[pend_index]);
				win.insert(position, pend[pend_index]);
				inserted[pend_index] = true;
			}
		}

		bool	complete = true;
		for (size_t	i = 0; i < inserted.size(); i++)
		{
			if (!inserted[i])
			{
				complete = false;
				break;
			}
		}
		if (complete)
			break ;
		k++;
	}

	if (has_odd)
	{
		std::vector<int>::iterator	position = std::upper_bound(
			win.begin(), win.end(), odd);
		win.insert(position, odd);
	}
	vec = win;



}

void	PmergeMe::sortDeque(std::deque<int> &deq)
{
	std::deque<int>	win;
	std::deque<int>	pend;

	if (deq.size() <= 1)
		return ;

	bool	has_odd = (deq.size() % 2 != 0);
	int	odd = 0;
	if (has_odd)
		odd = deq.back();

	size_t	limit = deq.size();
	if (has_odd)
		limit--;

	for (size_t	i = 0; i < limit; i += 2)
	{
		if (deq[i] > deq[i + 1])
		{
			win.push_back(deq[i]);
			pend.push_back(deq[i + 1]);
		}
		else
		{
			win.push_back(deq[i + 1]);
			pend.push_back(deq[i]);
		}
	}

	std::deque<int>	old = win;
	PmergeMe::sortDeque(win);

	std::deque<int>	n_pend;
	std::vector<bool>	used(old.size(), false);
	for (size_t	i = 0; i < win.size(); i++)
	{
		for (size_t	j = 0; j < old.size(); j++)
		{
			if (!used[j] && old[j] == win[i])
			{
				n_pend.push_back(pend[j]);
				used[j] = true;
				break;
			}
		}
	}
	pend = n_pend;

	if (pend.empty())
		return ;

	win.insert(win.begin(), pend[0]);
	std::vector<bool>	inserted(pend.size(), false);
	inserted[0] = true;

	size_t	k = 1;
	while (true)
	{
		size_t	index = jacobsthal(k + 1);
		if (index > pend.size())
			index = pend.size();
		for (size_t	i = index; i >= 1; i--)
		{
			size_t	pend_index = i - 1;
			if (!inserted[pend_index])
			{
				std::deque<int>::iterator	position = std::upper_bound(
					win.begin(), win.end(), pend[pend_index]);
				win.insert(position, pend[pend_index]);
				inserted[pend_index] = true;
			}
		}

		bool	complete = true;
		for (size_t	i = 0; i < inserted.size(); i++)
		{
			if (!inserted[i])
			{
				complete = false;
				break;
			}
		}
		if (complete)
			break ;
		k++;
	}

	if (has_odd)
	{
		std::deque<int>::iterator	position = std::upper_bound(
			win.begin(), win.end(), odd);
		win.insert(position, odd);
	}
	deq = win;
}
