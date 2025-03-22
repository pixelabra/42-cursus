# CPP Module 04

This module introduces us to Subtype Polymorphism, Abstract Classes and Interfaces.
Abstract classes are used to represent general concepts.

## Abstract Classes
- used as a base class
- contains at least one pure virtual function
- a pure virtual function cannot have pure specifier (= 0) and a declaration
- no parameter type, function return type, or type of explicit conversion nor declaration of abstract class object is allowed
- pointers and references to an abstract class are allowed
- a class derived from an abstract base class will remain abstract unless you override each pure virtual function in the derived class
- you can derive an abstract class from a non abstract class, you can override a non pure virtual function into a pure virtual function
- calling a pure virtual function directly or indirectly from its constructors / destructors is undefined behaviour
- destructors can be pure too
- a pure virtual function can have a definition, but it must be defined outside the class (not inline)

## Virtual Destructors
- always use a virtual destructor in a base class to ensure correct cleanup when deleting derived objects through base class pointers
- always use a virtual destructor with abstract classes
- order of destructor calls follows inheritance

```
virtual void	f() = 0; // pure virtual function
```

```plaintext
Cpp_Module_02/
├── ex00/
│   ├── Makefile
│   ├── Fixed.cpp
│   ├── Fixed.hpp
│   └── main.cpp
└── README.md				# Project documentation
```