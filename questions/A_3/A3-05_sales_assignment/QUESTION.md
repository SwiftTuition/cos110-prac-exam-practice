Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A3-05. Assignment operator: `Sales::operator=` in a derived class (100)

For this question, implement the assignment operator of the `Sales` class in the file `A_3.cpp`. `Sales` inherits from `Department`. All the other functions are given in the other files, including `Department::operator=`.

**Note:** in this question `Sales` has one extra attribute, `target`.

## UML (only the classes this question needs)

```text
Department
- teams: Team**
- size: int
# countEmployees(): int
+ Department(int)
+ ~Department()   {virtual}
+ operator=(const Department&): Department&
+ addTeam(Team*): void
+ operator[](int): Team*&
+ getSize(): int
+ costToCompany(): float   {virtual}
+ getName(): string   {virtual}
+ operator<<(ostream&, Department&): ostream&   {friend}

Sales : Department
- target: int
+ Sales(int)
+ operator=(const Sales&): Sales&   <- implement
+ setTarget(int): void
+ getTarget(): int
+ getName(): string
# costToCompany(): float

Team
- members: Employee**
- size: int
+ Team(int)
+ Team(const Team&)
+ ~Team()
+ addMember(Employee*): void
+ removeMember(int): void
+ operator[](int): const Employee&
+ getSize(): int
+ getMemberCount(): int
+ operator<<(ostream&, const Team&): ostream&   {friend}

Employee
- age: int
- firstName: string
- surName: string
- idNum: string
- gender: char
+ Employee(string, string, int, char)
+ Employee(const Employee&)
+ operator<<(ostream&, const Employee&): ostream&   {friend}

Exception
+ message: string
+ Exception(string)
+ what(): string
```

The other `Employee` members are in `Employee.h`.

Not on the published partial UML: `Sales::operator=` (the target), `Sales::target`, `Sales::setTarget`, `Sales::getTarget`, `getName()` in `Department` and `Sales`, `Department::operator=`, `Department::countEmployees`, `Department::getSize`, the `{virtual}` markers (the UML marks nothing virtual), `Team(const Team&)`, `Team::addMember`, `Team::removeMember`, `Team::getMemberCount`, `operator<<` (not drawn; the scenario says every class has one). The real exam's complete UML may add members like these.

How the given classes work:

- `Department::operator=` is given. It makes a deep copy of the other department's `teams` array and sets `size`. A deep copy gets its own new objects; it does not share them with the original. It checks for self-assignment and returns `*this`.
- `teams` and `size` are **private** in `Department`, so `Sales` cannot use them directly.
- A new `Sales` object has `target` equal to `0`. `Sales::costToCompany()` returns the number of employees times 15000.
- The `Department` copy constructor and `Team::operator=` are not used in this question, so they are declared private.

## What `Sales::operator=` must do

The statement `a = b;` (both are `Sales` objects) makes `a` a deep copy of `b`.

1. If the object is assigned to itself (`a = a;`), do nothing and return the object.
2. Use the given `Department::operator=` so that `Department` copies its own part. `teams` and `size` are private in `Department`, so `Sales` cannot copy them itself.
3. Copy `target` from the other object.
4. Return the current object by reference (`*this`), so that `a = b = c;` works.

## Rules

- Implement only `Sales::operator=` in `A_3.cpp`. The declaration is already in `Sales.h`.
- Your code must compile with `-std=c++98 -Wall -Werror`. Memory is marked: `valgrind` must show no leaks and no invalid reads or frees.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_3` folder.
2. Run `make A_3`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_3.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.

Hints for this practice question are in `HINTS.md` in this folder.
