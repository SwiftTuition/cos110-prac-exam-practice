Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# B1-07. Recursion: `List<T>::contains` (100)

For this question, implement the function `contains` of the class template `List<T>` **using recursion**, in the file `B_1.cpp`. All the other functions of `List<T>` and `Node<T>` are given in the other files.

## UML (only the classes this question needs)

```text
List<T>
- headNode: Node<T>*
- size: int
+ List()
+ ~List()
+ prepend(T): void
+ head(): Node<T>* const&   {const}
+ getSize(): int
+ contains(Node<T>*, T): bool   <- implement
+ operator<<(ostream&, const List<T>&): ostream&   {friend}

Node<T>
- data: T*
- nextNode: Node<T>*
+ Node(T*)
+ ~Node()
+ getData(): const T&
+ next(): Node<T>*&
```

Not on the published partial UML: `List<T>::contains` (the target), `operator<<` (not drawn; the scenario says every class has one). `head()` is written `Node<T>* const& head() const`: a call to the UML form `const Node<T>*&` gives a compile error. The real exam's complete UML may add members like these.

How the given classes work:

- `head()` returns the first node of the list, or `NULL` for an empty list.
- `next()` returns the next node, or `NULL` after the last node.
- `getData()` returns the value stored in the node.
- `operator<<` prints `Empty List` for an empty list, or the values joined by `->`, for example `1->2->3`.

## What `contains(curr, value)` must do

It searches the nodes from `curr` to the end of the list.

- Return `true` if `curr` or any node after `curr` holds a value equal to `value`. Compare with `==`.
- Return `false` if no node from `curr` onwards holds `value`. Nodes before `curr` are not searched.
- If `curr` is `NULL`, return `false`. (This also covers an empty list.)
- Strings are compared exactly, so `"hr"` is not equal to `"HR"`.

## File layout (templates)

- Template code must be visible wherever the template is used. So `List.h` includes `List.cpp` and then `B_1.cpp` at the bottom (the COS 110 rule for templates).
- `B_1.cpp` is also on the g++ line in the makefile. Its include guard (`#ifndef B_1_CPP`, `#define B_1_CPP`, `#endif`) makes both ways work. Keep your code between `#define B_1_CPP` and `#endif`. Code after `#endif` gives a redefinition error.
- `B_1.cpp` already has `#include "List.h"`. Do not add `#include "List.cpp"`.
- In the real exam, follow the given headers and makefile of the exam.

Your function is a template member. It starts like this:

```cpp
template <class T>
bool List<T>::contains(Node<T>* curr, T value) {
```

## Rules

- You must use recursion. **No loops (`for`, `while`, `do`) and no helper functions. Using either scores 0.** The function must call itself; it may not call any other function you write.
- Your code must compile with `-std=c++98 -Wall -Werror` and must not leak memory.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `B_1` folder.
2. Run `make B_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `B_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
