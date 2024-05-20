#pragma once

#include <algorithm>
#include <cstdlib>
#include <climits>
#include <string>
#include <iostream>
#include <stack>
#include <sstream>

#define OP "+-*/"

class RPN
{

public :

    RPN(int argc, char *operations);
    RPN(RPN const & copy);
    ~RPN(void);

    RPN & operator =(RPN const & src);

    void result(void) const;

    class WrongArgumentException : public std::exception {
		public :
			const char *what() const throw();
	};

    class EmptyArgumentException : public std::exception {
		public :
			const char *what() const throw();
	};

    class TooManyOperandsException : public std::exception {
		public :
			const char *what() const throw();
	};

    class NotEnoughOperandsException : public std::exception {
		public :
			const char *what() const throw();
	};

    class IntOverflowException : public std::exception {
		public :
			const char *what() const throw();
	};

    class DivisionByZeroException : public std::exception {
		public :
			const char *what() const throw();
	};

    class UnexpectedTokenException : public std::exception {
		public :
			const char *what() const throw();
	};


private :

    std::string _operations;
    void ProcessStack(std::stack<int> &operands) const;

};