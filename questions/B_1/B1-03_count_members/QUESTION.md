Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# B1-03. Recursion: `Team::countMembers` (100)

For this question, implement the function `countMembers` of the `Team` class **using recursion**, in the file `B_1.cpp`. All the other functions of `Team`, `Employee` and `Exception` are given in the other files.

## UML (only the classes this question needs)

```text
Team
- members: Employee**
- size: int
+ Team(int)
+ ~Team()
+ addMember(Employee*): void
+ removeMember(int): void
+ operator[](int): const Employee&
+ getSize(): int
+ countMembers(int): int   <- implement
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

Not on the published partial UML: `Team::countMembers` (the target), `Team::addMember`, `Team::removeMember`, `operator<<` (not drawn; the scenario says every class has one). The real exam's complete UML may add members like these.

How the given `Team` works:

- `members` is an array of `size` pointers. Each slot holds an `Employee*` or `NULL`. `NULL` means the slot is empty.
- `addMember` puts an employee in the first empty slot. `removeMember(i)` deletes the employee in slot `i` and sets the slot to `NULL`, so empty slots can be anywhere in the array.

## What `countMembers(index)` must do

It counts the slots that hold an employee (the slots that are not `NULL`), from slot `index` to the last slot (`size - 1`).

- `countMembers(0)` counts the whole team.
- When `index` is equal to `size`, there are no slots left, so return `0`.
- Invalid input: if `index` is less than `0` or more than `size`, return `0`.

Example: for a team of size 5 with slots `Thandi, empty, Anna, Ravi, empty`, `countMembers(0)` returns `3`, `countMembers(2)` returns `2` and `countMembers(4)` returns `0`.

## Rules

- You must use recursion. **No loops (`for`, `while`, `do`) and no helper functions. Using either scores 0.** The function must call itself; it may not call any other function you write.
- Implement only `Team::countMembers` in `B_1.cpp`. The declaration is already in `Team.h`.
- Use the members `members` and `size` directly.
- Your code must compile with `-std=c++98 -Wall -Werror` and must not leak memory.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `B_1` folder.
2. Run `make B_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `B_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
