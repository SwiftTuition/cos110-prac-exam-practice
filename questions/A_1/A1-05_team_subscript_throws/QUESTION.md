Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A1-05. Exceptions: `Team::operator[]` throws for a bad index or an empty slot (100)

For this question, implement the subscript operator `operator[]` of the `Team` class in the file `A_1.cpp`. It returns the employee in a slot of the `members` array. The return type is a reference, so the operator cannot return `NULL`. When there is no employee to return, it must throw an `Exception`.

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
+ operator[](int): const Employee&   <- implement
+ getSize(): int
+ getMemberCount(): int
+ operator<<(ostream&, const Team&): ostream&   {friend}
```

Not on the published partial UML: `Team::addMember`, `Team::removeMember`, `Team::getMemberCount`, `operator<<` (not drawn; the scenario says every class has one), the `int` return type of `extractIntFromString` (the UML shows no return type). The real exam's complete UML may add members like these.

## Given code you will use

- `Team(int size)` makes an array of `size` pointers. Every slot starts as `NULL`. An empty slot is `NULL`.
- `addMember(Employee*)` puts the employee in the first empty slot. The team owns its employees and deletes them in `~Team()`.
- `removeMember(int index)` deletes the employee in that slot and sets the slot to `NULL`. It does nothing for a bad index or an empty slot.

## What `operator[](int index)` must do

1. If `index` is less than 0, or `index` is greater than or equal to `size`, throw `Exception("Index out of bounds")`.
2. Otherwise, if the slot `members[index]` is `NULL`, throw `Exception("No employee at this index")`.
3. Otherwise, return the employee in that slot: `*members[index]`.

More rules:

- Do the range check first. Reading `members[index]` with a bad index reads memory outside the array, and valgrind reports it.
- Do not catch the exception and do not print anything. The caller catches it by reference, `catch (Exception& e)`.
- In some other questions both errors use one message. Here they use two.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_1` folder.
2. Run `make A_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
