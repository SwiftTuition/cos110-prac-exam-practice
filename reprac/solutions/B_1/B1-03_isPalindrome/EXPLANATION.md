# B1-03 Explanation: recursive Binary::isPalindrome

## What the function must do

`isPalindrome(start, end)` checks the bits from `start` to `end`, both included. It returns `true` when they read the same in both directions. A range of one bit or no bits is a palindrome. If `start < 0` or `end >= size`, the input is invalid and the result is `false`. Loops and helper functions score 0.

## The idea

Compare the two outer bits. If they differ, the range is not a palindrome. If they are equal, the answer depends only on the range inside them: `start + 1` to `end - 1`. Each call removes two bits, so the range becomes empty or one bit long. That is the base case.

This is the "start, end" index-pair style of the recursive binary search in Lecture 2 (`search(arr, start, end, value)`).

## How the solution works

```cpp
bool Binary::isPalindrome(int start, int end) {
    if (start < 0 || end >= size) {
        return false;
    }
```

The invalid-input test comes first, as the question says.

- `start < 0`: an index before the array.
- `end >= size`: an index after the array. The last valid index is `size - 1`.
- For `isPalindrome(4, 3)` on a 3-bit string, `end >= size` is `3 >= 3`, so the input is invalid and the result must be `false`. If the base case `start >= end` (`4 >= 3`) came first, the function would return `true`. So the order matters for invalid input.
- The recursive calls only move inward (`start` up, `end` down), so once the first call passes this test, every later call passes it too.

```cpp
    if (start >= end) {
        return true;
    }
```

This is the base case. `start == end` means one bit is left, and one bit reads the same both ways. `start > end` means no bits are left. This happens for an even number of bits, for example `1001`: after (0, 3) and (1, 2), the next call is (2, 1). An empty string called with `(0, getSize() - 1)` is `(0, -1)`: `-1 >= 0` is false, so the input is valid, and `0 >= -1` is true, so the result is `true`.

```cpp
    if (array[start] != array[end]) {
        return false;
    }
    return isPalindrome(start + 1, end - 1);
```

- If the two outer bits differ, the range is not a palindrome. The function returns `false` at once and makes no more calls.
- Otherwise the function calls itself on the inner range. Both indexes move one step toward the middle, so the range gets shorter by 2 each time and the base case is always reached.
- The function never changes `array`.

## Trace

`main.cpp` calls `a.isPalindrome(0, 3)` with `a` = `1001`.

| Call | start | end | Invalid? | `start >= end`? | `array[start]`, `array[end]` | Result |
|---|---|---|---|---|---|---|
| 1 | 0 | 3 | no | no | 1, 1 (equal) | result of call 2 |
| 2 | 1 | 2 | no | no | 0, 0 (equal) | result of call 3 |
| 3 | 2 | 1 | no | yes: base case | not read | `true` |

`true` returns through calls 2 and 1, so the line prints `palindrome`.

`b.isPalindrome(0, 3)` with `b` = `1011`:

| Call | start | end | `array[start]`, `array[end]` | Result |
|---|---|---|---|---|
| 1 | 0 | 3 | 1, 1 (equal) | result of call 2 |
| 2 | 1 | 2 | 0, 1 (differ) | `false` |

The other calls in `main.cpp`:

- `c` = `10101` with (0, 4): `array[0]` and `array[4]` are both 1. The next call is (1, 3): `array[1]` and `array[3]` are both 0. The next call is (2, 2): one bit, so `true`.
- `b` with (0, 2) checks `101`: `array[0]` and `array[2]` are both 1. The next call is (1, 1): one bit, so `true`.
- `b` with (1, 2) checks `01`: `array[1]` is 0 and `array[2]` is 1. They differ, so `false`.
- `a` with (0, 4): `4 >= 4`, so the input is invalid: `false`. No bit is read.
- `a` with (-1, 2): `-1 < 0`, so `false`.

The output of `main.cpp` is:

```text
1001 [0, 3]: palindrome
1011 [0, 3]: not a palindrome
10101 [0, 4]: palindrome
1011 [0, 2]: palindrome
1011 [1, 2]: not a palindrome
1001 [0, 4]: not a palindrome
1001 [-1, 2]: not a palindrome
```

## Common mistakes

- **No range test.** `isPalindrome(0, 4)` on `1001` reads `array[4]`. valgrind reports `Invalid read of size 1`.
- **Moving only one index**, as in `isPalindrome(start + 1, end)`. The function then compares every bit with the last bit. `1001` gives `false`.
- **`start == end` as the only base case.** For an even number of bits, `start` and `end` pass each other and are never equal. The calls continue with `start > end`: `start` runs past the end of the array and `end` runs below 0. The range test does not stop this, because it only checks `start < 0` and `end >= size`. In `main.cpp`, `1001` prints `not a palindrome`, and valgrind reports `Invalid read of size 1`. Use `start >= end`.
- **Returning `true` as soon as one pair is equal.** The inner bits are never checked. `1011` then gives `true`.
- **A loop or a helper function.** Either one scores 0.
