# B1-02 Explanation: recursive Binary::countOnes

## What the function must do

`countOnes(index)` returns the number of `true` bits from `index` to the end of the array. An index at the end or past it returns 0. A negative index is invalid and returns 0. Loops and helper functions score 0.

## How the solution works

```cpp
int Binary::countOnes(int index) {
```

The function is a member of `Binary`, so it uses `array` and `size` directly. The index moves forward by 1 in each call.

```cpp
    if (index < 0 || index >= size) {
        return 0;
    }
```

- `index >= size` is the base case. The valid indexes are 0 to `size - 1`. When `index` reaches `size`, no bits are left, so the count is 0. The same test covers a caller who passes an index far past the end, such as 50.
- `index < 0` is the invalid-input test from the question. Without it, `countOnes(-1)` reads `array[-1]`, which is before the start of the array.
- An empty string has `size` 0, so any call returns 0 at once.

```cpp
    if (array[index]) {
        return 1 + countOnes(index + 1);
    }
    return countOnes(index + 1);
```

This is the recursive case.

- If the bit at `index` is 1, the answer is 1 plus the number of 1 bits after it.
- If the bit is 0, the answer is the number of 1 bits after it.
- `index + 1` moves one bit to the right, toward `size`, so the recursion ends.

## Trace

`main.cpp` calls `a.countOnes(0)` with `a` = `10110` (size 5).

| Call | index | Base or invalid? | `array[index]` | Returns |
|---|---|---|---|---|
| 1 | 0 | no | 1 | 1 + call 2 = 1 + 2 = 3 |
| 2 | 1 | no | 0 | call 3 = 2 |
| 3 | 2 | no | 1 | 1 + call 4 = 1 + 1 = 2 |
| 4 | 3 | no | 1 | 1 + call 5 = 1 + 0 = 1 |
| 5 | 4 | no | 0 | call 6 = 0 |
| 6 | 5 | `5 >= 5`: base case | not read | 0 |

The values return from call 6 up to call 1: 0, 0, 1, 2, 2, 3.

The other calls in `main.cpp`:

- `countOnes(2)` starts at call 3 of the table and returns 2.
- `countOnes(4)` starts at call 5 and returns 0 (the last bit is 0).
- `countOnes(5)` is the base case at once and returns 0.
- `countOnes(-1)`: `-1 < 0` is true, so it returns 0 without reading the array.

The output of `main.cpp` is:

```text
10110 from index 0: 3
10110 from index 2: 2
10110 from index 4: 0
10110 from index 5: 0
10110 from index -1: 0
```

## Common mistakes

- **No `index < 0` test.** `countOnes(-1)` reads `array[-1]`, and then `array[0]` onwards. valgrind reports `Invalid read of size 1` in `main.cpp`.
- **`index > size` instead of `index >= size`.** The call with `index == size` reads `array[size]`, one element past the end. valgrind reports an invalid read.
- **The `1 +` on the wrong branch.** The function then counts the 0 bits. For `10110` it returns 2 instead of 3.
- **Calling `countOnes(index)` instead of `countOnes(index + 1)`.** The argument never changes, so the recursion never ends. The program stops with a stack overflow (valgrind shows `Stack overflow`), and the mark is 0.
- **A loop or a helper function.** Either one scores 0.
