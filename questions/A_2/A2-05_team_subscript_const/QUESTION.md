Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A2-05. Operator overloading: `Team::operator[]` (const) returning `const Employee&` (100)

For this question, implement the subscript operator `operator[]` of the `Team` class in the file `A_2.cpp`. Like an array, `team[i]` gives the employee in slot `i`. In this question the operator is a `const` member function, so it also works on a `const Team&`.

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
+ addMember(Employee*): void
+ removeMember(int): void
+ operator[](int): const Employee&   {const}   <- implement
+ getSize(): int
+ getMemberCount(): int
+ operator<<(ostream&, const Team&): ostream&   {friend}
```

Not on the published partial UML: `Team::addMember`, `Team::removeMember`, `Team::getMemberCount`, `operator<<` (not drawn; the scenario says every class has one), the `{const}` on `Team::operator[]` (the published UML does not mark it `const`), the `int` return type of `extractIntFromString` (the UML shows no return type). The real exam's complete UML may add members like these.

The UML marks this with `{const}`. In C++ the word `const` goes after the parameter list: `const Employee& operator[](int index) const;`.

## Given code you will use

- `Team(int size)` makes an array of `size` pointers. Every slot starts as `NULL`. An empty slot is `NULL`.
- `addMember(Employee*)` puts the employee in the first empty slot. The team owns its employees and deletes them in `~Team()`.
- `removeMember(int index)` deletes the employee in that slot and sets the slot to `NULL`. It does nothing for a bad index or an empty slot.

## What `operator[](int index) const` must do

1. If `index` is less than 0, or greater than or equal to `size`, or the slot `members[index]` is `NULL`, throw `Exception("Index out of bounds")`.
2. Otherwise, return the employee in that slot by reference: `*members[index]`.

More rules:

- The return type is a reference, so the operator cannot return `NULL`. Throwing is the only way to report a bad index.
- Check the range before you read `members[index]`.
- Write the word `const` after the parameter list in `A_2.cpp` as well, exactly as in the header. A `const` member function cannot change the team.
- Do not print anything and do not catch the exception.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
