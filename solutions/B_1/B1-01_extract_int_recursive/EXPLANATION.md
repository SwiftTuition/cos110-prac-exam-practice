# B1-01 Explanation: recursive extractIntFromString

## What the function must do

The function `Employee::extractIntFromString(str, start, end)` turns a part of a string into a whole number. The function reads the characters from index `start` up to, but not including, index `end`. For `"9702140123081"` with range `6` to `10`, the characters are `"0123"` and the result is `123`.

The function returns `-1` if the range is invalid or if one character in the range is not a digit. The value `0` is a real answer (for example `"00"`), so `-1` marks an error. The function must use recursion, with no loops and no helper functions.

## How the solution works

The function reads the range from the right. The value of `"1234"` is the value of `"123"` times 10, plus 4. So the function asks itself for the range that is one character shorter.

```cpp
if (start < 0 || start >= end || end > (int)str.length()) {
    return -1;
}
```

This `if` checks the range. `start < 0` protects against a negative index. `start >= end` rejects an empty range, such as 2 to 2, and a reversed range, such as 3 to 2. `end > (int)str.length()` rejects a range that goes past the string. Without this check, `str[end - 1]` would read outside the string. The cast `(int)str.length()` is needed because `length()` is unsigned. Without the cast, g++ reports `comparison of integer expressions of different signedness`, and `-Wall -Werror` stops the build.

```cpp
if (str[end - 1] < '0' || str[end - 1] > '9') {
    return -1;
}
int lastDigit = str[end - 1] - '0';
```

`str[end - 1]` is the last character of the range. A `char` holds a number code. The codes of `'0'` to `'9'` are next to each other, so this `if` is true when the character is not a digit. The function then returns `-1` at once. Without this check, a letter would become a wrong number. The line `str[end - 1] - '0'` turns a digit character into its value. For example, `'3' - '0'` is `3`.

```cpp
if (end - start == 1) {
    return lastDigit;
}
```

This is the base case. The range has one character, and the function already checked that it is a digit. So the answer is that digit. Every recursive call lowers `end` by 1, so the range gets shorter until it has one character. Without this base case, the calls go on to the empty range `(start, start)`. The range check returns `-1` for that call, and the `-1` passes upward, so every valid range gives `-1`.

```cpp
int front = extractIntFromString(str, start, end - 1);
if (front == -1) {
    return -1;
}
return front * 10 + lastDigit;
```

This is the recursive case. The variable `front` holds the number made from the shorter range. The `if` checks for the error value. If the shorter range holds a letter, `front` is `-1`. The function must pass that `-1` upward. Without this `if`, the line `front * 10 + lastDigit` would turn `-1` into another number. For `"x123"` the result would be wrong instead of `-1`. The order matters: the function adds `lastDigit` after the recursive call returns, because the last digit has the smallest place value.

The function allocates no memory, so nothing is freed.

## Trace

The call is `extractIntFromString("9702140123081", 6, 10)`. The string has 13 characters. The characters at index 6 to 9 are `0`, `1`, `2`, `3`.

| Call | start, end | Last character | Branch taken | Result |
|---|---|---|---|---|
| 1 | 6, 10 | `str[9]` is `'3'` | recursive case, calls `(6, 9)` | waits |
| 2 | 6, 9 | `str[8]` is `'2'` | recursive case, calls `(6, 8)` | waits |
| 3 | 6, 8 | `str[7]` is `'1'` | recursive case, calls `(6, 7)` | waits |
| 4 | 6, 7 | `str[6]` is `'0'` | base case, `end - start == 1` | returns `0` |

The calls return in the order 4, 3, 2, 1:

- Call 3: `front` is `0`, so the call returns `0 * 10 + 1 = 1`.
- Call 2: `front` is `1`, so the call returns `1 * 10 + 2 = 12`.
- Call 1: `front` is `12`, so the call returns `12 * 10 + 3 = 123`.

A second call shows the error path: `extractIntFromString("12a45", 0, 5)`.

| Call | start, end | Last character | Branch taken | Result |
|---|---|---|---|---|
| 1 | 0, 5 | `str[4]` is `'5'` | recursive case, calls `(0, 4)` | waits |
| 2 | 0, 4 | `str[3]` is `'4'` | recursive case, calls `(0, 3)` | waits |
| 3 | 0, 3 | `str[2]` is `'a'` | not a digit | returns `-1` |

Call 2 receives `front == -1` and returns `-1`. Call 1 does the same, so the final answer is `-1`.

The output of `main.cpp` is:

```text
Year: 97
Month: 2
Day: 14
Gender digits: 123
Bad range: -1
Not a digit: -1
Sipho Dlamini, 34, M, ID: 9105225800087
Caught: ID number must only contain digits
Caught: ID number must have 13 digits
Sipho Dlamini, 34, M, ID: 9105225800087
```

## Common mistakes

- **No check of `front` for `-1`.** The code `return extractIntFromString(str, start, end - 1) * 10 + lastDigit;` gives wrong output when a non-digit is before the last character. The main test `"12a45"` has the letter in the middle. With this mistake, the line `Not a digit:` shows `-55` instead of `-1`.
- **A base case at an empty range.** Suppose the function recurses until `start` equals `end`. The range `if` at the top returns `-1` for that call. The `-1` then travels upward through the check of `front`, so every valid range gives `-1`. In `main.cpp`, the lines `Year:`, `Month:`, `Day:` and `Gender digits:` all show `-1`. The base case must be the range with one character.
- **A wrong digit test.** A test that rejects `'0'`, or that accepts `'/'` or `':'`, changes the output for `"000"`, `"12/4"` and `"12:4"` in the edge tests. The character `'/'` has the code before `'0'`, and `':'` has the code after `'9'`. Rejecting `'0'` makes the edge line `3. all zeros:` show `-1` instead of `0`. Accepting `'/'` makes line `11.` show `1194`, and accepting `':'` makes line `12.` show `1304`.
- **A loop or a helper function.** QUESTION.md states that either one scores 0.
- **Comparing `str.length()` with an `int` without a cast.** g++ reports `comparison of integer expressions of different signedness` (`-Werror=sign-compare`). The build fails, so the mark is 0.
