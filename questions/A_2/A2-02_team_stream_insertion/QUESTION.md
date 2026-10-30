Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A2-02. Operator overloading: `operator<<` for `Team` (skips empty slots) (100)

For this question, implement the stream insertion operator `operator<<` for the `Team` class in the file `A_2.cpp`. It is a `friend` function of `Team`. It prints a heading and then every employee in the team.

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
+ operator[](int): const Employee&
+ getSize(): int
+ getMemberCount(): int
+ operator<<(ostream&, const Team&): ostream&   {friend}   <- implement
```

Not on the published partial UML: `Team::addMember`, `Team::removeMember`, `Team::getMemberCount`, `operator<<` (not drawn; the scenario says every class has one; the one for `Team` is the target), the `int` return type of `extractIntFromString` (the UML shows no return type). The real exam's complete UML may add members like these.

## Given code you will use

- `Team(int size)` makes an array of `size` pointers. Every slot starts as `NULL`. An empty slot is `NULL`.
- `addMember(Employee*)` puts the employee in the first empty slot. The team owns its employees and deletes them in `~Team()`.
- `removeMember(int index)` deletes the employee in that slot and sets the slot to `NULL`. It does nothing for a bad index or an empty slot.
- `Employee`'s `operator<<` (given) prints `<firstName> <surName>, <age>, <gender>, ID: <idNum>`, or `ID: none` when no ID number is set. It does not print a newline.

## What `operator<<(ostream& out, const Team& t)` must print

1. A heading line: `Team (<count>/<size>):` where `<count>` is the number of slots that are not `NULL`, and `<size>` is the length of the array.
2. If `<count>` is 0, one more line: two spaces, then `(no members)`.
3. Otherwise, for each slot that is not `NULL`, in slot order (index 0 first): two spaces, then the employee printed with `Employee`'s `operator<<`.

Every line ends with `endl`, including the last one. Example for a team of size 3 with an empty slot 0:

```text
Team (1/3):
  Sipho Dlamini, 35, M, ID: none
```

More rules:

- Skip empty (`NULL`) slots. Do not dereference them.
- Write to `out`, not to `cout`, and return `out`.
- Note: `t` is a `const` reference. `getMemberCount()` and `operator[]` are not `const` member functions, so `t` cannot call them. Count the members yourself using `t.members` and `t.size`, which a friend may read.
- Write the word `friend` only in the class. Do not write it again in `A_2.cpp`.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
