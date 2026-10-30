Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A1-02. Exceptions: `Employee::setIDNum` (digits, month, day and gender) (100)

For this question, implement the `setIDNum` function of the `Employee` class in the file `A_1.cpp`. The function checks a new ID number in several ways. If the ID number is valid, it is stored in `idNum`. If it is not valid, the function throws an `Exception` that says what is wrong.

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

## What `setIDNum(string idNum)` must do

Do the checks in this order. Stop at the first check that fails, and throw an `Exception` with exactly this message:

| Order | Check | Message |
|---|---|---|
| 1 | The length is not 13. | `ID number must have 13 digits` |
| 2 | At least one character is not a digit (`'0'` to `'9'`). | `ID number must contain only digits` |
| 3 | The month (index 2 to 3) is not from 1 to 12. | `Invalid birth month` |
| 4 | The day (index 4 to 5) is not from 1 to 31. | `Invalid birth day` |
| 5 | The gender digits (index 6 to 9) do not match `gender`. 5000 or more means `'M'`, less than 5000 means `'F'`. | `ID number does not match gender` |

If all five checks pass, store the new ID number in `idNum`.

More rules:

- Use the given `extractIntFromString` to read the month, the day and the gender digits.
- Check the characters one by one for check 2. Do not convert all 13 digits into one `int`: a 13-digit number does not fit in an `int`.
- Do not check how many days a month has. For example, day 30 in month 02 is accepted.
- One test ID in `main.cpp` contains the letter `O`, not the digit `0`.
- If a check fails, `idNum` keeps its old value.
- `setIDNum` must not catch its own exceptions and must not print anything. The caller catches them by reference, `catch (Exception& e)`.
- Compare an `int` with `idNum.length()` carefully: `-Wall -Werror` turns a signed/unsigned comparison warning into an error. Cast the length, for example `(int)idNum.length()`.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_1` folder.
2. Run `make A_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
