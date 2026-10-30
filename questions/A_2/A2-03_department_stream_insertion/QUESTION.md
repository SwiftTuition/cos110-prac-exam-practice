Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A2-03. Operator overloading: `operator<<` for `Department` (virtual calls) (100)

For this question, implement the stream insertion operator `operator<<` for the `Department` class in the file `A_2.cpp`. It is a `friend` function of `Department`. The same operator must print every kind of department (Sales, Marketing, HR and Development) correctly.

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
+ operator<<(ostream&, Department&): ostream&   {friend}   <- implement

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

Not on the published partial UML: `Department::countEmployees`, `Department::getSize`, `Department::getName`, `Sales::getName`, `Marketing::getName`, `HR::getName`, `Development::getName`, `Team::addMember`, `Team::getMemberCount`, `operator<<` (not drawn; the scenario says every class has one; the one for `Department` is the target), the `{virtual}` markers (the UML marks nothing virtual). The real exam's complete UML may add members like these.

`Employee` is the same as in the other questions. See `Employee.h`.

## Given code you will use

- `costToCompany()` is `virtual`. The base `Department` returns 0. Each subclass returns its number of employees (in all its teams) times a monthly cost: Sales R15000, Marketing R18000, HR R12000, Development R25000. `getName()` is also `virtual` and returns the class name, for example `"Sales"`.
- `Team`'s `operator<<` (given) prints `Team (<count>/<size>):` on one line, then each employee on its own line with two spaces in front, or the line `  (no members)` for a team with no employees. Every line ends with `endl`.

## What `operator<<(ostream& out, Department& d)` must print

1. A heading line: `Department: <name> (cost R<cost>)`, where `<name>` is `d.getName()` and `<cost>` is `d.costToCompany()`. End the line with `endl`.
2. Each team that is not `NULL`, in slot order, printed with `Team`'s `operator<<`.
3. If the department has no team at all (every slot is `NULL`, or the size is 0), print one line instead (two spaces, then `(no teams)`) and end it with `endl`.

Example:

```text
Department: Development (cost R50000)
Team (2/2):
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
```

More rules:

- Print the cost with the normal `cout` format, as `R50000` (no decimals). All costs in this question stay below one million.
- Friend functions are not inherited, so there is no `operator<<` for `Sales`. A `Sales` object is printed through this operator as a `Department&`. Call the `virtual` functions `getName()` and `costToCompany()` so that the subclass versions run.
- The parameter is `Department&` (not `const`), because `getName()` and `costToCompany()` are not `const` member functions.
- Write to `out`, not to `cout`, and return `out`.
- Write the word `friend` only in the class. Do not write it again in `A_2.cpp`.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
