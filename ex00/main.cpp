#include "BitcoinExchange.hpp"

int main(int arc, char **arv)
{
	BitcoinExchange engine;

	if (arc != 2)
	{
		std::cerr << "Error: u must input ./btc file.csv\n";
		return 1;
	}
	engine.run(arv[1]);
	return 0;
}
