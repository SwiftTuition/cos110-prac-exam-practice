Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A1-04. Exceptions: `Employee::extractIntFromString` (100)

For this question, implement the static function `extractIntFromString` of the `Employee` class in the file `A_1.cpp`. The function turns a part of a string into an `int`. It throws an `Exception` when the part is not valid. The given `setIDNum` uses it to read the gender digits of an ID number.

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
+ extractIntFromString(string, int, int): int   {static}   <- implement
+ operator<<(ostream&, const Employee&): ostream&   {friend}
```

Not on the published partial UML: `operator<<` (not drawn; the scenario says every class has one), the `int` return type of `extractIntFromString` (the UML shows no return type). The real exam's complete UML may add members like these.

## What `extractIntFromString(string str, int start, int end)` must do

- The part to read starts at index `start` and stops **before** index `end`. So it is the characters `str[start]`, `str[start + 1]`, ..., `str[end - 1]`.
- Example: `extractIntFromString("9702140123081", 6, 10)` reads `"0123"` and returns `123`. Leading zeros are allowed.
- First check the range. If `start < 0`, or `start >= end`, or `end` is greater than the length of `str`, throw `Exception("Invalid range")`.
- Then check the characters in the range. If one of them is not a digit (`'0'` to `'9'`), throw `Exception("Not a digit")`. Characters outside the range are not checked.
- Otherwise return the number. A digit character `c` has the value `c - '0'`.
- A range is never longer than 9 digits, so the result always fits in an `int`.

More rules:

- Do not print anything and do not catch the exceptions. The caller catches them by reference.
- In `A_1.cpp`, write the function as `int Employee::extractIntFromString(string str, int start, int end)`. Do not repeat the word `static` outside the class.
- `str.length()` is unsigned. Cast it, `(int)str.length()`, before you compare it with an `int`, or `-Wall -Werror` stops the build.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_1` folder.
2. Run `make A_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
