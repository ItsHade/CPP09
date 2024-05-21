#pragma once

#include <algorithm>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <ctime> // time
#include <typeinfo> //type of variable
#include <iomanip> // how to display on cout (time)


class PmergeMe
{

public :

    PmergeMe(char **args);
    PmergeMe(PmergeMe const & copy);
    ~PmergeMe(void);

    PmergeMe & operator =(PmergeMe const & src);

    void Sort(void);

    class InvalidArgumentsException : public std::exception {
		public :
			const char *what() const throw();
	};

    class InvalidContainerTypeException : public std::exception {
		public :
			const char *what() const throw();
	};

private :

    std::vector<int> _vector;
    std::deque<int> _deque;
    double  _vectorSortTime;
    double  _dequeSortTime;

    void SortVector(void);
    void SortDeque(void);
    int  StringToInt(std::string str);

    void DisplayContainers(std::string const & pre) const;
 
    template <typename T>
    void DisplayTime(T const & container) const;
    

};