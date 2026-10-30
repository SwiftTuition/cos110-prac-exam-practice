Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# B2-04. Linked lists: `List<T>::removeAt` (100)

For this question, write a function that removes the node at a given position from a singly linked list. Write the `removeAt` function of the class template `List<T>` in the file `B_2.cpp`.

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
+ removeAt(int): bool   <- implement
+ operator<<(ostream&, const List<T>&): ostream&   {friend}

Node<T>
- data: T*
- nextNode: Node<T>*
+ Node(T*)
+ ~Node()
+ getData(): const T&
+ next(): Node<T>*&
```

Not on the published partial UML: `removeAt` (the target), `operator<<` (not drawn; the scenario says every class has one). `head()` is written `Node<T>* const& head() const`: a call to the UML form `const Node<T>*&` gives a compile error. The real exam's complete UML may add members like these.

## What is given

- `Node<T>` stores a **pointer** to its value (`data: T*`). The node owns that value: `~Node()` deletes `data`. `~Node()` does **not** delete the next node.
- To make a node for a value, write `new Node<T>(new T(value))`. The given `prepend` does it this way.
- `next()` returns a reference to the link, so you can change a link with `curr->next() = ...;`.
- `getData()` returns the value itself (a `const T&`), not the pointer.
- `size` must always be equal to the number of nodes. `getSize()` returns it.
- `operator<<` prints `Empty List` for an empty list. Otherwise it prints the values joined by `->`, for example `1->2->3`. It does not print a newline.
- Inside `List` you can use `headNode` directly.

## Behaviour of `removeAt(int pos)`

- Positions start at 0. The head node is at position 0. The last node is at position `size - 1`.
- If `pos` is less than 0, or `pos` is equal to or greater than the number of nodes, change nothing and return `false`. An empty list always returns `false`.
- Otherwise, unlink the node at position `pos` and delete it. Deleting the node also deletes its data (`~Node()` does that), so do not delete the data yourself.
- Subtract 1 from `size` and return `true`.

Example: for `10->20->30`, `removeAt(1)` returns `true` and the list becomes `10->30`. `removeAt(3)` returns `false`.

## File layout (templates)

- Template code must be visible wherever the template is used. So `List.h` includes `List.cpp` and then `B_2.cpp` at the bottom (the COS 110 rule for templates).
- `B_2.cpp` is also on the g++ line in the makefile. Its include guard (`#ifndef B_2_CPP`, `#define B_2_CPP`, `#endif`) makes both ways work. Keep your code between `#define B_2_CPP` and `#endif`. Code after `#endif` gives a redefinition error.
- `B_2.cpp` already has `#include "List.h"`. Do not add `#include "List.cpp"`.
- In the real exam, follow the given headers and makefile of the exam.

Write the function as a template member. It starts like this:

```cpp
template <class T>
bool List<T>::removeAt(int pos) {
```

## Rules

- C++98 only: use `NULL`. Do not use `nullptr`, `auto` or `to_string`.
- Your code must compile with `-std=c++98 -Wall -Werror`. A warning stops the build.
- Memory is marked. valgrind must show no errors and no leaks.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `B_2` folder.
2. Run `make B_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `B_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
