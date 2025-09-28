#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>

class RPN {
	private:
		std::stack<float>	_operands;
		std::string			_expr;

		RPN();
		RPN& operator=(const RPN& other);
		RPN(const RPN& other);
	public:
		RPN(const std::string& expr);
		~RPN();

		void	fillStack() const;
};

#endif