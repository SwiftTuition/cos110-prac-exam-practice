Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A2-06. Operator overloading: `Department::operator[]` returning `Team*&` (100)

For this question, implement the subscript operator `operator[]` of the `Department` class in the file `A_2.cpp`. The return type is `Team*&`: a **reference to a pointer** in the `teams` array. The caller can use it to read the pointer, to call a function on the team, or to store a new pointer in the slot:

```cpp
(*dev)[0] = new Team(2);                  // store a pointer in slot 0
(*dev)[0]->addMember(new Employee(...));  // use the team in slot 0
Team* temp = (*dev)[0];                   // read the pointer in slot 0
```

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

Not on the published partial UML: `Department::countEmployees`, `Department::getSize`, `Department::getName`, `Development::getName`, `Team::addMember`, `Team::getMemberCount`, `operator<<` (not drawn; the scenario says every class has one), the `{virtual}` markers (the UML marks nothing virtual). The real exam's complete UML may add members like these.

`Employee` is the same as in the other questions. See `Employee.h`.

## Given code you will use

- `Department(int size)` makes an array of `size` team pointers. Every slot starts as `NULL`.
- `addTeam(Team*)` puts a team in the first `NULL` slot and throws `Exception("Department is full")` when there is none.
- The department owns its teams and deletes every slot in `~Department()`.
- `operator<<` prints `<name> (cost R<cost>)` and then each team that is not `NULL`. Development costs R25000 per employee.

## What `operator[](int index)` must do

1. If `index` is less than 0, or greater than or equal to `size`, throw `Exception("Index out of bounds")`.
2. Otherwise, return the slot `teams[index]` **by reference**.

More rules:

- An empty slot is not an error. Return the reference to the `NULL` pointer, so that the caller can test it or fill it.
- Return the array element itself, not a local copy of the pointer. A reference to a local variable is not valid after the function returns, and `-Wall -Werror` rejects it.
- Do not print anything and do not catch the exception.
- The caller owns the team in a slot. Before it stores a new pointer in a slot that already holds a team, the caller must delete the old team.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
