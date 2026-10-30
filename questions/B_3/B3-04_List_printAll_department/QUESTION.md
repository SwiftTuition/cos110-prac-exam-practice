Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# B3-04. Template specialization: `List<Department*>::printAll` (100)

For this question, write a specialization of one member function of a class template (a version of that member written for one exact type). `List<T>::printAll()` prints every value in the list. A company keeps its departments in a `List<Department*>`, and for that type the general version would print addresses. Write the specialization `List<Department*>::printAll()` in the file `B_3.cpp`.

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
+ printAll(): void
+ operator<<(ostream&, const List<T>&): ostream&   {friend}

List<Department*>   (specialization of one member)
+ printAll(): void   <- implement

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

Not on the published partial UML: `List::printAll` (the general version) and its specialization for `Department*` (the target), `Department::getSize`, `Department::getName`, the `{virtual}` markers (the UML marks nothing virtual), `operator<<` (not drawn; the scenario says every class has one). `head()` is written `Node<T>* const& head() const`: a call to the UML form `const Node<T>*&` gives a compile error. The real exam's complete UML may add members like these.

## What is given

- The general `printAll()` in `List.cpp`:
  ```cpp
  template <class T>
  void List<T>::printAll() {
      if (headNode == NULL) {
          cout << "Empty List" << endl;
          return;
      }
      Node<T>* curr = headNode;
      int index = 0;
      while (curr != NULL) {
          cout << index << ": " << curr->getData() << endl;
          curr = curr->next();
          index++;
      }
  }
  ```
- The declaration of the specialization at the bottom of `List.h`:
  ```cpp
  template <>
  void List<Department*>::printAll();
  ```
- `Node<T>` stores a pointer to its value (`data: T*`). For `List<Department*>`, `getData()` returns the `Department*`. `next()` returns the next node.
- The list does **not** own the Departments in this question. `main` deletes them.
- `Sales`, `HR` and `Development` inherit from `Department`. `costToCompany()` is virtual. It returns the number of employees in the department times a monthly amount: Sales R15000, HR R12000, Development R25000. The base `Department` returns 0.
- `operator<<` for a Department prints `<name> (cost R<cost>)` and a newline, and then every team (`Team:` and one line per employee). It already ends every line, so do not add an extra `endl` after it.
- A Department owns its teams, and a Team owns its employees.

## Behaviour of `List<Department*>::printAll()`

- If the list is empty, print `Empty List` and a newline (the same as the general version).
- Otherwise, for each node from the head, with `index` counting from 0:
  - if the `Department*` is `NULL`, print `<index>: No department` and a newline;
  - otherwise, print `<index>: ` and then the Department itself with the Department stream insertion operator. Do not add an extra newline, because the Department operator already ends its lines.
- Do not change the list and do not delete anything.

## File layout

- `List.h` includes `List.cpp` at the bottom (the COS 110 rule for templates), so `List.cpp` is not on the g++ line.
- After that include, `List.h` **declares** the specialization of one member for `T = Department*` (only the header line, ending in `;`). `List.h` has `class Department;` at the top so that it can name the type.
- You write the **definition** in `B_3.cpp`. A full specialization is an ordinary function, not a template, so it must be defined in exactly one `.cpp` file. `B_3.cpp` is compiled on its own (it is on the g++ line).
- A member specialization starts with `template <>`. Then write `List<Department*>::printAll()`. Do not write `template <class T>` and do not write `<T>`. Inside this function `T` means `Department*`, so the nodes have the type `Node<Department*>*`. You can use `headNode` and `size` directly.

## Rules

- Write the specialization like this: the line `template <>`, then `void List<Department*>::printAll()` and the body. The type goes after the class name `List`, not after `printAll`. It must match the declaration at the bottom of `List.h` exactly. Your definition starts like this:

  ```cpp
  template <>
  void List<Department*>::printAll() {
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
