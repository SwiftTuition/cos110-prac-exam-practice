Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# B3-07. Template specialization: `addition<Employee, Employee>` throws (100)

For this question, write a template specialization (a version of a template written for one exact type) in the same form as the lecture example, where adding two `char` values throws an exception. Adding two employees makes no sense. Write the specialization of `addition` for two `Employee` objects in the file `B_3.cpp`, so that it throws an `Exception`.

## UML (only the classes this question needs)

```text
Templates.h (function templates)
+ addition<T, U>(T, U): T
+ addition<Employee, Employee>(Employee, Employee): Employee   <- implement

Exception
+ message: string
+ Exception(string)
+ what(): string
+ operator<<(ostream&, const Exception&): ostream&   {friend}

Employee
- age: int
- firstName: string
- surName: string
- idNum: string
- gender: char
+ Employee(string, string, int, char)
+ Employee(const Employee&)
+ getFirstName(): string
+ getSurName(): string
+ getIDNum(): string
+ getAge(): int
+ getGender(): char
+ setIDNum(string): void
+ extractIntFromString(string, int, int): int   {static}
```

Not on the published partial UML: `addition` and its specialization (the target; function templates are not on the UML), the `int` return type of `extractIntFromString` (the UML shows no return type), `operator<<` (not drawn; the scenario says every class has one). The real exam's complete UML may add members like these.

## What is given

- The general template in `Templates.h` (from the lectures):
  ```cpp
  template <class T, class U>
  T addition(T v1, U v2) {
      return v1 + v2;
  }
  ```
- The declaration of the specialization, also in `Templates.h`:
  ```cpp
  template <>
  Employee addition<Employee, Employee>(Employee v1, Employee v2);
  ```
- `Exception` has a constructor that takes the message. `what()` returns the message. `operator<<` for an Exception prints `Exception: <message>`.

## Behaviour of `addition<Employee, Employee>(Employee v1, Employee v2)`

- Do not add anything. Throw an `Exception` with the message `Cannot add two employees`.
- Throw it by value (not a pointer, not a C-string), so that `catch (Exception& e)` catches it.
- Do not print anything.

## File layout

- `Templates.h` holds the general template (fully written) and, after it, a **declaration** of the specialization (only the header line, ending in `;`).
- You write the **definition** of the specialization in `B_3.cpp`. A full specialization is an ordinary function, not a template, so it must be defined in exactly one `.cpp` file. `B_3.cpp` is compiled on its own (it is on the g++ line).
- Because every file that includes `Templates.h` sees the declaration, `main.cpp` calls your specialization and not the general template.

## Rules

- Write the specialization the way it is shown in the lectures (L19): the line `template <>`, then the function with the concrete types in angle brackets after the function name. It must match the declaration in `Templates.h` exactly (return type, name, `<types>` and parameter types). Your definition starts with the same two lines as the declaration, without the `;`:

  ```cpp
  template <>
  Employee addition<Employee, Employee>(Employee v1, Employee v2) {
  ```
- Write only the definition of the specialization in `B_3.cpp`. Do not write the general template again, and do not change any header.
- C++98 only: use `NULL`. Do not use `nullptr`, `auto` or `to_string`.
- Your code must compile with `-std=c++98 -Wall -Werror`. A warning stops the build.
- Memory is marked. valgrind must show no errors and no leaks.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `B_3` folder.
2. Run `make B_3`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `B_3.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
