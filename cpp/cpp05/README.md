# CPP Module 05

This module introduces us to exceptions.

Circular dependencies.
Forward declarations.
Reminder that you cannot call the pure virtual function in constructor / destructor. It is undefined behaviour. You can call it in a  non virtual way (Abstract::f();). In the derived, it is possible to call the overriden pure virtual function in the constructor / destructor. Also the abstract version of the function in the function definition of the pure virtual function of the derived.

throw() keyword --> noexcept

custom exceptions
try catch statements

## Exceptions