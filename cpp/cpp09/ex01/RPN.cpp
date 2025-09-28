#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) {

}

RPN::RPN(const std::string& expr) {
    this->_expr = expr;
}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {

    }
    return (*this);
}

RPN::~RPN() {}

void    RPN::fillStack() {
    // 
}