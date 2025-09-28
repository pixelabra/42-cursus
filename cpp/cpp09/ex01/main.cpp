#include "RPN.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "The RPN arithmetic expression required in one argument." << std::endl;
		return (1);
	}
	try {
		RPN(av[1]);

		
	} catch (std::exception& e) {
		std::cerr << e.what();
	} catch (...) {
		std::cerr << "Unforeseen problem encountered." << std::endl;
	}
	return (0);
}
