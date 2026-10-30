Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A2-04. Operator overloading: template `operator<<` for `List<T>` (100)

For this question, implement the stream insertion operator `operator<<` for the template class `List<T>` in the file `A_2.cpp`. The operator is a template function and a `friend` of `List<T>`.

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
+ operator<<(ostream&, const List<T>&): ostream&   {friend}   <- implement

Node<T>
- data: T*
- nextNode: Node<T>*
+ Node(T*)
+ ~Node()
+ getData(): const T&
+ next(): Node<T>*&
```

Not on the published partial UML: `operator<<` (not drawn; the scenario says every class has one; the one for `List<T>` is the target). `head()` is written `Node<T>* const& head() const`: a call to the UML form `const Node<T>*&` gives a compile error. The real exam's complete UML may add members like these.

## Given code you will use

- `prepend(T value)` puts a new node holding a copy of `value` at the **front** of the list. So after `prepend(3)`, `prepend(2)`, `prepend(1)` the list is 1, 2, 3.
- `getData()` returns the value in a node. `next()` returns the pointer to the next node (`NULL` after the last node).
- `List.h` already declares the operator before the class and makes it a friend with `operator<< <>`:

```cpp
template <class T>
ostream& operator<<(ostream& out, const List<T>& list);
...
friend ostream& operator<< <>(ostream& out, const List<T>& list);
```

## What `operator<<(ostream& out, const List<T>& list)` must print

- If the list is empty, print `Empty List`.
- Otherwise print every value from the head to the last node, with `->` between two values. Example: `1->2->3`. Print each value with its own `operator<<`.
- Print no `->` after the last value, and **no newline**. `main` adds `endl` itself.
- Write to `out`, not to `cout`, and return `out`.

## File layout (templates)

- Template code must be visible wherever the template is used. So `List.h` includes `List.cpp` and then `A_2.cpp` at the bottom (the COS 110 rule for templates).
- `A_2.cpp` is also on the g++ line in the makefile. Its include guard (`#ifndef A_2_CPP`, `#define A_2_CPP`, `#endif`) makes both ways work. Keep your code between `#define A_2_CPP` and `#endif`. Code after `#endif` gives a redefinition error.
- `A_2.cpp` already has `#include "List.h"`. Do not add `#include "List.cpp"`.
- In the real exam, follow the given headers and makefile of the exam.

Write the operator as a function template. Its first two lines are:

```cpp
template <class T>
ostream& operator<<(ostream& out, const List<T>& list) {
```

- Keep the `#include "List.h"` line in `A_2.cpp`.
- Do not write `<>` in the definition. The `<>` belongs only to the `friend` line in `List.h`.
- Write the word `friend` only in the class. Do not write it again in `A_2.cpp`.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
