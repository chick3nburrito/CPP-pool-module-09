#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>

class BitcoinExchange
{
	private:
		std::map<std::string, double> data;

		bool load(const std::string& file);
		bool parse(const std::string& str, double& price) const;
		bool checkDate(const std::string& date) const;
		double getRate(const std::string& day, bool& ok) const;
		bool process(const std::string& line) const;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();
		bool run(const std::string& file);
};

#endif
