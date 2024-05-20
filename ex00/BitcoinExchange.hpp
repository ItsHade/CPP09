#pragma once

#include <cstdlib>
#include <sstream>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>

#define DATABASE_NAME "data.csv"

class BitcoinExchange
{

public :

	BitcoinExchange(int argc, char *filename);
	BitcoinExchange(BitcoinExchange const & copy);
	~BitcoinExchange(void);

	BitcoinExchange & operator =(BitcoinExchange const & src);

	void Run(void);
	void InitData(void);
	void InitFile(void);
	void FillDatabase(void);
	void FillDate(std::string line);
	void CheckDateFormat(std::string date) const;
	void Convert(std::string line);
	std::string FindClosestDate(std::string dateStr);

	class WrongArgumentException : public std::exception {
		public :
			const char *what() const throw();
	};

	class InvalidDataBaseException : public std::exception {
		public :
			const char *what() const throw();
	};

	class TooLargeNumberException : public std::exception {
		public :
			const char *what() const throw();
	};

	class NegativeNumberException : public std::exception {
		public :
			const char *what() const throw();
	};

	class WrongDateFormatException : public std::exception {
		public :
			const char *what() const throw();
	};

	class InvalidDateException : public std::exception {
		public :
			const char *what() const throw();
	};

	class InvalidFileException : public std::exception {
		public :
			const char *what() const throw();
	};

	class InvalidInputException : public std::exception {
		public :
			const char *what() const throw();
	};

	class DateTooEarlyException : public std::exception {
		public :
			const char *what() const throw();
	};

private :

	std::string	_filename;
	std::ifstream		_file;
	std::ifstream		_database;
	std::map<std::string, float>	_data;

};
