#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <sstream>
# include <cstdlib>

typedef struct s_pair {
	float	first;
	float	second;
} t_pair;

class RPN {
	private:
	std::string				_expr;
		std::stack<float>	_operands;

		RPN();
		RPN& operator=(const RPN& other);
		RPN(const RPN& other);

		void	performOperation(char op);
	public:
		RPN(const std::string& expr);
		~RPN();

		void	fillStack();
		void	executeOperation(char op);
};

int	exprIsValid(int ac, std::string expr);

#endif