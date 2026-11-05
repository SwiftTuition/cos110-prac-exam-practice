Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# B3-06. Template specialisation: `countTrue<Binary>` in a file that a header includes (100)

For this question, write a template specialisation (a version of a function template written for one exact type). The function template `countTrue` walks a list of nodes and counts the nodes whose data is true. For `Binary`, it must count the true **bits** in all the strings instead. Write the specialisation `countTrue<Binary>` in the file `B_3.cpp`.

In this question, `Templates.h` ends with `#include "B_3.cpp"`. Template class headers often do the same with their `.cpp` file. Read "How and where to write the specialisation": the definition must be `inline`.

## UML (only what this question needs)

```text
Templates.h (function templates)
+ countTrue<T>(Node<T>*): int
+ countTrue<Binary>(Node<Binary>*): int   <- implement

Node<T>
- data: T
- nextNode: Node<T>*
+ Node(T)
+ ~Node()
+ getData(): T&
+ next(): Node<T>*&

BinaryStrings
- head: Node<Binary>*
- size: int
+ BinaryStrings()
+ ~BinaryStrings()
+ prepend(const Binary&): void
+ getHead(): Node<Binary>*&
+ calculatePos(): int
+ operator<<(ostream&, const BinaryStrings&): ostream&   {friend}

Binary
- array: bool*
- size: int
+ Binary(string)
+ Binary(const Binary&)
+ ~Binary()
+ operator[](int): bool&
+ operator[](int): const bool&   {const}
+ getSize(): int   {const}
+ operator<<(ostream&, const Binary&): ostream&   {friend}
```

Not on the partial UML in the exam paper: `countTrue` and its specialisation (the target; function templates are not on the UML), the `operator<<` functions (not drawn; the exam paper says every class has one), and the `{const}` markers. The real exam's complete UML may add members like these.

## What is given

- The general template in `Templates.h`:
  ```cpp
  template <class T>
  int countTrue(Node<T>* head) {
      int count = 0;
      Node<T>* curr = head;
      while (curr != NULL) {
          if (curr->getData()) {
              count++;
          }
          curr = curr->next();
      }
      return count;
  }
  ```
  For `Node<int>` it counts the values that are not 0. A `Binary` cannot be used in an `if`, so the general template does not compile for `Binary`.
- After it, also in `Templates.h`, the declaration of the specialisation and then the include of your file:
  ```cpp
  template <>
  int countTrue<Binary>(Node<Binary>* head);

  #include "B_3.cpp"
  ```
- The starter `B_3.cpp` has an include guard (`#ifndef B_3_CPP`, `#define B_3_CPP`, `#endif`) and `#include "Templates.h"`. `B_3.cpp` is also compiled on its own (it is on the `g++` line in the makefile). The include guard stops the file from being read twice in one compilation.
- `getHead()` returns the first node of a `BinaryStrings` list. `curr->getData()` is the `Binary` in a node, `curr->getData()[i]` is bit `i`, and `curr->getData().getSize()` is its number of bits.

## What `countTrue<Binary>(Node<Binary>* head)` must do

- Walk from `head` to the end of the list (`next()` is `NULL` after the last node).
- Return the total number of `true` bits in all the strings. Example: `000 -> 0011 -> 1101 -> 0101` gives 0 + 2 + 3 + 2 = 7.
- `NULL` gives 0. Empty strings add 0.
- Do not change the list, and print nothing.

## How and where to write the specialisation

- Write it in `B_3.cpp`, **between** `#define B_3_CPP` and `#endif`. Code after `#endif` is read twice when `B_3.cpp` is compiled on its own, and gives a redefinition error.
- Use the Lecture 19 form (`template <>`, then the function with the type in angle brackets after the function name), and add the keyword `inline` before the return type:

  ```cpp
  template <>
  inline int countTrue<Binary>(Node<Binary>* head) {
  ```
- Why `inline`: a full specialisation is an ordinary function, not a template. Here its definition is in `B_3.cpp`, and `Templates.h` includes `B_3.cpp`. So every `.cpp` file that includes `Templates.h` (here `main.cpp` and `B_3.cpp` itself) gets its own copy of the definition. Without `inline`, the link fails with `multiple definition of 'int countTrue<Binary>(Node<Binary>*)'`. `inline` allows one identical definition in each file.
- The declaration in `Templates.h` comes after the general template and before any use, as Lecture 19 requires. Your definition comes right after it, through the include.
- Do not write the general template again, do not remove the include guard, and do not change any header.

## Rules

- C++98 only: use `NULL`. Do not use `nullptr`, `auto` or `to_string`.
- Your code must compile with `-std=c++98 -Wall -Werror`. A warning stops the build.
- Memory is marked. valgrind must show no errors and no leaks.

The `operator<<` functions and the `ExpectedOutput` block apply to this question only. Other questions may print the same class differently.

## Build and upload

1. Open a terminal in the `B_3` folder.
2. Run `make B_3`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `B_3.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
