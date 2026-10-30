Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# B1-09. Recursion: `Employee::checksum` (100)

For this question, implement the static function `checksum` of the `Employee` class **using recursion**, in the file `B_1.cpp`. All the other functions of `Employee` and `Exception` are given in the other files.

**Note:** a South African ID number ends with a check digit. The given `setIDNum` uses `checksum` to test that check digit. Only this question checks the check digit. In the other questions of this bank, an ID number such as `9702140123081` is accepted as a normal ID number.

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
+ checksum(string, int): int   {static}   <- implement
+ operator<<(ostream&, const Employee&): ostream&   {friend}

Exception
+ message: string
+ Exception(string)
+ what(): string
```

Not on the published partial UML: `Employee::checksum` (the target), the `int` return type of `extractIntFromString` (the UML shows no return type), `operator<<` (not drawn; the scenario says every class has one). The real exam's complete UML may add members like these.

## The Luhn sum

The check uses the Luhn rule. Look at every digit of `id`, from left to right:

- Count the characters **after** this digit (to the end of `id`). That number is `id.length() - 1 - index`.
- If that number is **odd**, double the digit. If the doubled value is more than 9, subtract 9 from it.
- If that number is **even**, use the digit as it is. (So the last digit is never doubled.)

The Luhn sum is the total of these values. An ID number is valid when its Luhn sum is a multiple of 10.

Worked example for `"7918"`:

| Index | Digit | Characters after it | Odd or even | Value |
|---|---|---|---|---|
| 0 | 7 | 3 | odd: 7 x 2 = 14, more than 9, so 14 - 9 | 5 |
| 1 | 9 | 2 | even | 9 |
| 2 | 1 | 1 | odd: 1 x 2 | 2 |
| 3 | 8 | 0 | even | 8 |

The Luhn sum is `5 + 9 + 2 + 8 = 24`. It is not a multiple of 10, so `"7918"` is not valid. `checksum("7918", 2)` is `2 + 8 = 10`: the `1` is still doubled, because the characters after it are counted to the end of the whole string.

## What `checksum(id, index)` must do

It returns the Luhn sum of the digits from position `index` to the end of `id`. The doubling rule always counts the characters after a digit up to the end of the **whole** string `id`.

- `checksum(id, 0)` is the Luhn sum of the whole ID number.
- When `index` is equal to the length of `id`, there are no digits left, so return `0`.
- Invalid input: if `index` is less than `0` or more than the length of `id`, return `0`.
- You may assume that `id` holds only digits. (`setIDNum` checks this before it calls `checksum`.)

Examples: `checksum("79927398713", 0)` is `70`. `checksum("9702140123086", 0)` is `50`, so that ID number is valid. `checksum("9702140123081", 0)` is `45`, so that one is not.

## Rules

- You must use recursion. **No loops (`for`, `while`, `do`) and no helper functions. Using either scores 0.** The function must call itself; it may not call any other function you write.
- Implement only `Employee::checksum` in `B_1.cpp`. The declaration is already in `Employee.h`. Do not write `static` again in `B_1.cpp`.
- `id.length()` is unsigned. Cast it, `(int)id.length()`, before you use it with an `int`, or `-Wall -Werror` stops the build.
- Your code must compile with `-std=c++98 -Wall -Werror` and must not leak memory.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `B_1` folder.
2. Run `make B_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `B_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
