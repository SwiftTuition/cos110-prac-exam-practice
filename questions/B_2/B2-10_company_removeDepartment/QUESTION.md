Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# B2-10. Linked lists: `Company::removeDepartment` (ownership when removing from a list) (100)

For this question, write a function that removes a department from a company. A company keeps its departments in a linked list (`List<Department*>`). Write the `removeDepartment` function of the `Company` class in the file `B_2.cpp`.

## UML (only the classes this question needs)

```text
Company
- departments: List<Department*>
+ Company()
+ ~Company()
+ addDepartment(Department*): void
+ costToCompany(): float
+ removeDepartment(string): bool   <- implement
+ operator<<(ostream&, Company&): ostream&   {friend}

List<T>
- headNode: Node<T>*
- size: int
+ List()
+ ~List()
+ prepend(T): void
+ head(): Node<T>* const&   {const}
+ getSize(): int
+ remove(T): bool
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

`Sales`, `HR`, `Marketing` and `Development` inherit from `Department`. `getName()` returns `"Sales"`, `"HR"`, `"Marketing"` or `"Development"`.

Not on the published partial UML: `~Company()`, `Company::costToCompany`, `removeDepartment` (the target), `List::remove`, `Department::getSize`, `Department::getName` and `getName()` in the subclasses, the `{virtual}` markers (the UML marks nothing virtual), `operator<<` (not drawn; the scenario says every class has one). `head()` is written `Node<T>* const& head() const`: a call to the UML form `const Node<T>*&` gives a compile error. The real exam's complete UML may add members like these.

## What is given

- `addDepartment` uses `prepend`, so the list order is the **reverse** of the order in which departments were added.
- **Ownership:** in this question the company owns its departments. `~Company()` deletes every Department that is still in the list. A Department deletes its teams, and a Team deletes its employees. (Other questions in this bank may give this job to a different class.)
- `List<Department*>` does **not** delete the Departments. Each node holds a pointer to a `Department*` (`data` is a `Department**`). `~Node()` deletes only that pointer, not the Department.
- `List<T>::remove(T value)` is given. It unlinks and deletes the first node whose data `== value`, updates `size`, and returns `true` (or `false` if there is no such node). For `List<Department*>` it compares the pointers.
- `departments.head()` returns the first node (or `NULL`). For a node `curr`, `curr->getData()` returns the `Department*` and `curr->next()` returns the next node.

## Behaviour of `removeDepartment(string name)`

- Find the **first** department in the list (starting from the head) whose `getName()` is equal to `name`. Names are case sensitive.
- Remove its node from the list **and** delete the Department object. After the call there must be no leak and no pointer to memory that was already deleted.
- Return `true` if a department was removed. If no department has that name, or the company has no departments, change nothing and return `false`.
- Do not use a node after it has been deleted.

## Rules

- C++98 only: use `NULL`. Do not use `nullptr`, `auto` or `to_string`.
- Your code must compile with `-std=c++98 -Wall -Werror`. A warning stops the build.
- Memory is marked. valgrind must show no errors and no leaks.
- `Company` is not a template, so `B_2.cpp` is compiled on its own (it is on the g++ line). `List.h` does not include `B_2.cpp` in this question.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `B_2` folder.
2. Run `make B_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `B_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
