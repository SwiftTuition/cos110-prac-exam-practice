Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A1-07. Exceptions: `Team::addMember` (NULL, already in the team, full) (100)

For this question, implement the `addMember` function of the `Team` class in the file `A_1.cpp`. It adds an employee to the `members` array. The team then owns the employee and deletes it in `~Team()`. When the employee cannot be added, the function throws an `Exception` and the team does not keep the pointer.

## UML (only the classes this question needs)

```text
Exception
+ message: string
+ Exception(string)
+ what(): string

Employee
- age: int
- firstName: string
- surName: string
- idNum: string
- gender: char
+ Employee(string, string, int, char)
+ Employee(const Employee&)
+ getFirstName(): string
+ getSurName(): string
+ getIDNum(): string
+ getAge(): int
+ getGender(): char
+ setIDNum(string): void
+ extractIntFromString(string, int, int): int   {static}
+ operator<<(ostream&, const Employee&): ostream&   {friend}

Team
- members: Employee**
- size: int
+ Team(int)
+ ~Team()
+ addMember(Employee*): void   <- implement
+ removeMember(int): void
+ operator[](int): const Employee&
+ getSize(): int
+ getMemberCount(): int
+ operator<<(ostream&, const Team&): ostream&   {friend}
```

Not on the published partial UML: `Team::addMember` (the target), `Team::removeMember`, `Team::getMemberCount`, `operator<<` (not drawn; the scenario says every class has one), the `int` return type of `extractIntFromString` (the UML shows no return type). The real exam's complete UML may add members like these.

## What `addMember(Employee* employee)` must do

Do the checks in this order. Stop at the first check that fails, and throw an `Exception` with exactly this message:

| Order | Check | Message |
|---|---|---|
| 1 | `employee` is `NULL`. | `Employee is NULL` |
| 2 | The same pointer is already stored in **any** slot of `members`. | `Employee is already in the team` |
| 3 | There is no empty (`NULL`) slot. | `Team is full` |

If all checks pass, store `employee` in the **first** empty slot (the lowest index that is `NULL`).

More rules:

- "Already in the team" means the same address (pointer), not the same name or ID number. Look at every slot, also slots after an empty slot. If the same pointer were stored twice, `~Team()` would delete it twice.
- When the function throws, it must not change `members`. The caller still owns the employee and must delete it (see `main.cpp`).
- Do not catch the exception and do not print anything.

## Given code you will use

- `removeMember(int index)` deletes the employee in that slot and sets the slot to `NULL`.
- `operator[](int)` returns the employee in a slot and throws `Exception("Index out of bounds")` for a bad index or an empty slot.
- `operator<<` prints `Team:` and then each employee on its own line.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_1` folder.
2. Run `make A_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
