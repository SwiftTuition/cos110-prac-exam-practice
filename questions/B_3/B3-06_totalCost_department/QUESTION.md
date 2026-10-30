Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# B3-06. Template specialization: `totalCost<Department*>` (100)

For this question, write a template specialization (a version of a template written for one exact type). The function template `totalCost` returns the total monthly cost of the things in a list. For most types this is 0. Write the specialization of `totalCost` for `Department*` in the file `B_3.cpp`. `Company::costToCompany()` also uses it.

## UML (only the classes this question needs)

```text
Templates.h (function templates)
+ totalCost<T>(List<T>&): float
+ totalCost<Department*>(List<Department*>&): float   <- implement

Company
- departments: List<Department*>
+ Company()
+ ~Company()
+ addDepartment(Department*): void
+ costToCompany(): float
+ operator<<(ostream&, Company&): ostream&   {friend}

List<T>
- headNode: Node<T>*
- size: int
+ List()
+ ~List()
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

Not on the published partial UML: `totalCost` and its specialization (the target; function templates are not on the UML), `~Company()`, `Company::costToCompany`, `Department::getSize`, `Department::getName`, the `{virtual}` markers (the UML marks nothing virtual), `operator<<` (not drawn; the scenario says every class has one). `head()` is written `Node<T>* const& head() const`: a call to the UML form `const Node<T>*&` gives a compile error. The real exam's complete UML may add members like these.

## What is given

- The general template in `Templates.h`:
  ```cpp
  template <class T>
  float totalCost(List<T>& list) {
      return 0;
  }
  ```
- The declaration of the specialization, also in `Templates.h`:
  ```cpp
  template <>
  float totalCost<Department*>(List<Department*>& list);
  ```
- `totalCost` is not a member of `List`, so it cannot use `headNode`. Use `list.head()` to get the first node (or `NULL`). For a node `curr`, `curr->getData()` returns the `Department*` and `curr->next()` returns the next node.
- `Company::costToCompany()` is given as `return totalCost(departments);`. In this question the company owns its departments, and `~Company()` deletes them. (Other questions in this bank may give this job to a different class.)
- `Sales`, `HR`, `Marketing` and `Development` inherit from `Department`. `costToCompany()` is virtual. It returns the number of employees in the department times a monthly amount: Sales R15000, HR R12000, Marketing R18000, Development R25000. The base `Department` returns 0.
- `operator<<` for a Department prints `<name> (cost R<cost>)` and a newline, and then every team (`Team:` and one line per employee). It already ends every line, so do not add an extra `endl` after it.
- A Department owns its teams, and a Team owns its employees.

## Behaviour of `totalCost<Department*>(List<Department*>& list)`

- Return the sum of `costToCompany()` of every Department in the list.
- Skip `NULL` entries.
- An empty list returns 0.
- Do not change the list and do not delete anything.

## File layout

- `Templates.h` holds the general template (fully written) and, after it, a **declaration** of the specialization (only the header line, ending in `;`).
- You write the **definition** of the specialization in `B_3.cpp`. A full specialization is an ordinary function, not a template, so it must be defined in exactly one `.cpp` file. `B_3.cpp` is compiled on its own (it is on the g++ line).
- Because every file that includes `Templates.h` sees the declaration, `main.cpp` calls your specialization and not the general template.

## Rules

- Write the specialization the way it is shown in the lectures (L19): the line `template <>`, then the function with the concrete type in angle brackets after the function name. It must match the declaration in `Templates.h` exactly (return type, name, `<type>` and parameter types). Your definition starts with the same two lines as the declaration, without the `;`:

  ```cpp
  template <>
  float totalCost<Department*>(List<Department*>& list) {
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
