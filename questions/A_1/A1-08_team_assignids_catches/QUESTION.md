Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A1-08. Exceptions: `Team::assignIDs` catches each error and continues (100)

For this question, implement the `assignIDs` function of the `Team` class in the file `A_1.cpp`. The function gives ID numbers to the members of the team. `setIDNum` throws an `Exception` for a bad ID number. Your function must **catch** each exception, print its message and continue with the next slot. No exception may leave `assignIDs`.

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
+ assignIDs(string*, int): int   <- implement
+ operator<<(ostream&, const Team&): ostream&   {friend}
```

Not on the published partial UML: `Team::addMember`, `Team::removeMember`, `Team::getMemberCount`, `Team::assignIDs` (the target), `operator<<` (not drawn; the scenario says every class has one), the `int` return type of `extractIntFromString` (the UML shows no return type). The real exam's complete UML may add members like these.

## Given code you will use

- `Employee::setIDNum(string)` throws `Exception("ID number must have 13 digits")` if the length is not 13, `Exception("Not a digit")` if a gender digit (index 6 to 9) is not a digit, and `Exception("ID number does not match gender")` if digits 6 to 9 do not match the gender (5000 or more is `'M'`). If it throws, the old ID number is kept.
- `Team(int size)` makes an array of `size` pointers. Every slot starts as `NULL`. An empty slot is `NULL`.
- `addMember(Employee*)` puts the employee in the first empty slot. The team owns its employees and deletes them in `~Team()`.
- `removeMember(int index)` deletes the employee in that slot and sets the slot to `NULL`. It does nothing for a bad index or an empty slot.

## What `assignIDs(string* ids, int n)` must do

`ids` is an array of `n` ID numbers. `ids[i]` is meant for the employee in slot `i` of `members`.

- If `ids` is `NULL` or `n` is 0 or less, print nothing and return 0.
- Otherwise, for each `i` from 0 to `n - 1`, print exactly one line:

| Case | Line printed |
|---|---|
| `i` is not a slot of the array (`i >= size`) | `Slot <i>: no such slot` |
| the slot is empty (`NULL`) | `Slot <i>: empty` |
| `setIDNum(ids[i])` works | `Slot <i>: <firstName> <surName> -> <the new ID number>` |
| `setIDNum(ids[i])` throws `e` | `Slot <i>: <firstName> <surName> -> Error: <e.what()>` |

- Return the number of ID numbers that were set.

Example line: `Slot 1: Sipho Dlamini -> Error: ID number does not match gender`

More rules:

- Catch by reference: `catch (Exception& e)`.
- One bad ID number must not stop the rest.
- An uncaught exception stops the program abnormally, and the mark is 0.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_1` folder.
2. Run `make A_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.

Hints for this practice question are in `HINTS.md` in this folder.
