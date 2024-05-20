#include "RPN.hpp"

int main(int argc, char **argv)
{
    try
    {
        RPN rpn(argc, argv[1]);
        rpn.result();
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return (0);
}