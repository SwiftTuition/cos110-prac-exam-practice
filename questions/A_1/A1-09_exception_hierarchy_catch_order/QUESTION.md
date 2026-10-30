Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A1-09. Exceptions: `Team::setMemberID` catches two exception types (100)

For this question, implement the `setMemberID` function of the `Team` class in the file `A_1.cpp`. The function sets the ID number of one member and catches every exception that this can throw. Two exception types can be thrown: `InvalidIDException`, which is derived from `Exception`, and `Exception` itself. Each type must be handled in its own way.

## UML (only the classes this question needs)

```text
Exception
+ message: string
+ Exception(string)
+ what(): string

InvalidIDException : Exception
- badID: string
+ InvalidIDException(string, string)
+ getBadID(): string

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
+ operator[](int): const Employee&
+ getMember(int): Employee*
+ getSize(): int
+ getMemberCount(): int
+ setMemberID(int, string): bool   <- implement
+ operator<<(ostream&, const Team&): ostream&   {friend}
```

Not on the published partial UML: the class `InvalidIDException`, `Team::addMember`, `Team::getMember`, `Team::getMemberCount`, `Team::setMemberID` (the target), `operator<<` (not drawn; the scenario says every class has one), the `int` return type of `extractIntFromString` (the UML shows no return type). The real exam's complete UML may add members like these.

## Given code you will use

- `Employee::setIDNum(string idNum)`:
  - throws `InvalidIDException(idNum, "ID number must have 13 digits")` if the length is not 13;
  - throws `InvalidIDException(idNum, "ID number must contain only digits")` if a character is not a digit;
  - throws a plain `Exception("ID number does not match gender")` if digits 6 to 9 do not match the gender (5000 or more is `'M'`);
  - otherwise stores the ID number. After a throw, the old ID number is kept.
- `InvalidIDException` passes `message` to the `Exception` constructor, so `what()` returns the message. `getBadID()` returns the ID number that was rejected.
- `Team::getMember(int index)` returns the `Employee*` in a slot. It throws `Exception("No member at this index")` for a bad index or an empty slot.

## What `setMemberID(int index, string idNum)` must do

Inside a `try` block, get the member with `getMember(index)` and call `setIDNum(idNum)` on it. Then print one line and return:

| Case | Line printed | Return |
|---|---|---|
| no exception | `Member <index>: ID set to <idNum>` | `true` |
| an `Exception e` that is not an `InvalidIDException` | `Member <index>: <e.what()>` | `false` |
| an `InvalidIDException e` | `Member <index>: bad ID [<e.getBadID()>]: <e.what()>` | `false` |

Example lines:

```text
Member 1: bad ID [91052258000]: ID number must have 13 digits
Member 2: No member at this index
```

More rules:

- No exception may leave `setMemberID`. An uncaught exception stops the program abnormally, and the mark is 0.
- Catch each type by reference (with `&`).
- Order matters. An `InvalidIDException` is also an `Exception`. Think about which `catch` block must come first. If the order is wrong, g++ stops with an error.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_1` folder.
2. Run `make A_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.

Hints for this practice question are in `HINTS.md` in this folder.
