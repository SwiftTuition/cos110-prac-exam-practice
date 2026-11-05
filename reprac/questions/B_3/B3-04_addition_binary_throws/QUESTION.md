Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# B3-04. Template specialisation: `addition<Binary, Binary>` throws (100)

For this question, write a template specialisation (a version of a function template written for exact types). The lecture example does the same for two `char` values: it throws an exception. Adding two binary strings is not allowed in this system. Write the specialisation of `addition` for two `Binary` objects in the file `B_3.cpp`. It must throw.

## UML (only what this question needs)

```text
Templates.h (function templates)
+ addition<T, U>(T, U): T
+ addition<Binary, Binary>(Binary, Binary): Binary   <- implement

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

Not on the partial UML in the exam paper: `addition` and its specialisation (the target; function templates are not on the UML), `operator<<` (not drawn; the exam paper says every class has one), and the `{const}` markers. The real exam's complete UML may add members like these.

## What is given

- The general template in `Templates.h` (from the lectures):
  ```cpp
  template <class T, class U>
  T addition(T v1, U v2) {
      return v1 + v2;
  }
  ```
- The declaration of the specialisation, also in `Templates.h`, right after the general template:
  ```cpp
  template <>
  Binary addition<Binary, Binary>(Binary v1, Binary v2);
  ```
- `Binary` has no `+` operator. The section B UML has no exception class.

## What `addition<Binary, Binary>(Binary v1, Binary v2)` must do

- Do not add anything. Throw the C-string `"Cannot add two binary strings"`, as the lecture example throws `"Cannot add two chars"`.
- `main.cpp` catches it with `catch (const char* msg)`. A C-string literal is thrown as a `const char*`, so this catch matches it.
- Do not throw a `std::string`, a `Binary` or a pointer made with `new`. None of these match `catch (const char* msg)`.
- Do not print anything.

## How and where to write the specialisation

- Write it in `B_3.cpp`, in the form of the lecture example (Lecture 19): the line `template <>`, then the function with **both** types in angle brackets after the function name. It must match the declaration in `Templates.h` exactly (return type, name, `<Binary, Binary>` and parameter types). Your definition starts with the same two lines as the declaration, without the `;`:

  ```cpp
  template <>
  Binary addition<Binary, Binary>(Binary v1, Binary v2) {
  ```
- The return type `Binary` is still required, even though the function only throws.
- Why `B_3.cpp`: a full specialisation is an ordinary function, not a template. It must be defined in exactly one `.cpp` file. Suppose the body were in `Templates.h`. Both `main.cpp` and `B_3.cpp` include `Templates.h`, so each would get its own copy. The link would then fail with `multiple definition`. (An `inline` definition would be allowed; see B3-06.)
- Why the declaration is in the header: Lecture 19 says specialisations must be "placed after the general template function". They must also come before the first use. Every file that includes `Templates.h` sees the declaration, so `main.cpp` calls your version.
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
