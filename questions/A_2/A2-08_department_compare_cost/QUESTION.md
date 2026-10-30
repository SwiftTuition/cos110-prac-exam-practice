Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A2-08. Operator overloading: `Department` `operator<` and `operator>` by cost (100)

For this question, implement the two comparison operators `operator<` and `operator>` of the `Department` class in the file `A_2.cpp`. Departments are compared by how much they cost the company each month.

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
+ operator[](int): Team*&
+ getSize(): int
+ costToCompany(): float   {virtual}
+ getName(): string   {virtual}
+ operator<(Department&): bool   <- implement
+ operator>(Department&): bool   <- implement
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
```

Not on the published partial UML: `Department::countEmployees`, `Department::getSize`, `Department::getName`, `Department::operator<` (the target), `Department::operator>` (the target), `Sales::getName`, `Marketing::getName`, `HR::getName`, `Development::getName`, `Team::addMember`, `Team::getMemberCount`, `operator<<` (not drawn; the scenario says every class has one), the `{virtual}` markers (the UML marks nothing virtual). The real exam's complete UML may add members like these.

`Employee` is the same as in the other questions. See `Employee.h`.

## Given code you will use

- `costToCompany()` is `virtual`. The base `Department` returns 0. Each subclass returns its number of employees (in all its teams) times a monthly cost: Sales R15000, Marketing R18000, HR R12000, Development R25000. `getName()` is also `virtual` and returns the class name, for example `"Sales"`.
- `addTeam(Team*)` puts a team in the first empty slot. `countEmployees()` (protected) counts the employees in all teams.

## What the operators must return

- `a < b` is `true` when `a.costToCompany()` is less than `b.costToCompany()`. Otherwise it is `false`.
- `a > b` is `true` when `a.costToCompany()` is greater than `b.costToCompany()`. Otherwise it is `false`.
- When the two costs are equal, both operators return `false`.

Example: a Sales department with 2 employees costs R30000, and a Development department with 1 employee costs R25000. So `sales < dev` is `false` and `sales > dev` is `true`.

More rules:

- Compare the **cost**, not the number of employees. Different departments have different costs per employee.
- Call `costToCompany()` on both objects. It is `virtual`, so the subclass rule is used even through a `Department&`.
- The parameter is `Department&` (not `const`), because `costToCompany()` is not a `const` member function.
- Do not print anything.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
