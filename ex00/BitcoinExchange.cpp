#include "BitcoinExchange.hpp"


static std::string RemoveWhiteSpaces(std::string line)
{
    std::string str;

    for (std::string::iterator it = line.begin(); it != line.end(); it++)
    {
        if (!std::isspace(*it))
            str += *it;
    }
    return (str);
}

static bool isLeapYear(unsigned int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}



BitcoinExchange::BitcoinExchange(int argc, char *filename)
{
    if (argc != 2)
        throw BitcoinExchange::WrongArgumentException();
    _filename = filename;
    InitData();
    InitFile();
    return ;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const & copy)
{
    *this = copy;
    return ;
}

BitcoinExchange::~BitcoinExchange(void)
{
    _file.close();
    _database.close();
    return ;
}

BitcoinExchange & BitcoinExchange::operator =(BitcoinExchange const & src)
{
    _filename = src._filename;
    return (*this);
}



void BitcoinExchange::InitData(void)
{
    _database.open(DATABASE_NAME);
    if (!_database.is_open())
    {
        throw BitcoinExchange::InvalidDataBaseException();
    }
    FillDatabase();
    return ;
}

void BitcoinExchange::InitFile(void)
{
    _file.open(_filename.c_str());
    if (!_file.is_open())
        throw BitcoinExchange::InvalidFileException();
    return ;
}

void BitcoinExchange::FillDatabase(void)
{
    std::string line;

    while (std::getline(_database, line))
        FillDate(line);
    return ;
}

void BitcoinExchange::FillDate(std::string line)
{
    line = RemoveWhiteSpaces(line);
    std::size_t separatorPos = line.find_first_of(",");

    if (separatorPos != std::string::npos)
    {
        std::string dateStr = line.substr(0, separatorPos);
        std::string valueStr = line.substr(separatorPos + 1, line.size());

        std::istringstream valueStream(valueStr);
        float value;
        if (valueStream >> value)
        {
            CheckDateFormat(dateStr);
            _data[dateStr] = value;
            return ;
        }
    }
    else
        throw BitcoinExchange::InvalidDataBaseException();
}

void BitcoinExchange::CheckDateFormat(std::string date) const
{
    // YYYY-MM-DD
    // 01 < DD < 31 (or 30 or february)
    // 01 < MM < 12
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        throw BitcoinExchange::WrongDateFormatException();
    std::istringstream issYear(date.substr(0, 4));
    std::istringstream issMonth(date.substr(5, 2));
    std::istringstream issDay(date.substr(8, 2));

    unsigned int year, month, day;
    issYear >> year;
    issMonth >> month;
    issDay >> day;

    const unsigned int dayPerMonth[12] = {31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year < 2000 || !(month >= 1 && month <= 12) || !(day >= 1 && day <= dayPerMonth[month - 1]))
        throw BitcoinExchange::InvalidDateException();
    return ;
}

void BitcoinExchange::Run(void)
{
    std::string line;

    while (std::getline(_file, line))
    {
        try
        {
            Convert(line);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return ;
}

void BitcoinExchange::Convert(std::string line)
{
    line = RemoveWhiteSpaces(line);
    std::size_t separatorPos = line.find_first_of('|');

    if (separatorPos != std::string::npos)
    {
        std::string dateStr = line.substr(0, separatorPos);
        std::string valueStr = line.substr(separatorPos + 1, line.size());

        std::istringstream valueStream(valueStr);
        float value;
        if (valueStream >> value)
        {
            CheckDateFormat(dateStr);
            if (value < 0)
                throw BitcoinExchange::NegativeNumberException();
            if (value > 1000)
                throw BitcoinExchange::TooLargeNumberException();
            std::string closestDate = FindClosestDate(dateStr);
            std::cout << closestDate << " => " << value << " = " << value * _data.at(closestDate) << std::endl;
        }
    }
    else
        throw BitcoinExchange::InvalidInputException();
    return ;
}

std::string BitcoinExchange::FindClosestDate(std::string dateStr)
{
    std::map<std::string, float>::iterator key = _data.upper_bound(dateStr); 
    if (key == _data.begin())
        throw BitcoinExchange::DateTooEarlyException();
    return (key->first);
}



const char *BitcoinExchange::WrongArgumentException::what() const throw()
{
    return ("could not open file.");
}

const char *BitcoinExchange::InvalidDataBaseException::what() const throw()
{
    return ("database is not valid.");
}

const char *BitcoinExchange::NegativeNumberException::what() const throw()
{
    return ("not a positive number.");
}

const char *BitcoinExchange::TooLargeNumberException::what() const throw()
{
    return ("number is too large.");
}

const char *BitcoinExchange::WrongDateFormatException::what() const throw()
{
    return ("invalid date format.");
}

const char *BitcoinExchange::InvalidDateException::what() const throw()
{
    return ("invalid date.");
}

const char *BitcoinExchange::InvalidFileException::what() const throw()
{
    return ("invalid input file.");
}

const char *BitcoinExchange::InvalidInputException::what() const throw()
{
    return ("not a valid input.");
}

const char *BitcoinExchange::DateTooEarlyException::what() const throw()
{
    return ("bitcoin didn't exist at that time");
}

