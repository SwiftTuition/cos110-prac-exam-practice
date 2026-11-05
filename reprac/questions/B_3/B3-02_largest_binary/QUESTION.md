Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# B3-02. Template specialisation: `largest<Binary>` (100)

For this question, write a template specialisation (a version of a function template written for one exact type). The function template `largest` returns the larger of two values with `>`. `Binary` has no `>` operator, so the general template cannot be used for it. Write the specialisation `largest<Binary>` in the file `B_3.cpp`. It compares the two strings by decimal value.

## UML (only what this question needs)

```text
Templates.h (function templates)
+ largest<T>(T, T): T
+ largest<Binary>(Binary, Binary): Binary   <- implement

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

Not on the partial UML in the exam paper: `largest` and its specialisation (the target; function templates are not on the UML), `operator<<` (not drawn; the exam paper says every class has one), and the `{const}` markers. The real exam's complete UML may add members like these.

## What is given

- The general template in `Templates.h`:
  ```cpp
  template <class T>
  T largest(T a, T b) {
      if (b > a) {
          return b;
      }
      return a;
  }
  ```
- The declaration of the specialisation, also in `Templates.h`, right after the general template:
  ```cpp
  template <>
  Binary largest<Binary>(Binary a, Binary b);
  ```
- `Binary` has a deep copy constructor, so passing and returning a `Binary` by value is safe. `operator=` of `Binary` is private and not defined in this question.
- `operator<<` for a `Binary` prints its bits, for example `1000`, with no newline.
- In examples, a call such as `largest("11", "0001")` is short for `largest(Binary("11"), Binary("0001"))`.

## What `largest<Binary>(Binary a, Binary b)` must do

- The decimal value reads the bits as an unsigned binary number, with `array[0]` (the leftmost bit) as the most significant bit. `0111` is 7, `1000` is 8, `0001` is 1, and an empty string is 0.
- Return the string with the larger decimal value. Return the original string, not the decimal value: `largest("11", "0001")` returns `11`, not `3`.
- If the two values are equal, return `a`. Example: `largest("011", "11")` returns `011`.
- The number of bits and the number of 1 bits do not decide anything. Only the value does.
- The tests use at most 31 bits, so the value fits in an `int`.
- Print nothing.

## How and where to write the specialisation

- Write it in `B_3.cpp`, in the form of the lecture example (Lecture 19): the line `template <>`, then the function with the type in angle brackets after the function name. It must match the declaration in `Templates.h` exactly. The general template takes `T` by value, so the parameters are `Binary a, Binary b`, not references. Your definition starts with the same two lines as the declaration, without the `;`:

  ```cpp
  template <>
  Binary largest<Binary>(Binary a, Binary b) {
  ```
- Why `B_3.cpp`: a full specialisation is an ordinary function, not a template. It must be defined in exactly one `.cpp` file. Suppose the body were in `Templates.h`. Both `main.cpp` and `B_3.cpp` include `Templates.h`, so each would get its own copy. The link would then fail with `multiple definition`. (An `inline` definition would be allowed; see B3-06.)
- Why the declaration is in the header: the specialisation must come after the general template and before the first use (Lecture 19). Every file that includes `Templates.h` sees the declaration, so `main.cpp` calls your version.
- Write only the definition. Do not write the general template again, and do not change any header.

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
