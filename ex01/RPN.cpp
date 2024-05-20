#include "RPN.hpp"

static bool isOperator(std::string &token)
{
    return (token.size() == 1 && token.find_first_of(OP) != std::string::npos);
}

static int addition(int nb1, int nb2)
{
    std::cout << "addition:" << std::endl;
    std::cout << "\tnb1: " << nb1 << std::endl;
    std::cout << "\tnb2: " << nb2 << std::endl;
    std::cout << "\t" << INT_MAX - nb2 << std::endl;
    if (nb1 > (INT_MAX - nb2) )
        throw RPN::IntOverflowException();
    return (nb1 + nb2);
}
// 1 > 2147483648 + (-8)

static int substraction(int nb1, int nb2)
{
    std::cout << "substraction:" << std::endl;
    std::cout << "\tnb1: " << nb1 << std::endl;
    std::cout << "\tnb2: " << nb2 << std::endl;
    if (nb1 < INT_MIN + nb2)
        throw RPN::IntOverflowException();
    return (nb1 - nb2);
}

static int multiplication(int nb1, int nb2)
{
    std::cout << "multiplication:" << std::endl;
    std::cout << "\tnb1: " << nb1 << std::endl;
    std::cout << "\tnb2: " << nb2 << std::endl;
    if (nb1 != 0 && nb2 != 0)
    {
        if (nb1 > INT_MAX / nb2)
            throw RPN::IntOverflowException();
    }
    return (nb1 * nb2);
}

static int division(int nb1, int nb2)
{
    std::cout << "division:" << std::endl;
    std::cout << "\tnb1: " << nb1 << std::endl;
    std::cout << "\tnb2: " << nb2 << std::endl;
    if (nb2 == 0)
        throw RPN::DivisionByZeroException();
    return (nb1 / nb2);
}

static int ProcessOperation(int nb1, int nb2, const std::string &op)
{
    static int (*operations[])(int, int) = {addition, substraction, multiplication, division};

    static std::string operators = OP;
    return (operations[operators.find(op)](nb1, nb2));
}

static int GetOperand(const std::string &op)
{
    if (op.size() == 1 && isdigit(op[0]))
        return (op[0] - 48);
    else
        throw RPN::UnexpectedTokenException();
}

RPN::RPN(int argc, char *operations)
{
    if (argc != 2)
        throw RPN::WrongArgumentException();
    if (operations == NULL || operations[0] == 0)
        throw RPN::EmptyArgumentException();
    _operations = operations;
}

RPN::RPN(RPN const & copy)
{
    *this = copy;
    return ;
}

RPN::~RPN(void)
{
    return ;
}

RPN & RPN::operator=(RPN const & src)
{
    _operations = src._operations;
    return (*this);
}

void RPN::result(void) const
{
    std::stack<int> operands;
    ProcessStack(operands);
    if (operands.size() > 1)
        throw RPN::TooManyOperandsException();
    std::cout << operands.top() << std::endl;
    return ;
}

void RPN::ProcessStack(std::stack<int> &operands) const
{
    std::istringstream iss(_operations);
    std::string token;

    while (iss >> token)
    {
        if (isOperator(token))
        {
            if (operands.size() < 2)
                throw RPN::NotEnoughOperandsException();
            int operand1 = operands.top();
            operands.pop();
            int operand2 = operands.top();
            operands.pop();

            int result = ProcessOperation(operand2, operand1, token);
            std::cout << "detail: " << operand2 << " " << token << " " << operand1 << " = " << result << std::endl;
            operands.push(result);
        }
        else
        {
            int operand = GetOperand(token);
            operands.push(operand);
        } 
    }
    return ;
}



const char *RPN::WrongArgumentException::what() const throw()
{
    return ("wrong number of arguments.");
}

const char *RPN::EmptyArgumentException::what() const throw()
{
    return ("argument is empty.");
}

const char *RPN::TooManyOperandsException::what() const throw()
{
    return ("too many operands.");
}

const char *RPN::NotEnoughOperandsException::what() const throw()
{
    return ("not enough operands.");
}

const char *RPN::IntOverflowException::what() const throw()
{
    return ("int overflow.");
}

const char *RPN::DivisionByZeroException::what() const throw()
{
    return ("division by zero not allowed.");
}

const char *RPN::UnexpectedTokenException::what() const throw()
{
    return ("unexpected token.");
}