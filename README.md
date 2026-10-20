# CPP09 — C++98 STL

This module is designed to help you understand containers in C++.
Final module of the 42 Common Core. Focus: practical use of the C++98 Standard Template Library.

## Exercises

| # | Name | Description |
|---|------|-------------|
| ex00 | **Bitcoin Exchange** | Parse a CSV of historical BTC prices into a `std::map`; look up the rate for a given date. |
| ex01 | **RPN Calculator** | Evaluate postfix arithmetic expressions using a `std::stack`. |
| ex02 | **PmergeMe** | Sort a list of integers with the **Ford-Johnson merge-insertion sort**, benchmarking `std::vector` vs `std::deque`. |

## ex02 — Algorithm

1. Pair consecutive elements; sort each pair.
2. Recursively sort the "max" elements.
3. Binary-insert the "min" elements using **Jacobsthal numbers** to minimize comparisons.

Both containers are timed (µs / ms / s) and results printed side by side.

## Build

```bash
make   
