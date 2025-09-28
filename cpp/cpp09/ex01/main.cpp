#include "RPN.hpp"

int	exprIsValid(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "The RPN arithmetic expression required in one argument." << std::endl;
		return (1);
	}
	std::string	expr(av[1]);
	if (expr.find_first_not_of("0123456789+-*/ ") != std::string::npos) {
		std::cerr << "Invalid character in expression." << std::endl;
		return (1);
	}
	return (0);
}

int main(int ac, char **av) {
	if (exprIsValid(ac, av))
		return (1);
	try {
		RPN	calculator(av[1]);

		calculator.fillStack();
	} catch (std::exception& e) {
		std::cerr << e.what();
	} catch (...) {
		std::cerr << "Unforeseen problem encountered." << std::endl;
	}
	return (0);
}
