#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other): _expr(other._expr), _operands(other._operands)   {}

RPN::RPN(const std::string& expr) {
    this->_expr = expr;
}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {

    }
    return (*this);
}

RPN::~RPN() {}

void	populateOperands(t_pair& operand, std::stack<float>& stack) {
	operand.second = stack.top();
	stack.pop();
	operand.first = stack.top();
	stack.pop();
}

void    RPN::executeOperation(char op) {
	t_pair	operand;

	if (_operands.size() < 2) {
		throw std::runtime_error("Not enough operands for operations");
	}
	switch(op) {
		case '+':
			populateOperands(operand, _operands);
			_operands.push(operand.first + operand.second);
			break ;
		case '-':
			populateOperands(operand, _operands);
			_operands.push(operand.first - operand.second);
			break;
		case '*':
			populateOperands(operand, _operands);
			_operands.push(operand.first * operand.second);
			break;
		case '/':
			populateOperands(operand, _operands);
			if (operand.second == 0) {
				throw std::runtime_error("Error: division by zero.");
			}
			_operands.push(operand.first / operand.second);
			break;
		default:
			throw std::runtime_error("Error: invalid operator '");
		}
}

void    RPN::fillStack() {
	std::istringstream	ss(_expr);
	std::string			token;

	while (ss >> token) {
		if (isdigit(token[0])) {
			if (token.find_first_not_of("0123456789") == std::string::npos) {
				if (std::atoi(token.c_str()) > 9) {
					throw std::runtime_error("Error: numbers must be single digit.");
				}
				_operands.push(std::atof(token.c_str()));
			} else {
				throw std::runtime_error("Error: invalid token " + token + "' in expression.");
			}
		} else {
			if (token.length() > 1 || token.find_first_not_of("+-*/") != std::string::npos) {
				throw std::runtime_error("Error: invalid token " + token + "' in expression.");
            }
            executeOperation(token[0]);
		}
	}
	if (_operands.size() != 1)
		throw std::runtime_error("Error: not enough operators.");
	std::cout << "Result: " << _operands.top() << std::endl;
}
