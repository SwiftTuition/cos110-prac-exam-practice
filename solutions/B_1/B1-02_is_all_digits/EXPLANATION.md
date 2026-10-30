# B1-02 Explanation: recursive isAllDigits

## What the function must do

The function `Employee::isAllDigits(str, index)` checks the end part of a string. The function starts at position `index` and goes to the last character. The function returns `true` if every character in that part is a digit from `'0'` to `'9'`. The function returns `false` as soon as it finds a character that is not a digit.

Characters before `index` are not checked. If `index` is equal to the length of `str`, no characters are left, so the answer is `true`. If `index` is negative or larger than the length, the answer is `false`. The given `setIDNum` calls this function to check an ID number.

## How the solution works

The function checks one character, then asks itself about the rest of the string. The parameter `str` is a `string` passed by value, so the function works on its own copy. The function allocates no memory, so nothing is freed.

```cpp
if (index < 0 || index > (int)str.length()) {
    return false;
}
```

This `if` rejects an invalid `index`. `index < 0` protects against a negative position. `index > (int)str.length()` protects against a position past the end. The cast `(int)` is needed because `length()` is unsigned, and `-Wall -Werror` stops a comparison between an unsigned value and an `int`. The test uses `>`, not `>=`. The value `index == str.length()` is valid and means "nothing left to check".

```cpp
if (index == (int)str.length()) {
    return true;
}
```

This is the base case. When `index` equals the length, the function has checked every character and found no error, so the answer is `true`. The same line gives `true` for an empty string, because `isAllDigits("", 0)` has `index == 0 == length`. Without this base case, the function reads `str[index]` when `index` equals the length. In C++98 this is undefined behaviour. With g++ 13 the read gives the character `'\0'`, which is not a digit, so the function returns `false` for every string that reaches the end.

```cpp
if (str[index] < '0' || str[index] > '9') {
    return false;
}
```

This `if` tests the current character. The character is not a digit when its code is less than the code of `'0'` or more than the code of `'9'`. The function returns `false` at once and makes no further call. This line runs only after the two earlier checks, so `index` is a valid position.

```cpp
return isAllDigits(str, index + 1);
```

This is the recursive case. The current character is a digit, so the answer depends on the rest of the string. The call uses `index + 1`, which moves one position closer to the base case `index == str.length()`. The function returns the value of this call without a change. No statement runs after the call, so the order of statements does not change the result.

## Trace

The call is `isAllDigits("abc123", 3)`. The string has 6 characters, and the characters from index 3 are `1`, `2`, `3`.

| Call | index | Branch taken | Result |
|---|---|---|---|
| 1 | 3 | `str[3]` is `'1'`, a digit, so the recursive case runs | waits for call 2 |
| 2 | 4 | `str[4]` is `'2'`, a digit, so the recursive case runs | waits for call 3 |
| 3 | 5 | `str[5]` is `'3'`, a digit, so the recursive case runs | waits for call 4 |
| 4 | 6 | `index == (int)str.length()`, base case | returns `true` |

The calls return in the order 4, 3, 2, 1. Each call returns the `true` that it receives, so the final answer is `true`.

The call `isAllDigits("abc123", 0)` stops at once. At index 0 the character is `'a'`. The character is not a digit, so call 1 returns `false` and makes no recursive call.

The output of `main.cpp` is:

```text
9702140123081 from 0: true
97021401230X1 from 0: false
abc123 from 3: true
abc123 from 0: false
Caught: ID number must only contain digits
Thandi Mokoena, 29, F, ID: 9702140123081
```

## Common mistakes

- **Using `>=` in the first `if`.** Then `index == str.length()` returns `false`. Every recursion that reaches the end of the string returns `false`. So `isAllDigits("9702140123081", 0)` is `false`, and the edge tests for `""` and for `"123"` from index `3` fail.
- **No base case for `index == (int)str.length()`.** The function then reads `str[index]` when `index` equals the length. In C++98 this is undefined behaviour, so the result cannot be trusted. With g++ 13 the read gave `'\0'`, which is not a digit, so every string of digits gave `false`, the same output as the `>=` mistake. In `main.cpp`, `setIDNum("9702140123081")` then throws an exception that nothing catches, and the program stops with `terminate called after throwing an instance of 'Exception'`.
- **Calling the function without `return`.** The line `isAllDigits(str, index + 1);` computes the answer and discards it. The compiler warns that control reaches the end of a non-void function. Under `-Wall -Werror` this stops the build, and the mark is 0.
- **Checking characters before `index`.** The edge test `isAllDigits("12x45", 3)` expects `true`, because the `'x'` is at index 2. A function that starts at index 0 returns `false`.
- **A loop or a helper function.** QUESTION.md states that either one scores 0.
