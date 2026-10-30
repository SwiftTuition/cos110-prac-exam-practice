Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A1-03. Exceptions: `Employee::setIDNum` (the age must match the birth year) (100)

For this question, implement the `setIDNum` function of the `Employee` class in the file `A_1.cpp`. The function checks that a new ID number fits the employee: the birth year must give the employee's `age`, and the gender digits must give the employee's `gender`. If the ID number is valid, it is stored in `idNum`. If it is not valid, the function throws an `Exception`.

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
+ setIDNum(string): void   <- implement
+ extractIntFromString(string, int, int): int   {static}
+ operator<<(ostream&, const Employee&): ostream&   {friend}
```

Not on the published partial UML: `operator<<` (not drawn; the scenario says every class has one), the `int` return type of `extractIntFromString` (the UML shows no return type). The real exam's complete UML may add members like these.

## ID numbers

A South African ID number in this question is a string of 13 characters. The positions are counted from 0:

| Index | Meaning |
|---|---|
| 0 to 1 | year of birth (YY) |
| 2 to 3 | month of birth (MM) |
| 4 to 5 | day of birth (DD) |
| 6 to 9 | gender digits: 0000 to 4999 is female (`'F'`), 5000 to 9999 is male (`'M'`) |
| 10 to 12 | other digits (not checked) |

`Employee::extractIntFromString(str, start, end)` is given. It returns the number made by the characters from index `start` up to, **but not including**, index `end`. For example, `extractIntFromString("9702140123081", 6, 10)` returns `123`. It throws `Exception("Invalid range")` for a bad range and `Exception("Not a digit")` if one of those characters is not a digit.

## How to work out the age

- Read `YY` (index 0 to 1) with `extractIntFromString(idNum, 0, 2)`.
- Rule for this question only: if `YY` is 26 or less, the birth year is `2000 + YY`. Otherwise it is `1900 + YY`.
- Use 2026 as the current year. The age that the ID number gives is `2026 - birthYear`. Ignore the month and the day.

Examples: `97` gives 1997 and age 29. `26` gives 2026 and age 0. `27` gives 1927 and age 99. `00` gives 2000 and age 26.

## What `setIDNum(string idNum)` must do

Do the checks in this order. Stop at the first check that fails, and throw an `Exception` with exactly this message:

| Order | Check | Message |
|---|---|---|
| 1 | The length is not 13. | `ID number must have 13 digits` |
| 2 | The age from the ID number is not equal to `age`. | `ID number does not match age` |
| 3 | The gender digits (index 6 to 9) do not match `gender`. 5000 or more means `'M'`, less than 5000 means `'F'`. | `ID number does not match gender` |

If all three checks pass, store the new ID number in `idNum`.

More rules:

- If a check fails, `idNum` keeps its old value.
- If the year digits or the gender digits are not digits, `extractIntFromString` throws `Exception("Not a digit")`. Do not catch it inside `setIDNum`. Let it go to the caller.
- This version does not check the month, the day or the other characters.
- `setIDNum` must not catch its own exceptions and must not print anything.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_1` folder.
2. Run `make A_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
