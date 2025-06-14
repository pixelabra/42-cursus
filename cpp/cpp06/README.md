# CPP Module 06
This module introduces 

- static functions cannot have a const specifier
- virtual functions must be non static

Named constructors as methods? is this what is required?
why are they static methods?

wjich constructor to  use?
```
class Point {
public:
  Point(float x, float y);     // Rectangular coordinates
  Point(float r, float a);     // Polar coordinates (radius and angle)
  // ERROR: Overload is Ambiguous: Point::Point(float,float)	
};
int main()
{
  Point p = Point(5.7, 1.2);   // Ambiguous: Which coordinate system?
  // ...
}
```

so you want:

```
#include <cmath>               // To get std::sin() and std::cos()
class Point {
public:
  static Point rectangular(float x, float y);      // Rectangular coord's
  static Point polar(float radius, float angle);   // Polar coordinates
  // These static methods are the so-called "named constructors"
  // ...
private:
  Point(float x, float y);     // Rectangular coordinates
  float x_, y_;
};
inline Point::Point(float x, float y)
  : x_(x), y_(y) { }
inline Point Point::rectangular(float x, float y)
{ return Point(x, y); }
inline Point Point::polar(float radius, float angle)
{ return Point(radius*std::cos(angle), radius*std::sin(angle)); }
```

## Implicit & Explicit Declarations

Implicit: without you mentioning what to do. compiler is allowed to compile one implict conversion n the code. without needing to cast. It's allowed to do only one

// Horrendous
class Entity
{
	private:
		std::string		m_Name;
		int				m_Age;
	public:
		Entity(const std::string& name) : m_Name(name), m_Age(-1) {}
		explicit Entity(int age) : m_Name(""), m_Age(age) {} // added the explicit; to show this 
};

void	printEntity(const Entity& entity) {}

int main()
{
	Entity	a = "example";
	Entity	b = 27;

	printEntity(23);
	printEntity(std::string("hello"));
	printEntity(Entity("example"));
}

Explicit: disables this implicit functionality, no implicit conversions. This constructor must explicitly be called. Good to use for math libraries. Low level wrappers could be useful.

## Casting
type casting: conversions withing the type system
c++: types are enforced.

int to double: implicit conversion
double to in: implicit conversion

static cast: 

int main(void)
{
	double value = 5.25;
	double a = (int)value + a;
	double s = static_cast<int>(value) + 5.3;
}

// They do not do anything that c cast cannot do ish. 
- static cast
- reinterpret cast
- dynamic cast
works only in c++ it checks if it's aallowed or not.. it is evaluated at runtime: runtime cost 

pointer of base but that could be a derived or another derived. dynamic cast will return a null pointer. we can check if an object is a given type

Player	*plaayer = new Player();
Entity	*e = player;
Entity	*actuallyPlayer = player;
Player	*p = e; // problem

Entity	*e1 = new Enemy();
Entity	*actuallyEnemy = new Enemy();

Player*	p = (Player*)e1; // this will initially work but something unique to player that enemy does not have, program will likely crash

Player	*p = dynamic_cast<Player*>(e1); // works with only polymorphicype class. (make one virtual function)

Player	*p0  = dynamic_cast<Player*>(actuallyEnemy); // this should fail
Player	*p1  = dynamic_cast<Player*>(actuallyPlayer); // this should fail

- const cast

Static casting:
- compile time
Dynamic casting:
- run time

it works only on polymorphic bases since it needs RTTI information for down-casting a polymorphic type from the virtual tables 

virtual alklows the cration of the v table and it also stores the type safety information stuff.

class Vehicle
{
	private:

	public:
		virtual void startEngine() {
			std::cout << "Empty Implementation" >> std::endl;
		}
};

class Ship: public Vehicle
{
	public:
		void	startEngine() {
			std::cout << "ship engine started" >> std::endl;
		}
		void startSailing() {
			std::cout << "ship sailing..." << std::endl;
		}
}

class Car: public Vehicle
{
	public:
		void	startEngine() {
			std::cout << "car engine started" >> std::endl;
		}
		void startRiding() {
			std::cout << "car ride..." << std::endl;
		}
}

void test_downcast(Vehicle *vehicle) {
	
	try {
		Ship *ship = dynamic_cast<Ship*>(vehicle);
		ship.startEngine();

	} catch (std::bad_cast& exception) {
		std::cout << "downcast failed"<< e.what() << std::endl;
	}

	if (!ship) {
		std::cout << "downcasting to ship failed..." << std::endl;
	} else {
		std::cout << "downcasting to ship success"<< std::endl;
		ship->startEngine();
		ship->startSailing();
	}
}

int	main(int ac, char **av) {
	Vehicle *vehicle = new Ship();
	test_downcast(vehicle); // we need a dynamic casting to make sure we call the right specific methods
	return (0);
}
dynamic cast only on polymorphic.
dynamic cast works with pointers and references. It will attempt at runtime 
dynamic cast more expensive.
static cast: less expensive, compile time more information if legal
RTTI: runtime type information

avoid casting where possible.
prefer dynamic cast (maybe not in games), but you can to checks

if you must use a cast, use a named cast

check out expression rules isocpp.github.io/cppcoreguidelines/cppcoreguidelines

Derived	d;
Base	b;

d.Do();
b.Do();
(static_cast<Base>(d)).Do(); // it will use the base Do not the derived do.
(static_cast<Derived>(b)).Do(); // erro, it's  not going to traverse the hierarchy for us. 

Base	*b = new Base;
Derived	*d = new Derived;

// is this something taht we should be able to do? Allowable with pointers to do static_cast, but no run-time checks to see if this is something we shoudl be able to do. If classes are not polymorphic (concrete classes without vtable), then we have some strange behaviour. If we do make a vtable.
static_cast<Derived*>(b)->Do(); 
d->Do();

(static_cast<Base*>(d))->Base::Do();
(dynamic_cast<Base*>(d))->Base::Do();

converting to void* or from void*
int i = 10;
void	*v = static_cast<void*>(&i);
int		*p = static_cast<int*>(v);	

Dangerous casts:
- pass at compile time, fail at run time
char	c;
int		*p1 = (int *)(&c); // allowed
*p1 = 3; //PASS at compile, FAIL at runtime
int	*p2 = static_cast<int*>(&c); // FAIL at compile


STATIC CASTING
private inheritance. we can
class Person {};
class Student : private Person {}; // 'has-a', not 'is-a'

void eat(const Person& p) {}
void study(const Student& s) {}

int main() {
	Person	p;
	Student	s;

	eat(p); // OK, p is a Person
	eat(s); // NOT OK, s isn't a Person
}

FIX with static cast:
class A{};
class B : private A{};

int main() {
	B	b;
	A	*aptr = (A*)(&b); // Allowed
	A	*aptr1 = static_cast<A*>(&b); // NOT Allowed: 'A' is an inaccessible base of 'B
}

DYNAMIC CASTING

RTTI: run time type identification: standard way for a program to determine the type of object durin runtime. It is provided through two operators:
- typeid operator: returns the actual type of object referred to by pointer (or reference)
- dynamic_cast operator: safely converts from pointer (or reference) to base type to pointer (or reference) to a derived type

class Animal {};
class Cat : public Animal {};
class Dog : public Animal {};

Aniaml	*bp1 = new Cat();
Animal	*bp2 = new Dog();

Dog		*pD = dynamic_cast<Dog*>(bp1); // return null ptr
Dog		*pD = dynamic_cast<Dog*>(bp2); // it will convert appropriately

- runtime type check 
- base class has to be polymorphic (at least virtual function)
- success returns valew of the type passed in angle brackets
- runtime overhead, use static cast when not problem.

class Base {};
class Derived : public Base {
	virtual void f() {}; // the main won't compile if the virtual function is not present.
};

int main() {
	Base	b;
	Derived	d;

	Base	*pb = dynamic_cast<Base*>(&d); // allowed
	Derived	*pd = dynamic_cast<Derived*>(&b); // NULL PTR
	return (0);
}

class Base {virtual void	f(){};};
class Derived : public Base {};

int	main() {
	Base	*pBD = new Derived;
	Base	*pBB = new Base;
	Derived	*pd;

	pd = dynamic_cast<Derived*>(pBD);
	pd = dynamic_cast<Derived*>(pBB);
	return (0);
}

{
	Animal	*p1 = new Cat;
	Animal	*p2 = new Dog;

	Cat	*pC1 = dynamic_cast<Cat*>(p1); // OK
	Cat	*pC2 = dynamic_cast<Cat*>(p2); // returns NULL
}

// References
int	main() {
	Derived	d;
	Base	b;

	try {
		Base&	rb = dynamic_cast<Base&>(d);
		Derived&	rd = dynamic_cast<Derived&>(b); //exception bad_cast
	} catch (exception& e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
}

Literals:
- integer literals: decimal (normal representation), octal representation (begin with zero), hexadecimal representation (0x / 0X)
e.g. number 25. (decimal: 25, octal: divide groups of bits into three = 031, hexadecimal: 0x19)
- floating point literals: exponent specified with e or E
e.g 3.14159E2, 3.14159e3, 3.14159E-1
- character and character string literals: single quotes is a literal type of char, double quotation marks is string literal. string = array cof const characters. compiler appends null character.
e.g. 'a' (char), "Fruit Salad" (string)

PRIVATE CONSTRUCTOR
a class method requires an instance to be called. but constructors and destructors are private so calling the function is not allowed unless it is declares as a static method.


PROJECT:

input: av[1]

- check that number of arguments is only  2
- check that there are no forbidden characters in the string
- if -inff, +inff, nanf, -inf, +inf, nan
- convert the parameter from string to its actual type then to the other types.
- conversion does not make sense or overflows display message


- parsing, type identification (int, float, double, char)

if only one character and not a digit: char for sure
if only one character and a digit: int for sure
if negative number only the first can be -, only 1 . can be present, only one nondigit allowed and that is 'f' at the very end.