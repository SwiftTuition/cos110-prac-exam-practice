Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A2-07. Operator overloading: `Employee::operator==` and `operator!=` (100)

For this question, implement the two comparison operators `operator==` and `operator!=` of the `Employee` class in the file `A_2.cpp`. Two `Employee` objects are the same person when they have the same ID number.

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
+ operator==(const Employee&): bool   {const}   <- implement
+ operator!=(const Employee&): bool   {const}   <- implement
+ operator<<(ostream&, const Employee&): ostream&   {friend}
```

Not on the published partial UML: `Employee::operator==` (the target), `Employee::operator!=` (the target), `operator<<` (not drawn; the scenario says every class has one), the `int` return type of `extractIntFromString` (the UML shows no return type). The real exam's complete UML may add members like these.

Both operators are `const` member functions (see `Employee.h`).

## What the operators must return

`a == b` is `true` when the two `idNum` strings are equal. Otherwise it is `false`. The names, the age and the gender are **not** compared.

`a != b` must always give the opposite of `a == b`.

Results to check your work:

| Case | `a == b` | `a != b` |
|---|---|---|
| same ID number, different names | `true` | `false` |
| different ID numbers | `false` | `true` |
| one ID number set, the other not set | `false` | `true` |
| **both** ID numbers not set | `true` | `false` |
| an employee compared with itself | `true` | `false` |

Look at row 4 carefully (both ID numbers not set). An ID number that is not set yet is the empty string `""`. Two employees with no ID number both have `""`, so they are equal, even if their names are different. The marking program checks this case.

More rules:

- Inside the member function you may read `other.idNum` directly, because `other` is an object of the same class.
- Write `const` after the parameter list in `A_2.cpp`, exactly as in the header.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.

Hints for this practice question are in `HINTS.md` in this folder.
