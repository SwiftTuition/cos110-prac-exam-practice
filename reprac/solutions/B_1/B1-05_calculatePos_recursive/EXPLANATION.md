# B1-05 Explanation: recursive BinaryStrings::calculatePos(curr, index)

## What the function must do

`calculatePos(curr, index)` counts the positive strings from node `curr` to the end of the list. A string is positive when bit 0 is 0 and at least one other bit is 1. `index` is the bit of `curr` that this call checks. The first call is `calculatePos(getHead(), 1)`. `NULL` gives 0, and an `index` below 1 gives 0. Loops and helper functions score 0.

## Why there are two parameters

A solution with loops needs two loops: one over the nodes and one over the bits of each string. With no loops, both walks become recursive calls of the same function:

- `calculatePos(curr, index + 1)` moves to the next **bit** of the same string.
- `calculatePos(curr->next(), 1)` moves to the next **node** and starts again at bit 1.

The same shape works for a grid. One call moves along a row, and another call jumps to the start of the next row. Here each node is like a row, and each bit is like a column.

## How the solution works

```cpp
int BinaryStrings::calculatePos(Node<Binary>* curr, int index) {
    if (curr == NULL) {
        return 0;
    }
```

Base case: no node is left, so no string is left to count. This also covers an empty list.

```cpp
    if (index < 1) {
        return 0;
    }
```

Invalid input. Bit 0 is the sign bit, so the search for a 1 starts at bit 1 or later. The recursive calls always pass 1 or more, so only a wrong first call can reach this line.

```cpp
    if (index >= curr->getData().getSize() || curr->getData()[0]) {
        return calculatePos(curr->next(), 1);
    }
```

This test finds a string that is **not** positive. The function then skips the string and moves to the next node at bit 1.

- `index >= curr->getData().getSize()`: the search has passed the last bit of the string without finding a 1. So the string is zero (`000`) or too short to hold a 1 after the sign bit (`0`, `1`, or an empty string).
- `curr->getData()[0]`: the sign bit is 1, so the string is negative.
- The operator `||` stops at the first true test. For an empty string, `index >= 0` is true, so bit 0 of an empty string is never read. The order of the two tests matters.

```cpp
    if (curr->getData()[index]) {
        return 1 + calculatePos(curr->next(), 1);
    }
```

The sign bit is 0 (the test above was false), and bit `index` is 1. So this string is positive. Count it once with `1 +`, then move to the next node at bit 1. The function does not look at the rest of this string, so a string with many 1 bits is still counted once.

```cpp
    return calculatePos(curr, index + 1);
}
```

Bit `index` is 0. The function checks the next bit of the **same** node. `index + 1` moves toward the size of the string, so this inner walk always ends at the test `index >= size`.

The function changes no pointer and no bit, and it allocates nothing.

## Trace

In `main.cpp`, the list is `000 -> 0011 -> 1101 -> 0101`. The call is `calculatePos(list.getHead(), 1)`.

In calls 1 to 7, `curr == NULL` is false and `index < 1` is false. The table shows the other three tests. "Not read" means that an earlier test was true, so the call returned before this test.

| Call | curr | index | `index >= size`? | Bit 0 is 1? | Bit `index` is 1? | Next call | Adds |
|---|---|---|---|---|---|---|---|
| 1 | `000` | 1 | `1 >= 3`: false | false | false (bit 1 is 0) | (`000`, 2) | 0 |
| 2 | `000` | 2 | `2 >= 3`: false | false | false (bit 2 is 0) | (`000`, 3) | 0 |
| 3 | `000` | 3 | `3 >= 3`: true, no 1 found, not positive | not read | not read | (`0011`, 1) | 0 |
| 4 | `0011` | 1 | `1 >= 4`: false | false | false (bit 1 is 0) | (`0011`, 2) | 0 |
| 5 | `0011` | 2 | `2 >= 4`: false | false | true (bit 2 is 1): positive | (`1101`, 1) | 1 |
| 6 | `1101` | 1 | `1 >= 4`: false | true: negative | not read | (`0101`, 1) | 0 |
| 7 | `0101` | 1 | `1 >= 4`: false | false | true (bit 1 is 1): positive | (`NULL`, 1) | 1 |
| 8 | `NULL` | 1 | not read (`curr == NULL` is true: base case) | not read | not read | none | returns 0 |

The return values come back up: call 8 gives 0, call 7 gives 1, call 6 gives 1, call 5 gives 2, and calls 4 to 1 pass the 2 up unchanged. The result is 2.

The other calls in `main.cpp`:

- The empty list: `getHead()` is `NULL`, so the result is 0.
- `calculatePos(third, 1)` starts at `1101`. It runs calls 6, 7 and 8 and returns 1.
- `calculatePos(getHead(), 0)`: `0 < 1`, so the result is 0. No node is visited.

The output of `main.cpp` is:

```text
Empty: 0 positive
000 -> 0011 -> 1101 -> 0101: 2 positive
from 1101: 1 positive
invalid index 0: 0
```

## Common mistakes

- **Reading the sign bit before the size test** (`curr->getData()[0] || index >= ...`). For an empty string this reads element 0 of an array of size 0. `main.cpp` does not show this mistake, because its list has no empty string. A list made from `Binary("0011")`, `Binary("")` and `Binary("01")` does: the line still prints `2 positive`, but valgrind reports `Invalid read of size 1`.
- **Keeping the old index when moving to the next node**, as in `calculatePos(curr->next(), index)`. The next string is then checked from the wrong bit. `main.cpp` does not show this mistake. The list `0000000001 -> 01` does: it gives 1 instead of 2. The search in `0000000001` ends at index 9, and `01` is then checked from bit 9, which is past its end.
- **Counting every 1 bit**, as in `return 1 + calculatePos(curr, index + 1);`. The string `0111` then counts 3 times.
- **Counting zero as positive.** If the function counts a string as soon as bit 0 is 0, `000` counts. In `main.cpp`, the second line then prints `3 positive` instead of `2 positive`.
- **Calling `calculatePos(curr, index)` with the same arguments.** Nothing changes between calls, so the recursion never ends. The program stops with a stack overflow, and the mark is 0.
- **A loop or a helper function.** Either one scores 0. A loop over the bits inside a recursive walk over the nodes is still a loop.

## Note on the name

The exam paper does not explain `calculatePos(): int`. In this question "Pos" means "positive", with bit 0 as a sign bit (0 means not negative, 1 means negative). In the exam, read the question text: "Pos" may mean something else, such as a position. The two-parameter recursion pattern stays the same for any rule that needs a walk over nodes and over bits.

If the exam keeps `calculatePos(): int` with no parameters and its text allows a helper, put this same body in a helper such as `int calculatePos(Node<Binary>* curr, int index)` and call it once: `return calculatePos(head, 1);`. The exam question text decides whether helpers are allowed.
