Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# B3-05. Template specialisation: member `Node<Binary>::toInt` (100)

For this question, write a specialisation of **one member function** of a class template (a version of that member written for one exact type). `Node<T>::toInt()` converts the data of a node to an `int`. For `Node<Binary>`, the general version cannot convert a `Binary`. Write the specialisation `Node<Binary>::toInt()` in the file `B_3.cpp`. It returns the decimal value of the stored string.

## UML (only the classes this question needs)

```text
Node<T>
- data: T
- nextNode: Node<T>*
+ Node(T)
+ ~Node()
+ getData(): T&
+ next(): Node<T>*&
+ toInt(): int

Node<Binary>   (specialisation of one member)
+ toInt(): int   <- implement

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

Not on the partial UML in the exam paper: `Node<T>::toInt` and its specialisation for `Binary` (the target), the `operator<<` functions (not drawn; the exam paper says every class has one), and the `{const}` markers. The real exam's complete UML may add members like these.

## What is given

- The general `toInt()` in `Node.cpp`:
  ```cpp
  template <class T>
  int Node<T>::toInt() {
      return (int)data;
  }
  ```
  For `Node<int>` it returns the value, for `Node<double>` it drops the fraction (3.9 gives 3), for `Node<bool>` it gives 1 or 0, and for `Node<char>` the character code.
- The declaration of the specialisation at the bottom of `Node.h`, after `#include "Node.cpp"`:
  ```cpp
  template <>
  int Node<Binary>::toInt();
  ```
  `Node.h` includes `Binary.h` at the top, because the declaration names `Node<Binary>`, and a `Node<Binary>` holds a whole `Binary`.
- Inside a member of `Node<Binary>`, `data` is the stored `Binary`. `data[i]` is bit `i`, and `data.getSize()` is the number of bits.

## What `Node<Binary>::toInt()` must do

- Return the decimal value of `data`, read as an unsigned binary number with `data[0]` (the leftmost bit) as the most significant bit. `1010` gives 10, `0011` gives 3, and an empty string gives 0.
- The tests use at most 31 bits, so the value fits in an `int`.
- Do not change `data`, and print nothing.

## How and where to write the specialisation

- Write it in `B_3.cpp`.
- The lecture rule (Lecture 19) is `template <>` followed by the concrete type. The slides show only a function (`addition<char, char>`). For a member of a class template, the type goes after the class name.
- Write the line `template <>`, then the return type, then the class name **with the type** `Node<Binary>`, then `::toInt()`. The type goes after the **class** name, not after the function name.
- Your definition starts with the same two lines as the declaration in `Node.h`, without the `;`:

  ```cpp
  template <>
  int Node<Binary>::toInt() {
  ```
- Do not write `template <class T>`. Do not write `Node::toInt<Binary>()`. Both give compile errors.
- Why `B_3.cpp`: the specialisation is an ordinary member function, not a template. It must be defined in exactly one `.cpp` file. Suppose the body were written at the end of `Node.cpp`. The link then fails with `undefined reference to 'Node<Binary>::toInt()'`. Suppose instead the body were written in `Node.h`. Every file that includes `Node.h` gets its own copy, and the link fails with `multiple definition of 'Node<Binary>::toInt()'`. (An `inline` definition would be allowed; see B3-06.) You upload only `B_3.cpp`, so the definition goes there.
- Why the declaration is in `Node.h`: the specialisation must come after the general template and before the first use. Every file that includes `Node.h` sees it, so `main.cpp` calls your version.
- Write only the definition. Do not change any header.

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
