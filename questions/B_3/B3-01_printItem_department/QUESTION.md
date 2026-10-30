Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# B3-01. Template specialization: `printItem<Department*>` (100)

For this question, write a template specialization (a version of a template written for one exact type). The function template `printItem` prints any value with its stream insertion operator. For a `Department*`, this would print an address. Write the specialization of `printItem` for `Department*` in the file `B_3.cpp`, so that it prints the Department itself.

## UML (only the classes this question needs)

```text
Templates.h (function templates)
+ printItem<T>(const T&): void
+ printItem<Department*>(Department* const&): void   <- implement

Department
- teams: Team**
- size: int
+ Department(int)
+ ~Department()   {virtual}
+ addTeam(Team*): void
+ operator[](int): Team*&
+ getSize(): int
+ costToCompany(): float   {virtual}
+ getName(): string   {virtual}
+ operator<<(ostream&, Department&): ostream&   {friend}
```

Not on the published partial UML: `printItem` and its specialization (the target; function templates are not on the UML), `Department::getSize`, `Department::getName`, the `{virtual}` markers (the UML marks nothing virtual), `operator<<` (not drawn; the scenario says every class has one). The real exam's complete UML may add members like these.

## What is given

- The general template in `Templates.h`:
  ```cpp
  template <class T>
  void printItem(const T& item) {
      cout << item << endl;
  }
  ```
- With `T = Department*`, the parameter type `const T&` becomes `Department* const&` (a reference to a constant pointer). It is **not** `const Department*&`. The declaration in `Templates.h` already uses the right type:
  ```cpp
  template <>
  void printItem<Department*>(Department* const& item);
  ```
- `Sales`, `HR` and `Development` inherit from `Department`. `costToCompany()` is virtual. It returns the number of employees in the department times a monthly amount: Sales R15000, HR R12000, Development R25000. The base `Department` returns 0.
- `operator<<` for a Department prints `<name> (cost R<cost>)` and a newline, and then every team (`Team:` and one line per employee). It already ends every line, so do not add an extra `endl` after it.
- A Department owns its teams, and a Team owns its employees.

## Behaviour of `printItem<Department*>(Department* const& item)`

- If `item` is `NULL`, print `No department` and a newline.
- Otherwise, print the Department that `item` points to, using the Department stream insertion operator. Do not print the address. Do not add an extra newline, because the Department operator already ends its lines.

## File layout

- `Templates.h` holds the general template (fully written) and, after it, a **declaration** of the specialization (only the header line, ending in `;`).
- You write the **definition** of the specialization in `B_3.cpp`. A full specialization is an ordinary function, not a template, so it must be defined in exactly one `.cpp` file. `B_3.cpp` is compiled on its own (it is on the g++ line).
- Because every file that includes `Templates.h` sees the declaration, `main.cpp` calls your specialization and not the general template.

## Rules

- Write the specialization the way it is shown in the lectures (L19): the line `template <>`, then the function with the concrete type in angle brackets after the function name. It must match the declaration in `Templates.h` exactly (return type, name, `<type>` and parameter types). Your definition starts with the same two lines as the declaration, without the `;`:

  ```cpp
  template <>
  void printItem<Department*>(Department* const& item) {
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
