# CPP Module 02

This module and all upcoming ones require use of the Orthodox Canonical Form for each class created.

The first excercise introduces us to fixed-point numbers, commonly used in computer graphics, sound processing and scientific programming. Up to this exercise, we used integers or float-point numbers (or any of their variants). Here is three articles to look at for more information about float-point numbers. [1](https://www.cprogramming.com/tutorial/floating_point/understanding_floating_point.html), [2](https://www.cprogramming.com/tutorial/floating_point/understanding_floating_point_representation.html), and [3](https://www.cprogramming.com/tutorial/floating_point/understanding_floating_point_printing.html)

## Copy Constructors && Copy Assignment Operator Overload
A copy constructoor initialise a new object as a copy of an existing one.
Direct copy = shallow copy
Deep copy = copying entire object
C++ supplies a default copy constructor

Copy assignment is used to copy the values from one existing object to another after both objects have been constructedd

```plaintext
Cpp_Module_02/
├── ex00/
│   ├── Makefile
│   ├── Fixed.cpp
│   ├── Fixed.hpp
│   └── main.cpp
└── README.md				# Project documentation