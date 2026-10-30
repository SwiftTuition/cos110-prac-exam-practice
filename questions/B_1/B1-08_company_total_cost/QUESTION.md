Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# B1-08. Recursion: `Company::totalCost` (100)

For this question, implement the function `totalCost` of the `Company` class **using recursion**, in the file `B_1.cpp`. All the other functions are given in the other files.

## UML (only the classes this question needs)

```text
Company
- departments: List<Department*>
+ Company()
+ ~Company()
+ addDepartment(Department*): void
+ getDepartments(): List<Department*>&
+ costToCompany(): float
+ totalCost(Node<Department*>*): float   <- implement
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
# countEmployees(): int
+ Department(int)
+ ~Department()   {virtual}
+ addTeam(Team*): void
+ operator[](int): Team*&
+ getSize(): int
+ costToCompany(): float   {virtual}
+ getName(): string   {virtual}
+ operator<<(ostream&, Department&): ostream&   {friend}

Sales : Department
+ Sales(int)
+ getName(): string
# costToCompany(): float

Marketing : Department
+ Marketing(int)
+ getName(): string
# costToCompany(): float

HR : Department
+ HR(int)
+ getName(): string
# costToCompany(): float

Development : Department
+ Development(int)
+ getName(): string
# costToCompany(): float
```

`Team`, `Employee` and `Exception` are the same as in the other questions. See `Team.h`, `Employee.h` and `Exception.h`.

Not on the published partial UML: `Company::totalCost` (the target), `~Company()` (given: it deletes every department, because the list frees only its nodes), `Company::getDepartments`, `Company::costToCompany`, `Department::countEmployees`, `Department::getSize`, `getName()` in `Department` and its subclasses, the `{virtual}` markers (the UML marks nothing virtual), `operator<<` (not drawn; the scenario says every class has one). `head()` is written `Node<T>* const& head() const`: a call to the UML form `const Node<T>*&` gives a compile error. The real exam's complete UML may add members like these.

How the given classes work:

- `addDepartment` adds a department at the **front** of the list (it uses `prepend`).
- For `List<Department*>`, each node stores a `Department*`, so `curr->getData()` gives a `Department*`.
- A node can store a `NULL` department. In that case `curr->getData()` is `NULL`.
- `costToCompany()` is `virtual`. Through a `Department*` it calls the cost of the real department type: the number of employees times R15000 (Sales), R18000 (Marketing), R12000 (HR) or R25000 (Development).
- The given `Company::costToCompany()` returns `totalCost(departments.head())`.

## What `totalCost(curr)` must do

It returns the total cost of the department in node `curr` and of every department in the nodes after `curr`.

- Add `costToCompany()` of each department, from `curr` to the end of the list.
- If `curr->getData()` is `NULL` (no department), add `0` for that node.
- If `curr` is `NULL`, there are no nodes, so return `0`. (This also covers an empty company.)

## Rules

- You must use recursion. **No loops (`for`, `while`, `do`) and no helper functions. Using either scores 0.** The function must call itself; it may not call any other function you write. Calling the given `costToCompany()` of a department is allowed.
- Implement only `Company::totalCost` in `B_1.cpp`. The declaration is already in `Company.h`.
- Your code must compile with `-std=c++98 -Wall -Werror` and must not leak memory.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `B_1` folder.
2. Run `make B_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `B_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
