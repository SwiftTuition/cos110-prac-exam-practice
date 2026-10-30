Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# B1-02. Recursion: `Employee::isAllDigits` (100)

For this question, implement the static function `isAllDigits` of the `Employee` class **using recursion**, in the file `B_1.cpp`. All the other functions of `Employee` and `Exception` are given in the other files. The given `setIDNum` uses `isAllDigits` to check an ID number.

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
+ extractIntFromString(string, int, int): int   {static}
+ isAllDigits(string, int): bool   {static}   <- implement
+ operator<<(ostream&, const Employee&): ostream&   {friend}

Exception
+ message: string
+ Exception(string)
+ what(): string
```

Not on the published partial UML: `Employee::isAllDigits` (the target), the `int` return type of `extractIntFromString` (the UML shows no return type), `operator<<` (not drawn; the scenario says every class has one). The real exam's complete UML may add members like these.

## What `isAllDigits(str, index)` must do

It checks the characters of `str` from position `index` to the end of the string.

- Return `true` if every character from `index` to the end is a digit (`'0'` to `'9'`). Characters before `index` are not checked.
- Return `false` as soon as one of those characters is not a digit.
- When `index` is equal to the length of `str`, there is nothing left to check, so return `true`. (So `isAllDigits("", 0)` is `true`.)
- Invalid input: if `index` is less than `0` or more than the length of `str`, return `false`.

Examples: `isAllDigits("9702140123081", 0)` is `true`. `isAllDigits("abc123", 3)` is `true`. `isAllDigits("abc123", 0)` is `false`.

## Rules

- You must use recursion. **No loops (`for`, `while`, `do`) and no helper functions. Using either scores 0.** The function must call itself; it may not call any other function you write.
- Implement only `Employee::isAllDigits` in `B_1.cpp`. The declaration is already in `Employee.h`. Do not write `static` again in `B_1.cpp`.
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
