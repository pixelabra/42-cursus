// This test allows us to use a simple pointer to a public member function
// to calculate the sum of two integers. It is worth noting that it requires a
// an object of type MyClass to be able to dereference the pointer against to use it
// even if that obj is not used/

#include <iostream>

// class	MyClass
// {
// 	public:
// 		int	value;
// 		MyClass(int val): value(val) {};
// 		int	add(int x, int y) {return (x + y);}
// };

// int	main()
// {
// 	MyClass	obj(1000);

// 	int	(MyClass::*ptr)(int, int) = &MyClass::add;
// 	int	result = (obj.*ptr)(20, 30);
// 	std::cout << "Result from the member function is: " << result << std::endl;
// 	return (0);
// }

// A Utility class is created to obtain the double and the triple of 
// a private int. Reusing the same pointer that was typedeffed to make it 
// more readable throught the program. Based on a condition the pointer
// is assigned either one function or the other
class Utility
{
	private:
		int	x;
	public:
		Utility(int val): x(val) {}
		void	setX(int val) {x = val;}
		int		getX() {return (x);}
		int		doublex() {return (2 * x);}
		int		triplex() {return (3 * x);}
};

typedef int	(Utility::*UT)();

int	main()
{
	Utility	ut(10);
	UT		ptr;

	ptr = &Utility::doublex;
	int	result = (ut.*ptr)();
	std::cout << "Result of the doublex is: " << result << std::endl;

	ptr = &Utility::triplex;
	result = (ut.*ptr)();
	std::cout << "Result of the triplex is: " << result << std::endl;

	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
			ut.setX(i);
		else
			ut.setX(i * i);
		if (ut.getX() >= 9)
			ptr = &Utility::doublex;
		else
			ptr = &Utility::triplex;
		result = (ut.*ptr)();
		std::cout << "Result is: " << result << std::endl;
	}
	return (0);
}
