Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A3-06. Assignment operator: `List<T>::operator=` (100)

For this question, implement the assignment operator of the class template `List<T>` in the file `A_3.cpp`. All the other functions of `List<T>` and `Node<T>` are given in the other files.

## UML (only the classes this question needs)

```text
List<T>
- headNode: Node<T>*
- size: int
+ List()
+ ~List()
+ operator=(const List<T>&): List<T>&   <- implement
+ prepend(T): void
+ head(): Node<T>* const&   {const}
+ getSize(): int
+ operator<<(ostream&, const List<T>&): ostream&   {friend}

Node<T>
- data: T*
- nextNode: Node<T>*
+ Node(T*)
+ ~Node()
+ getData(): const T&
+ next(): Node<T>*&
```

Not on the published partial UML: `List<T>::operator=` (the target), `operator<<` (not drawn; the scenario says every class has one). `head()` is written `Node<T>* const& head() const`: a call to the UML form `const Node<T>*&` gives a compile error. The real exam's complete UML may add members like these.

How the given classes work:

- A node owns its `data`. `~Node()` deletes `data`. It does **not** delete the next node.
- `prepend(value)` makes a new node holding `new T(value)` and puts it at the front of the list. It adds 1 to `size`.
- `~List()` deletes every node.
- `next()` returns a reference to the node's `nextNode` pointer, so `curr->next() = newNode;` links a new node after `curr`.
- `operator<<` prints `Empty List` for an empty list, or the values joined by `->`, for example `1->2->3`.
- The `List` copy constructor and the `Node` copy constructor and `operator=` are not used in this question, so they are declared private.

## What `operator=` must do

The statement `a = b;` makes list `a` a deep copy of list `b`. A deep copy gets its own new nodes and data; it does not share them with the original.

1. If the list is assigned to itself (`a = a;`), do nothing and return the list.
2. Delete every node of this list. Set `headNode` to `NULL` and `size` to `0`.
3. Copy every node of the other list, **in the same order**. Each new node holds its own `new T(...)` copy of the value. (Note: `prepend` adds at the front, so using it while you walk from the head would reverse the order.)
4. After the copy, `size` is the same as the other list's size.
5. Return the current object by reference (`*this`), so that `a = b = c;` works.

After the assignment, the two lists must not share any node or any data.

## File layout (templates)

- Template code must be visible wherever the template is used. So `List.h` includes `List.cpp` and then `A_3.cpp` at the bottom (the COS 110 rule for templates).
- `A_3.cpp` is also on the g++ line in the makefile. Its include guard (`#ifndef A_3_CPP`, `#define A_3_CPP`, `#endif`) makes both ways work. Keep your code between `#define A_3_CPP` and `#endif`. Code after `#endif` gives a redefinition error.
- `A_3.cpp` already has `#include "List.h"`. Do not add `#include "List.cpp"`.
- In the real exam, follow the given headers and makefile of the exam.

Your function is a template member. It starts like this:

```cpp
template <class T>
List<T>& List<T>::operator=(const List<T>& other) {
```

## Rules

- Implement only `List<T>::operator=` in `A_3.cpp`. The declaration is already in `List.h`.
- `other` is a `const List<T>&`. Use `other.headNode` directly. This is allowed inside the class's own operator.
- Your code must compile with `-std=c++98 -Wall -Werror`. Memory is marked: `valgrind` must show no leaks and no invalid reads or frees.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_3` folder.
2. Run `make A_3`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_3.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
