Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A1-06. Exceptions: `Department::operator[]` with two error messages (100)

For this question, implement the subscript operator `operator[]` of the `Department` class in the file `A_1.cpp`. It returns a **reference to a slot** of the `teams` array (type `Team*&`). Because it returns a reference, the caller can read the pointer and can also store a new pointer in the slot, for example `(*sales)[2] = new Team(1);`. For a bad index there is no slot to return, so the operator must throw an `Exception`.

## UML (only the classes this question needs)

```text
Exception
+ message: string
+ Exception(string)
+ what(): string

Department
- teams: Team**
- size: int
# countEmployees(): int
+ Department(int)
+ ~Department()   {virtual}
+ addTeam(Team*): void
+ operator[](int): Team*&   <- implement
+ getSize(): int
+ costToCompany(): float   {virtual}
+ getName(): string   {virtual}
+ operator<<(ostream&, Department&): ostream&   {friend}

Team
- members: Employee**
- size: int
+ Team(int)
+ ~Team()
+ addMember(Employee*): void
+ operator[](int): const Employee&
+ getSize(): int
+ getMemberCount(): int
+ operator<<(ostream&, const Team&): ostream&   {friend}

Sales : Department
+ Sales(int)
+ getName(): string
# costToCompany(): float
```

Not on the published partial UML: `Department::countEmployees`, `Department::getSize`, `Department::getName`, `Team::addMember`, `Team::getMemberCount`, `Sales::getName`, `operator<<` (not drawn; the scenario says every class has one), the `{virtual}` markers (the UML marks nothing virtual). The real exam's complete UML may add members like these.

`Employee` is the same as in the other questions. See `Employee.h`.

## Given code you will use

- `Department(int size)` makes an array of `size` team pointers. Every slot starts as `NULL`.
- `addTeam(Team*)` puts a team in the first empty slot. The department owns its teams and deletes them in `~Department()`.
- `Sales::costToCompany()` is R15000 for each employee in all its teams. This is only for the printed cost.

## What `operator[](int index)` must do

1. If `index` is less than 0, throw `Exception("Negative index")`.
2. Otherwise, if `index` is greater than or equal to `size`, throw `Exception("Index too large")`.
3. Otherwise, return the slot `teams[index]` by reference.

More rules:

- An empty slot is **not** an error. If `teams[index]` is `NULL`, return the reference to that `NULL` pointer. The caller can test it (`if ((*d)[1] == NULL)`) or fill it.
- Do not catch the exception and do not print anything.
- When an assignment such as `(*d)[3] = extra;` throws, nothing is stored, so the caller still owns `extra` and must delete it (see `main.cpp`).

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_1` folder.
2. Run `make A_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
