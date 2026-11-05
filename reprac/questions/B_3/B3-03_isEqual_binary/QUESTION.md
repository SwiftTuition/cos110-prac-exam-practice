Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# B3-03. Template specialisation: `isEqual<Binary>` (100)

For this question, write a template specialisation (a version of a function template written for one exact type). The function template `isEqual` compares two values with `==`. `Binary` has no `==` operator, so the general template cannot be used for it. Write the specialisation `isEqual<Binary>` in the file `B_3.cpp`. It compares two strings bit by bit.

## UML (only what this question needs)

```text
Templates.h (function templates)
+ isEqual<T>(const T&, const T&): bool
+ isEqual<Binary>(const Binary&, const Binary&): bool   <- implement

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

Not on the partial UML in the exam paper: `isEqual` and its specialisation (the target; function templates are not on the UML), `operator<<` (not drawn; the exam paper says every class has one), and the `{const}` markers. The real exam's complete UML may add members like these.

## What is given

- The general template in `Templates.h`:
  ```cpp
  template <class T>
  bool isEqual(const T& a, const T& b) {
      return a == b;
  }
  ```
- The declaration of the specialisation, also in `Templates.h`, right after the general template:
  ```cpp
  template <>
  bool isEqual<Binary>(const Binary& a, const Binary& b);
  ```
- `operator[]` has a `const` version and `getSize()` is `const`, so both can be used on a `const Binary&`.
- `Binary(string)`: each `'1'` becomes `true`; every other character becomes `false`.

## What `isEqual<Binary>(const Binary& a, const Binary& b)` must do

- Return `true` when `a` and `b` have the same size **and** the same bit at every index. Otherwise return `false`.
- Strings of different sizes are not equal, even with the same value: `011` and `11` are not equal.
- Two empty strings are equal.
- Never read a bit outside a string: when the sizes differ, do not compare bits.
- Do not change either string, and print nothing.

## How and where to write the specialisation

- Write it in `B_3.cpp`, in the form of the lecture example (Lecture 19): the line `template <>`, then the function with the type in angle brackets after the function name. It must match the declaration in `Templates.h` exactly. With `T = Binary`, each `const T&` becomes `const Binary&`. Your definition starts with the same two lines as the declaration, without the `;`:

  ```cpp
  template <>
  bool isEqual<Binary>(const Binary& a, const Binary& b) {
  ```
- Do not write `template <class T>` here. That declares a new, different template, and the specialisation that `main.cpp` calls stays undefined (link error).
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
