# A1-04 Explanation: Employee::extractIntFromString

## What the function must do

The function `extractIntFromString` reads a part of a string and returns the number that the digits make. The part starts at index `start` and stops before index `end`. If the range is not valid, the function throws `Exception("Invalid range")`. If a character in the range is not a digit, the function throws `Exception("Not a digit")`. The function is `static`, so a caller can write `Employee::extractIntFromString(...)` without an `Employee` object.

## How the solution works

```cpp
int Employee::extractIntFromString(string str, int start, int end) {
```

The word `static` appears only in the class declaration in `Employee.h`. The definition in `A_1.cpp` does not repeat it.

**Step 1: check the range.**

```cpp
    if (start < 0 || start >= end || end > (int)str.length()) {
        throw Exception("Invalid range");
    }
```

The three conditions are joined with `||`. The whole condition is true if at least one part is true.

- `start < 0` protects against a negative index. The call `str[-1]` reads memory outside the string.
- `start >= end` protects against an empty range or a reversed range, such as 3 to 1 or 2 to 2. The question requires `Invalid range` for these.
- `end > (int)str.length()` protects against a range that goes past the last character. The valid values of `end` are up to and including the length, because `end` itself is not read. The function `length()` returns an unsigned number. The cast `(int)` avoids a signed/unsigned comparison warning, which `-Wall -Werror` turns into an error.

This check comes before the loop. The loop reads `str[i]`. Without the check, the loop could read characters that do not exist. The check also decides which message the function gives. The input `"abc"` with range 0 to 5 gives `Invalid range` and not `Not a digit`.

**Step 2: build the number.**

```cpp
    int result = 0;
    for (int i = start; i < end; i++) {
```

The variable `result` starts at 0. The loop visits index `start` up to `end - 1`. The condition `i < end` excludes `end`, as the question requires.

**Step 3: check each character.**

```cpp
        if (str[i] < '0' || str[i] > '9') {
            throw Exception("Not a digit");
        }
```

The characters `'0'` to `'9'` have consecutive codes. A character below `'0'` or above `'9'` is not a digit. This includes letters, a space and `'-'`. The function checks only the characters in the range, so characters outside the range have no effect. The `throw` leaves the loop and the function at once.

**Step 4: add the digit.**

```cpp
        result = result * 10 + (str[i] - '0');
```

The expression `str[i] - '0'` gives the value of the digit. For example, `'7' - '0'` is 7. Multiplying `result` by 10 moves the earlier digits one place to the left. Leading zeros add nothing, so `"0042"` from index 1 to 4 gives 42.

```cpp
    return result;
```

The function returns the number. A range has at most 9 digits, so the value fits in an `int`.

The function allocates no memory, so nothing needs to be freed.

## Trace

The call is `tryExtract("12a4", 0, 4)`.

| Step | Code | Values | Result |
|---|---|---|---|
| 1 | range check | `start` 0, `end` 4, length 4 | 0 < 0 false, 0 >= 4 false, 4 > 4 false, continue |
| 2 | `result = 0` | | `result` is 0 |
| 3 | `i = 0` | `'1'` is a digit | `result = 0 * 10 + 1`, so 1 |
| 4 | `i = 1` | `'2'` is a digit | `result = 1 * 10 + 2`, so 12 |
| 5 | `i = 2` | `'a'` is greater than `'9'` | throw `Exception("Not a digit")` |

The function never reaches `i = 3` and never returns. The `catch (Exception& e)` in `tryExtract` prints the message.

A successful call is `tryExtract("9702140123081", 6, 10)`. The characters at index 6 to 9 are `0`, `1`, `2`, `3`. The values of `result` are 0, 1, 12, 123. The function returns 123.

The call `tryExtract("1234", 2, 2)` fails at step 1, because `start >= end` is true.

The output of `main.cpp` is:

```text
"9702140123081" [0, 2) = 97
"9702140123081" [2, 4) = 2
"9702140123081" [6, 10) = 123
"12a4" [0, 4): Not a digit
"1234" [2, 2): Invalid range
Thandi Mokoena, 29, F, ID: 9702140123081
Sipho Dlamini, 35, M, ID: 9105225800087
```

## Common mistakes

- **Treat `end` as included.** If the loop uses `i <= end`, the function reads one more character. The call from 0 to 2 would give a number with three digits. The main test rejected this change because its output differed.
- **Return 0 for an empty range.** If the range check allows `start == end`, the call `tryExtract("1234", 2, 2)` prints a value and not `Invalid range`. The main test rejected this change.
- **Compare an `int` with `str.length()` without a cast.** The comparison of a signed number with an unsigned number gives a warning. Under `-Wall -Werror` the warning is an error, and the program does not compile. The mark is 0.
- **Check the digits before the range.** For `"abc"` with range 0 to 5, the loop meets the letter `'a'` first and throws `Not a digit`. The question requires `Invalid range`. For `"1234"` with range 0 to 5, the loop reads `str[4]`, which is after the last character. In C++98 this read is undefined behaviour. With g++ the read gives the end character `'\0'`, so the function throws `Not a digit` and not `Invalid range`. The edge test rejected this change because its output differed.
- **Write `static` again in `A_1.cpp`.** The compiler reports an error, because `static` is allowed only inside the class declaration.
