#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
        return (-1);
    try
    {
        PmergeMe merge(argv + 1);
        merge.Sort();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error" << std::endl;
        return (-1);
    }


    return (0);
}