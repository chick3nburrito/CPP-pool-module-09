#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : data(other.data)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		data = other.data;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

std::string trim(const std::string& str)
{
	std::string::size_type start = 0;
	std::string::size_type end = str.size();

	while (start < str.size() && std::isspace(static_cast<unsigned char>(str[start])) != 0)
		++start;
	while (end > start && std::isspace(static_cast<unsigned char>(str[end - 1])) != 0)
		--end;
	return str.substr(start, end - start);
}

bool BitcoinExchange::parse(const std::string& str, double& price) const
{
	char* endPtr = 0;

	if (str.empty())
		return false;
	price = std::strtod(str.c_str(), &endPtr);
	if (endPtr == str.c_str())
		return false;
	while (*endPtr != '\0')
	{
		if (std::isspace(static_cast<unsigned char>(*endPtr)) == 0)
			return false;
		++endPtr;
	}
	return true;
}

bool BitcoinExchange::checkDate(const std::string& date) const
{
	int year;
	int month;
	int day;
	int maxDay;
	bool leap;

	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (size_t i = 0; i < date.size(); i++)
	{
		if (i != 4 && i != 7 && !std::isdigit(static_cast<unsigned char>(date[i])))
			return false;
	}
	year = std::atoi(date.substr(0, 4).c_str());
	month = std::atoi(date.substr(5, 2).c_str());
	day = std::atoi(date.substr(8, 2).c_str());
	if (year < 1 || month < 1 || month > 12 || day < 1)
		return false;

	leap = (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
	maxDay = 31;
	if (month == 4 || month == 6 || month == 9 || month == 11)
		maxDay = 30;
	else if (month == 2)
		maxDay = leap ? 29 : 28;
	return (day <= maxDay);
}

bool BitcoinExchange::load(const std::string& file)
{
	std::ifstream fin(file.c_str());
	std::string line;

	if (!fin.is_open())
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return false;
	}
	if (!std::getline(fin, line))
		return false;
	while (std::getline(fin, line))
	{
		std::string::size_type x = line.find(',');
		std::string day;
		double price;

		if (x == std::string::npos)
			continue;
		day = trim(line.substr(0, x));
		if (!checkDate(day) || !parse(trim(line.substr(x + 1)), price))
			continue;
		data[day] = price;
	}
	return !data.empty();
}

double BitcoinExchange::getRate(const std::string& day, bool& ok) const
{
	std::map<std::string, double>::const_iterator it = data.lower_bound(day);

	if (it != data.end() && it->first == day)
	{
		ok = true;
		return it->second;
	}
	if (it == data.begin())
	{
		ok = false;
		return 0;
	}
	if (it == data.end() || it->first > day)
		--it;
	ok = true;
	return it->second;
}

bool BitcoinExchange::process(const std::string& line) const
{
	std::string::size_type x = line.find('|');
	std::string day;
	std::string valueStr;
	double value;
	double rate;
	bool ok;

	if (x == std::string::npos)
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return false;
	}
	day = trim(line.substr(0, x));
	valueStr = trim(line.substr(x + 1));
	if (!checkDate(day) || !parse(valueStr, value))
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return false;
	}
	if (value < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	if (value > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	rate = getRate(day, ok);
	if (!ok)
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return false;
	}
	std::cout << day << " => " << value << " = " << (value * rate) << std::endl;
	return true;
}

bool BitcoinExchange::run(const std::string& file)
{
	std::ifstream fin(file.c_str());
	std::string line;

	if (!load("data.csv"))
		return false;
	if (!fin.is_open())
	{
		std::cerr << "Error: Couldnt open input file" << std::endl;
		return false;
	}
	if (!std::getline(fin, line))
		return false;
	while (std::getline(fin, line))
		process(line);
	return true;
}
