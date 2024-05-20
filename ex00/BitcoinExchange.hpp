#pragma once

#include <cstdlib>std::map<std::string, float>	_data;
#include <sstream>
#include <iostream>
#include <map>
#include <string>
#include <fstream>

class BitcoinExchange
{

public :

	BitcoinExchange(int argc, std::string filename);
	BitcoinExchange(BitcoinExchange const & copy);
	~BitcoinExchange();

	BitcoinExchange & operator =(BitcoinExchange const & src);

	void PutConversion(void);

private :

	const std::string	_filename;
	std::ifstream		_file;
	std::ifstream		_database;
	std::map<std::string, float>	_data;

};
