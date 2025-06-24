# CPP Module 08
This module introduces us to cointainers and algorithms. STL usage is mandatory.

Keywords:
STL
Containers
Algorithms

## Containers
Vectors, lists, maps etc.
Container is a holder object. Stores collection of other objects (elements). They are implemented as class templates.

Containers replicate: dynamic arrays (vectors), queues, stacks, heaps, linked lists, trees, associative arrays (maps)

Questions:
What are associative containers?

Containers: sequence containers, container adaptors, associative containers, unordered associative containers

Video 1:
loops, branches operating on pieces of data that is related to others. we strive to organise program and data. program structure around the data. group data together perhaps. arrays are this grouping.

an array: a pointer is created that holds the memory address where we have 10 x 4 byes (if int). Arrays have to be contiguous.arrays are very fast to access.

include array frorm the standard library
```
std::array<int, 10> b;
b[17] = 6; throws an error

b.size();
b.data();
```
standard array is emulating a container.

an empty container containes no data. container can be traverse. some data exists at the front and some at the back. we abstract away from the usual contiguours. there is a beginnning and an end adn we traverse with iterators.

```
for (std::array<int, 10>::iterator i = b.begin(); i != b.end(); ++i) {
	*i = something();
}
```
std::array<int, 10>::iterator --> auto (new cpp)

Iterates through the whole thing. Arranged for loops.
```
for (auto& i : b) {
	*i = something();
}
```

#include <algorithm>
std::fill(b.begin(), b.end(), something());

### Vectors
std::vector is a structure / array that can grow
when we declare we only specify the int, not the size.
containers have a front and a back. when we add stuff we push to the back. it's contiguous. that's why they offer fast indexable access. copies the entirety of it's contents. let's assume pointer to one of the old elements of the vectors before the copy. we can't assume that any pointer remains valid. if they do not change in size then ok.
don't grow element by element. they make educated guesses. no time overhead at all.

### List
std::list
no guarantee they are contiguous. nodes are joined with pointers. double linked lists. next and previous.
adding front of the list creates the node and just add. location is not going to change. insertion and removal very cheap.
problem: count how many where there is no next.
we can not perform [0]. to reach a node you need you need to go through all of them

### Deques (double ended queue)
std::deque
imagine insertion speed of a list but indexable speed of a vector.
linked list of arrays
significant memory overhead
not as fast as vectors

### Sets
They are stored in order, exclusive no duplicates
items are always within the same place

### Unordered sets
gain performance so they are not ordered
unordered

### Map
used to store key-value pairs. unordered faster i believe

## Exercises
ex00: find first occurenece in one of the second thing

## Unrelated Questions
- What are Lambda functions?
```