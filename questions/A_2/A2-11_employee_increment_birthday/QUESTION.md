Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A2-11. Operator overloading: `Employee` prefix and postfix `operator++` (a birthday) (100)

For this question, implement **both** increment operators of the `Employee` class in the file `A_2.cpp`. Each one is a birthday: it adds 1 to `age`. The two versions return different things.

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
+ operator++(): Employee&   <- implement
+ operator++(int): Employee   <- implement
+ operator<<(ostream&, const Employee&): ostream&   {friend}
```

Not on the published partial UML: `Employee::operator++` (the target), `operator<<` (not drawn; the scenario says every class has one), the `int` return type of `extractIntFromString` (the UML shows no return type). The real exam's complete UML may add members like these.

## What the operators must do

| Operator | Use | What it does | Returns |
|---|---|---|---|
| `Employee& operator++()` | `++e` (prefix) | adds 1 to `age` | the employee itself, `*this`, by reference |
| `Employee operator++(int)` | `e++` (postfix) | adds 1 to `age` | a **copy** of the employee from **before** the change, by value |

Example: if `e` is 30, then `Employee old = e++;` makes `old` 30 and `e` 31.

More rules:

- Nothing else changes: not the names, not the gender and not the ID number.
- The `int` parameter of the postfix version has no name and is not used. It only tells C++ which version is meant.
- Because prefix returns a reference to the same object, `++(++e)` adds 2 to `e`.
- Use the given copy constructor `Employee(const Employee&)` to make the copy in the postfix version.
- `Employee`'s `operator<<` (given) prints `<firstName> <surName>, <age>, <gender>, ID: <idNum>`, or `ID: none` when no ID number is set. It does not print a newline.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
