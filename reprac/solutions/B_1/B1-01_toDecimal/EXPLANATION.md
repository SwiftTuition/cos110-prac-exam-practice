# B1-01 Explanation: recursive Binary::toDecimal

## What the function must do

`toDecimal(index)` returns the value of the bits from index 0 up to and including `index`, read as an unsigned binary number. `array[0]` is the leftmost bit and the most significant bit. For `1011`, `toDecimal(3)` is 11. An index below 0 or at `size` or above returns 0. Loops and helper functions score 0.

## The idea

Reading a binary number from the left, each new bit doubles the value so far and then adds the new bit. For `1011`: start at 0, then 0×2+1 = 1, 1×2+0 = 2, 2×2+1 = 5, 5×2+1 = 11.

So the value of the bits up to `index` is two times the value of the bits up to `index - 1`, plus the bit at `index`. That sentence is the recursive case. The recursion walks from `index` down to 0. One step further, `index` is -1, which means "no bits": the value is 0. That is the base case.

## How the solution works

```cpp
int Binary::toDecimal(int index) {
```

The function is a member of `Binary`, so it can use `array` and `size` directly. It allocates nothing and frees nothing.

```cpp
    if (index < 0 || index >= size) {
        return 0;
    }
```

This one test does two jobs.

- `index < 0` is the base case. Every recursive chain ends with a call on `index - 1 = -1`. No bits are left, so the value is 0. The same test also covers a negative argument from the caller, which the question says returns 0.
- `index >= size` is the invalid-input test. `array` has `size` elements, at indexes 0 to `size - 1`. Without this test, `toDecimal(4)` on a 4-bit string reads `array[4]`, which is outside the array.
- The operator `||` stops at the first true test. Both tests return the same value, so their order does not matter here.
- An empty string has `size` 0. The call `toDecimal(getSize() - 1)` is `toDecimal(-1)`, so it returns 0.

```cpp
    if (array[index]) {
        return 2 * toDecimal(index - 1) + 1;
    }
    return 2 * toDecimal(index - 1);
```

This is the recursive case.

- `array[index]` is a `bool`. The `if` asks: is this bit a 1?
- If it is, the result is twice the value of the bits before it, plus 1. If not, the result is twice that value, plus 0.
- `index - 1` moves one bit to the left. Each call is one step closer to -1, so the recursion ends.
- The function never changes `array`.

## Trace

`main.cpp` calls `a.toDecimal(3)` with `a` = `1011` (`array[0]` = 1, `array[1]` = 0, `array[2]` = 1, `array[3]` = 1).

| Call | index | Test `index < 0 \|\| index >= 4` | `array[index]` | Waits for | Returns |
|---|---|---|---|---|---|
| 1 | 3 | false | 1 | call 2 | 2 × 5 + 1 = 11 |
| 2 | 2 | false | 1 | call 3 | 2 × 2 + 1 = 5 |
| 3 | 1 | false | 0 | call 4 | 2 × 1 = 2 |
| 4 | 0 | false | 1 | call 5 | 2 × 0 + 1 = 1 |
| 5 | -1 | true (base case) | not read | nothing | 0 |

Calls 1 to 5 go down. The return values come back up: call 5 gives 0, call 4 gives 1, call 3 gives 2, call 2 gives 5, and call 1 gives 11.

The other calls in `main.cpp`:

- `a.toDecimal(1)` runs calls 3, 4 and 5 of the table and returns 2 (the bits `10`).
- `a.toDecimal(0)` returns 2 × 0 + 1 = 1.
- `b.toDecimal(b.getSize() - 1)` with `b` = `00000101` is `toDecimal(7)`. The five leading zeros keep the value at 0. Then 1, 2, 5. It returns 5.
- `a.toDecimal(4)`: `4 >= 4` is true, so it returns 0 at once. No bit is read.
- `a.toDecimal(-1)`: `-1 < 0` is true, so it returns 0.

The output of `main.cpp` is:

```text
1011 up to index 3: 11
1011 up to index 1: 2
1011 up to index 0: 1
00000101 whole string: 5
invalid index 4: 0
invalid index -1: 0
```

## Common mistakes

- **Only `index < 0` in the test.** The call `toDecimal(4)` on `1011` then reads `array[4]`. valgrind reports `Invalid read of size 1`, and the mark for memory is lost.
- **Forgetting the factor 2.** `return toDecimal(index - 1) + 1;` adds the bits instead of building the number. `1011` gives 3, not 11. The output is wrong.
- **Reading from the wrong end.** A version that starts at index 0 and calls `toDecimal(index + 1)` treats the last bit as the most significant bit. `00000101` read from index 0 gives 160, not 5. In `main.cpp`, `toDecimal(7)` then prints 1, and `1011` up to index 3 prints 1 instead of 11.
- **A base case of `index == 0` that returns `array[0]`.** This works for valid indexes, but `toDecimal(-1)` and an empty string then skip the base case and read `array[-1]`. Keep the `index < 0` test.
- **No base case at all.** g++ may warn `infinite recursion detected`. Under `-Werror` the build fails, and the mark is 0.
- **A loop, or a helper such as `power(2, n)`.** Either one scores 0. The doubling idea avoids any power function.
