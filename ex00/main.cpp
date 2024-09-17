#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
	switch (argc)
	{
		case 2: 
		{
			Btc btc;
			btc.parse(argv[1]);
			return (0);
		}
		default:
			std::cout << "Wrong number of arguments" << std::endl;
	}
}
