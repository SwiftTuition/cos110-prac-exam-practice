Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# B1-01. Recursion: `Employee::extractIntFromString` (100)

For this question, implement the static function `extractIntFromString` of the `Employee` class **using recursion**, in the file `B_1.cpp`. All the other functions of `Employee` and `Exception` are given in the other files.

**Note:** in this question, `extractIntFromString` returns `-1` for invalid input. It does not throw. The given `setIDNum` calls it and expects `-1` when a part of the ID number is not valid.

## UML (only the classes this question needs)

```text
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

Exception
+ message: string
+ Exception(string)
+ what(): string
```

Not on the published partial UML: the `int` return type of `extractIntFromString` (the UML shows no return type), `operator<<` (not drawn; the scenario says every class has one). The real exam's complete UML may add members like these.

## What `extractIntFromString(str, start, end)` must do

It reads the characters of `str` from index `start` up to, **but not including**, index `end`, and returns them as one whole number.

- Example: for `str = "9702140123081"`, `extractIntFromString(str, 0, 2)` returns `97`, and `extractIntFromString(str, 6, 10)` reads `"0123"` and returns `123`.
- Leading zeros are allowed: `"007"` gives `7`, and `"000"` gives `0`.
- Return `-1` if the range is invalid. The range is invalid when `start < 0`, or `start >= end` (an empty range), or `end` is more than the length of `str`.
- Return `-1` if **any** character in the range is not a digit (`'0'` to `'9'`). Characters outside the range are not checked.
- `0` is a real result (for example `"00"`), so it cannot be used to mean "invalid". That is why invalid input gives `-1` in this question.
- The range is never longer than 9 characters, so the result always fits in an `int`.

## Rules

- You must use recursion. **No loops (`for`, `while`, `do`) and no helper functions. Using either scores 0.** The function must call itself; it may not call any other function you write.
- Implement only `Employee::extractIntFromString` in `B_1.cpp`. The declaration is already in `Employee.h`. Do not write `static` again in `B_1.cpp`.
- `str.length()` is unsigned. Cast it, `(int)str.length()`, before you compare it with an `int`, or `-Wall -Werror` stops the build.
- Your code must compile with `-std=c++98 -Wall -Werror` and must not leak memory.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `B_1` folder.
2. Run `make B_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `B_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.

Hints for this practice question are in `HINTS.md` in this folder.
