# CPP Module 08
This module introduces us to things.

1. ex00: std::map
2. ex01: std::stack
3. ex02: std::list + std::vector use with std::pair somewhere?

## Containers
1. std::array
Container that encapsulates fixed size arrays.
std::array<T, N> array;
N must be specified at compile time.

at() thorws an exception if out of bounds.
data() gives access to the underlying array

2. std::vector
linked list + array (dynamically,  access time O(1))
use reserve to internally create an array of a specific size.

3. std::set
std::set< T, std::greater<> > 

4. std::unordered_set
'The elements of an unordered associative container are organized into buckets. Keys with the same hash code appear in the same bucket'

Organises elements into buckets. No requirements on how this is done. Each bucket is probably a list and the container of buckets is probably a vector. It varies from compiler to compiler, from version to version.

Example: add item to unordered_set --> hash value, reduce it to the size of the array. Add item at the tail of that linked list. Two consecutively added itmes may be added at completely different places.

The set checks if something exists or not and then push.
Search, insertion and removal --> avg. constant-time complexity. It uses hashing to insert elements into buckets.

Unordered set: unique items w/ fast insertion and removal.

Unordered multiset: not unique not sorted (complexity can be constant c). Map might need a lot of binary tree searchc and shuffling, whereas the set bucket situation could be easier

5. std::multiset
Associative container a sorted set of duplicate objects of type key. insertiono, removal, search have logarithmic complexity

implemented using the Red-Black Tree. or AVL.

6. std::map
Associative container s tores elements in key-value pair. key should be unique.
Implemented using Self-balance BSTs (AVL/Red Black Tree)

Stores them in sorted order on the basis of key
std::map< T2, T2 > obj;

keys have to be unique otherwise overwrites existing value.
alternative
std::map< string, std::vector< int > > map;

unordered_map : hashing and bucket (cnstant time complexity)

7. std::multimap
Can have multiple inputs with the same key. They are stored in ascening or descending.

We do not have at() and [] liek std::map

Could be red black tree.

equal_range method (get all the pairs for a given tree)

8. std::list
doubly linked list, sequence container. non contiguous memory allocation.
Faster (compared to other sequence containers vector, forward_list, deques) in terms of insertion, remoal and moving elements in any position provided we have the iterator of the position 

use sort + unique if removing duplicates is required.

9. std::deque
indexed sequence container (same like vector?). vectors have inside an array. 
deque has pop_front. vectors do not.
they are not stored contiguously. list of vectors,
individual fixed allocated fixedsize arrays, w/ additional bookkeeping. two pointer dereference

expansion of deque is cheaper than expansion of vector. 

even one element 16 times of object size or 4096 bytes should be allocated to its internal array

insertion or removal of elements at the end or beginning  constant O(1)
inserting or removal of elements linear O(n)

10. misc
std::pair
map, multimap, unordered maps and unordered multimaps can use std::pars to insert data into their structures.

### Questions
- What is collision chaining?

- How does >> know how to populate a data type from a stringstream?
C++ defines operator>> for all the fundamental types (int, float, bool, std::string, etc.). It reads characters from the stream until it finds something that isn’t part of an integer (digits).


### QUESTION 01
RPN: 3 + 4 becomes 3 4 +
LIFO construct for left to right 
push 3, push 4. subtraction removes the top two items from the stack and puts the result onto the stack.

(3 + 4) * (5 + 6) becomes 3 4 + 5 6 + *

smaller nmber of keystrokes, coudl be faster, more difficutl for those who learned algebraic notation

operand encountered: two items opped off the stack, operation performed result pushed on the stack

RPN ideal for interpreters

Brackets are not allowed nput should be proper.

### QUESTION 02
merge-insert sort algorithm

parse the arguments
- positive integers
- isdigit

duplicates: st
