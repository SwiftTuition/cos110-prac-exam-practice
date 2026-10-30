Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# B1-04. Recursion: `Department::totalEmployees` (100)

For this question, implement the function `totalEmployees` of the `Department` class **using recursion**, in the file `B_1.cpp`. All the other functions of `Department`, `Team`, `Employee` and `Exception` are given in the other files.

## UML (only the classes this question needs)

```text
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
+ totalEmployees(int): int   <- implement
+ operator<<(ostream&, Department&): ostream&   {friend}

Team
- members: Employee**
- size: int
+ Team(int)
+ ~Team()
+ addMember(Employee*): void
+ removeMember(int): void
+ operator[](int): const Employee&
+ getSize(): int
+ getMemberCount(): int
+ operator<<(ostream&, const Team&): ostream&   {friend}
```

`Employee` and `Exception` are the same as in the other questions. See `Employee.h` and `Exception.h`.

Not on the published partial UML: `Department::totalEmployees` (the target), `Department::getSize`, `Department::getName`, the `{virtual}` markers (the UML marks nothing virtual), `Team::addMember`, `Team::removeMember`, `Team::getMemberCount`, `operator<<` (not drawn; the scenario says every class has one). The real exam's complete UML may add members like these.

How the given classes work:

- `teams` is an array of `size` pointers. Each slot holds a `Team*` or `NULL`. `NULL` means the slot is empty.
- `Team::getMemberCount()` is given. It returns the number of employees in that team (the member slots that are not `NULL`).

## What `totalEmployees(index)` must do

It returns the total number of employees in the teams from slot `index` to the last slot (`size - 1`).

- An empty slot (`NULL`) adds `0`. A team with no employees also adds `0`.
- `totalEmployees(0)` counts every employee in the department.
- When `index` is equal to `size`, there are no slots left, so return `0`.
- Invalid input: if `index` is less than `0` or more than `size`, return `0`.

Example: for slots `team with 2 employees, empty, team with 1 employee, empty`, `totalEmployees(0)` returns `3`, `totalEmployees(2)` returns `1` and `totalEmployees(3)` returns `0`.

## Rules

- You must use recursion. **No loops (`for`, `while`, `do`) and no helper functions. Using either scores 0.** The function must call itself; it may not call any other function you write. Calling the given `Team::getMemberCount()` is allowed.
- Implement only `Department::totalEmployees` in `B_1.cpp`. The declaration is already in `Department.h`.
- Use the members `teams` and `size` directly.
- Your code must compile with `-std=c++98 -Wall -Werror` and must not leak memory.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `B_1` folder.
2. Run `make B_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `B_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
