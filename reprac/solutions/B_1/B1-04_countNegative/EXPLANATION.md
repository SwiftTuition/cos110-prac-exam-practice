# B1-04 Explanation: recursive BinaryStrings::countNegative

## What the function must do

`countNegative(curr)` counts the strings from node `curr` to the end of the list whose bit 0 is 1. An empty string has no bit 0, so it does not count. `NULL` gives 0. Loops and helper functions score 0.

## How the solution works

The parameter is the node to look at. Each call handles one node and passes the next node to the next call.

```cpp
int BinaryStrings::countNegative(Node<Binary>* curr) {
    if (curr == NULL) {
        return 0;
    }
```

This is the base case. After the last node, `next()` is `NULL`. There are no strings left, so the count is 0. The same test covers an empty list, where `getHead()` is `NULL`. Without it, the next line would call `getData()` through `NULL` and the program would crash.

```cpp
    if (curr->getData().getSize() > 0 && curr->getData()[0]) {
        return 1 + countNegative(curr->next());
    }
    return countNegative(curr->next());
```

- `curr->getData()` is the `Binary` in this node. `getData()` returns a reference (`T&`), so no copy is made.
- `getSize() > 0` asks: does the string have at least one bit? For an empty string the array has 0 elements, so `[0]` would read outside it.
- `curr->getData()[0]` calls `Binary::operator[]` and gives bit 0, the sign bit.
- The operator `&&` stops at the first false test. For an empty string, `getSize() > 0` is false, so bit 0 is never read. The order of the two tests matters.
- If both tests are true, this string is negative: 1 plus the count for the rest of the list.
- Otherwise: the count for the rest of the list.
- `curr->next()` moves one node forward, toward `NULL`, so the recursion ends.
- The function changes no pointer and no bit. It allocates nothing.

## Trace

In `main.cpp`, the list is `100 -> 0011 -> 1101 -> 0101`. The call is `countNegative(list.getHead())`.

| Call | curr | size > 0? | bit 0 | Returns |
|---|---|---|---|---|
| 1 | `100` | yes | 1 | 1 + call 2 = 1 + 1 = 2 |
| 2 | `0011` | yes | 0 | call 3 = 1 |
| 3 | `1101` | yes | 1 | 1 + call 4 = 1 + 0 = 1 |
| 4 | `0101` | yes | 0 | call 5 = 0 |
| 5 | `NULL` | base case | - | 0 |

The values return from call 5 up: 0, 0, 1, 1, 2.

- The first line of `main.cpp` uses the empty list: `getHead()` is `NULL`, so the base case returns 0 at once.
- `countNegative(third)` starts at `1101`. It runs calls 3, 4 and 5 and returns 1.

The output of `main.cpp` is:

```text
Empty: 0 negative
100 -> 0011 -> 1101 -> 0101: 2 negative
from 1101: 1 negative
```

## Common mistakes

- **No size test.** `curr->getData()[0]` on an empty string reads the first element of an array of size 0. `main.cpp` does not show this mistake, because its list has no empty string. A list made from `Binary("100")`, `Binary("")` and `Binary("0101")` does: the line still prints `1 negative`, but valgrind reports `Invalid read of size 1`.
- **The tests in the wrong order** (`curr->getData()[0] && curr->getData().getSize() > 0`). Bit 0 is read before the size is checked, which is the same invalid read.
- **Returning 1 at the first negative string**, without the recursive call. The count stops early. In `main.cpp`, the second line then prints `1 negative` instead of `2 negative`.
- **No `NULL` test.** The empty list in `main.cpp` calls `getData()` through `NULL`. valgrind reports `Invalid read`, the program stops with a segmentation fault (`SIGSEGV`), and the mark is 0.
- **Copying the Binary**, as in `Binary b = curr->getData();`. This compiles (it uses the copy constructor) and frees its copy at the end of the call, so it gives the correct count. It makes a new array in every call, which is not needed. `Binary& b = curr->getData();` makes no copy.
- **A loop or a helper function.** Either one scores 0.
