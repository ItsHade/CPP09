#include "PmergeMe.hpp"

template<typename T>
static void InsertionSort(T & container)
{
	int tmp;
    typename T::iterator it;
	typename T::iterator prev;
	typename T::iterator j;
    for (it = container.begin(); it != container.end(); ++it)
	{
        tmp = *it;
        j = it;
        while (j != container.begin()) 
        {
            prev = j;
            --prev;
            if (*prev > tmp) {
                *j = *prev;
                --j;
            }
            else
                break;
        }
        *j = tmp;
    }
    return ;
}

template <typename T>
static void MergeInsertionSort(T & container)
{
    size_t	size = container.size();
	size_t	threshold = 100;  // "if the size of the list is small insertion sort runs faster"


    //We will split the list by 2 until the size is under 100 then we will perform insertion sort on the sub list
	if (size > threshold)
	{
        //Split initial list into 2
		typename T::iterator begin = container.begin();
		typename T::iterator mid = container.begin();
		std::advance(mid, container.size() / 2);
		typename T::iterator end = container.end();
		T left(begin, mid);
    	T right(mid, end);

        //Recurive call to MergeInsertionSort
		if (left.size() > 1)
			MergeInsertionSort(left);
		if (right.size() > 1)
    		MergeInsertionSort(right);
        
        //At the end of recursion -> merge back everything
		std::merge(left.begin(), left.end(), right.begin(), right.end(), container.begin());
	}
    else
    	InsertionSort(container);
    return ;
}

PmergeMe::PmergeMe(char **args)
{
    if (*args == NULL)
        throw PmergeMe::InvalidArgumentsException();
    _vectorSortTime = 0;
    _dequeSortTime = 0;
    clock_t vectorStart = clock();
    for (int i = 0; args[i]; i++)
    {
        std::string nbStr = args[i];
        if (nbStr.empty())
            throw PmergeMe::InvalidArgumentsException();
        int nb = StringToInt(nbStr);
        _vector.push_back(nb);
    }
    clock_t vectorEnd = clock();
    _vectorSortTime += difftime(vectorEnd, vectorStart) / (CLOCKS_PER_SEC / 1000000);

    //gestion des donnees
    clock_t dequeStart = clock();
    for (int i = 0; args[i]; i++)
    {
        std::string nbStr = args[i];
        if (nbStr.empty())
            throw PmergeMe::InvalidArgumentsException();
        int nb = StringToInt(nbStr);
        _deque.push_back(nb);
    }
    clock_t dequeEnd = clock();
    _vectorSortTime += difftime(dequeEnd, dequeStart) / (CLOCKS_PER_SEC / 1000000);
    return ;
}

PmergeMe::PmergeMe(PmergeMe const & copy)
{
    *this = copy;
    return ;
}

PmergeMe::~PmergeMe(void)
{
    return ;
}

PmergeMe & PmergeMe::operator =(PmergeMe const & src)
{
    _vector = src._vector;
    _deque = src._deque;
    return (*this);
}

int PmergeMe::StringToInt(std::string str)
{
    int nb = 0;

    for (size_t i = 0; i < str.size(); i++)
    {
        if (isdigit(str[i]))
        {
            nb = 10 * nb + (str[i] - 48);
            if (nb < 0)
                throw InvalidArgumentsException();
        }
        else
            throw InvalidArgumentsException();
    }
    return (nb);
}

void PmergeMe::DisplayContainers(std::string const & pre) const
{
    std::cout << pre;
    for (std::vector<int>::const_iterator it = _vector.begin(); it != _vector.end(); it++)
    {
        std::cout << *it;
        if (it + 1 != _vector.end())
            std::cout << " "; 
    }
    std::cout << std::endl;
    return ;
}

template <typename T>
void PmergeMe::DisplayTime(T const & container) const
{
    double time = 0;
    std::cout << "Time to process a range of ";
    std::cout << std::setw(3);
    std::cout << container.size() << " elements with "; 
    if (typeid(container) == typeid(std::vector<int>))
    {
        std::cout << "std::vector : ";
        time = _vectorSortTime;

    }
    else if (typeid(container) == typeid(std::deque<int>))
    {
        std::cout << "std::deque : ";
        time = _dequeSortTime;
    }
    else
        throw InvalidContainerTypeException();
    std::cout << std::setprecision(6) << time << " us" << std::endl;
    return ;
}

void PmergeMe::Sort(void)
{
    DisplayContainers("Before: ");
    SortVector();
    SortDeque();
    DisplayContainers("After: ");
    DisplayTime(_vector);
    DisplayTime(_deque);
    return ;
}

void PmergeMe::SortVector(void)
{
    clock_t start = clock();
    MergeInsertionSort(_vector);
    clock_t end = clock();
    double d = std::difftime(end, start) / (CLOCKS_PER_SEC / 1000000);
    _vectorSortTime += d;
    return ;
}

void PmergeMe::SortDeque(void)
{
    clock_t start = clock();
    MergeInsertionSort(_deque);
    clock_t end = clock();
    double d = std::difftime(end, start) / (CLOCKS_PER_SEC / 1000000);
    _dequeSortTime += d;
    return ;
}

const char *PmergeMe::InvalidArgumentsException::what() const throw()
{
    return ("invalid arguments or no arguments.");
}

const char *PmergeMe::InvalidContainerTypeException::what() const throw()
{
    return ("container type doesn't correspond to std::vector or std::deque");
}