# B1-09 Explanation: recursive checksum (Luhn sum)

## What the function must do

The function `Employee::checksum(id, index)` returns the Luhn sum of the digits of `id`, from position `index` to the end. The Luhn rule treats each digit by its distance from the end of the whole string. A digit is doubled when the number of characters after it is odd. If the doubled value is more than 9, the function subtracts 9. All other digits keep their value.

The call `checksum(id, 0)` gives the sum for the whole ID number. An ID number is valid when this sum is a multiple of 10. If `index` equals the length of `id`, no digits are left, so the answer is `0`. If `index` is negative or larger than the length, the answer is also `0`. The function may assume that `id` holds only digits.

## How the solution works

The function handles one digit, then asks itself about the digits after it. The parameter `id` is a `string` passed by value, so the function works on its own copy. The function allocates no memory and frees none.

```cpp
if (index < 0 || index >= (int)id.length()) {
    return 0;
}
```

This is the base case. `index < 0` protects against a negative position. `index >= (int)id.length()` covers the position after the last digit, where no digits are left, and any larger invalid position. Both give `0`. The cast `(int)` is needed because `length()` is unsigned, and `-Wall -Werror` stops a comparison between an unsigned value and an `int`. Without this base case, every call would make another call, so the recursion could never end. g++ 13 sees this and reports `infinite recursion detected`. Under `-Wall -Werror` the build fails.

```cpp
int digit = id[index] - '0';
```

The expression `id[index]` is a character. The codes of `'0'` to `'9'` are next to each other, so subtracting `'0'` turns a digit character into its number. For example, `'7' - '0'` is `7`.

```cpp
if (((int)id.length() - 1 - index) % 2 == 1) {
    digit = digit * 2;
    if (digit > 9) {
        digit = digit - 9;
    }
}
```

The value `(int)id.length() - 1 - index` is the number of characters after the current digit, counted to the end of the whole string. The base case guarantees that `index` is less than the length, so this number is never negative. The operator `%` gives the remainder after division, so `% 2 == 1` is true when the number is odd. In that case the function doubles the digit. The inner `if` applies the "more than 9" rule: a doubled value such as `14` becomes `14 - 9 = 5`. A digit in an even position keeps its value. The count must use the length of the whole string, not the part that remains, so the recursive calls give the same answer as the first call.

```cpp
return digit + checksum(id, index + 1);
```

This is the recursive case. The call `checksum(id, index + 1)` returns the sum for the digits after the current one. Each call raises `index` by 1, so the calls move toward `index == id.length()`, which is the base case. The addition runs after the recursive call returns. The function returns the sum itself. The caller applies `% 10` to test the sum.

## Trace

The call is `checksum("9702140123086", 6)` from `main.cpp`. The string has 13 characters, so the number of characters after index `i` is `12 - i`.

| Call | index | Digit | Characters after | Rule | Value of `digit` |
|---|---|---|---|---|---|
| 1 | 6 | 0 | 6, even | keep | 0 |
| 2 | 7 | 1 | 5, odd | double: 2 | 2 |
| 3 | 8 | 2 | 4, even | keep | 2 |
| 4 | 9 | 3 | 3, odd | double: 6 | 6 |
| 5 | 10 | 0 | 2, even | keep | 0 |
| 6 | 11 | 8 | 1, odd | double: 16, then 16 - 9 | 7 |
| 7 | 12 | 6 | 0, even | keep | 6 |
| 8 | 13 | none | not tested | base case, `13 >= 13` | returns `0` |

The calls return in the order 8, 7, 6, 5, 4, 3, 2, 1:

- Call 7 returns `6 + 0 = 6`.
- Call 6 returns `7 + 6 = 13`.
- Call 5 returns `0 + 13 = 13`.
- Call 4 returns `6 + 13 = 19`.
- Call 3 returns `2 + 19 = 21`.
- Call 2 returns `2 + 21 = 23`.
- Call 1 returns `0 + 23 = 23`.

The output of `main.cpp` is:

```text
Luhn sum of 9702140123086: 50
Valid: yes
Luhn sum of 9702140123081: 45
Valid: no
Sum from index 6 of 9702140123086: 23
Caught: ID number has a wrong check digit
Thandi Mokoena, 29, F, ID: 9702140123086
```

## Common mistakes

- **Counting the doubling position from the front.** A test such as `index % 2 == 0` gives the wrong digits to double when the string has an odd length. The edge test `"12345"` expects `21`, but this version gives `15`. The rule must use the number of characters after the digit.
- **Counting from `index` instead of from the end of `id`.** QUESTION.md states that `checksum("7918", 2)` is `10`, because the `1` is still doubled. A function that restarts the count at each call gives a different sum.
- **Leaving out the subtraction of 9.** For `"59"`, the digit `5` doubles to `10`. The correct value is `1`, so the sum is `10`. Without the subtraction, the sum is `19`. For `"99"`, the correct sum is `18`, and without the subtraction it is `27`. Both are edge tests.
- **Returning the sum modulo 10.** The function must return the sum. The call `checksum("79927398713", 0)` must return `70`, not `0`.
- **Using `index > (int)id.length()` in the base case.** When `index` equals the length, the function reads `id[index]` past the last character. In C++98 this is undefined behaviour, so the result cannot be trusted. With g++ 13 the read gave `'\0'`, so `digit` was `0 - 48 = -48`, and every sum was wrong. For example, the edge line `4. index equal to the length:` showed `-48` instead of `0`.
- **A loop or a helper function.** QUESTION.md states that either one scores 0.
