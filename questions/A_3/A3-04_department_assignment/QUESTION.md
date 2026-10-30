Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A3-04. Assignment operator: `Department::operator=` (100)

For this question, implement the assignment operator of the `Department` class in the file `A_3.cpp`. All the other functions of `Department`, `Team`, `Employee` and `Exception` are given in the other files.

## UML (only the classes this question needs)

```text
Department
- teams: Team**
- size: int
+ Department(int)
+ ~Department()   {virtual}
+ operator=(const Department&): Department&   <- implement
+ addTeam(Team*): void
+ operator[](int): Team*&
+ getSize(): int
+ costToCompany(): float   {virtual}
+ getName(): string   {virtual}
+ operator<<(ostream&, Department&): ostream&   {friend}

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

Not on the published partial UML: `Department::operator=` (the target), `Department::getSize`, `Department::getName`, the `{virtual}` markers (the UML marks nothing virtual), `Team(const Team&)`, `Team::addMember`, `Team::removeMember`, `Team::getMemberCount`, `operator<<` (not drawn; the scenario says every class has one). The real exam's complete UML may add members like these.

How the given classes work:

- `teams` is an array of `size` pointers. Each slot holds a `Team*` or `NULL`. `NULL` means the slot is empty.
- The department owns its teams. `~Department()` deletes every team and then the array. Each team deletes its own employees.
- `Team(const Team&)` is given. It makes a deep copy of a team: a new array, a new copy of every employee, and `NULL` slots stay `NULL`.
- `operator[](int)` returns a reference to a slot. It throws `Exception("Index out of bounds")` for an index outside `0` to `size - 1`.
- `addTeam` puts a team in the first empty slot and throws `Exception("Department is full")` when there is none.
- In `Department`, `costToCompany()` returns `0` and `getName()` returns `"Department"`.
- Two members are not used in this question, so they are declared private: the `Department` copy constructor and `Team::operator=`.

## What `operator=` must do

The statement `a = b;` makes department `a` a deep copy of department `b`. A deep copy gets its own new objects; it does not share them with the original.

1. If the department is assigned to itself (`a = a;`), do nothing and return the department.
2. Delete every team that this department owns, and then delete the `teams` array.
3. Set `size` to the other department's size and create a new array of that size.
4. For every slot of the other department: if the slot is `NULL`, this slot is `NULL`. Otherwise, this slot gets a **new copy** of that team (use the `Team` copy constructor). Every team stays in the same slot number. A team with no employees is still a team, so it is copied too.
5. Return the current object by reference (`*this`), so that `a = b = c;` works.

After the assignment, the two departments must not share any `Team` or `Employee` object.

## Rules

- Implement only `Department::operator=` in `A_3.cpp`. The declaration is already in `Department.h`.
- `other` is a `const Department&`. Use `other.size` and `other.teams` directly. This is allowed inside the class's own operator.
- Your code must compile with `-std=c++98 -Wall -Werror`. Memory is marked: `valgrind` must show no leaks and no invalid reads or frees.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_3` folder.
2. Run `make A_3`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_3.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
