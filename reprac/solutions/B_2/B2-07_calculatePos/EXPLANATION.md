# B2-07 Explanation: BinaryStrings::calculatePos

## What the function must do

`calculatePos()` returns the number of positive binary strings in the list. Bit 0 is a sign bit. A string is positive when bit 0 is 0 and at least one other bit is 1. Zero (`000`), negative strings (`1101`), one-bit strings and the empty string are not positive. Each positive string counts once.

The exam paper does not explain "Pos". In this question it means "positive". In the exam, the question text decides; the loop shape below (a walk over the nodes with a walk over the bits inside) also works for other rules that look at the bits of each string.

## How the solution works

```cpp
int BinaryStrings::calculatePos() {
    int count = 0;
    Node<Binary>* curr = head;
    while (curr != NULL) {
```

The outer loop is the standard traversal from Lecture 21: start at `head`, stop when the traversal pointer is `NULL`. `head` itself is never moved. For an empty list the loop does not run, and the result is 0.

```cpp
        Binary& b = curr->getData();
```

`b` is a reference to the string in the node. `getData()` returns `T&`, so no copy is made, and no extra array is created.

```cpp
        if (b.getSize() > 0 && b[0] == false) {
```

- `b.getSize() > 0`: the string has at least one bit. An empty string has an array of size 0, so `b[0]` would read outside it.
- `b[0] == false`: the sign bit is 0. A string with sign bit 1 is negative and is skipped.
- `&&` stops at the first false test. For an empty string, `b[0]` is never read. The order of the two tests matters.

```cpp
            for (int i = 1; i < b.getSize(); i++) {
                if (b[i]) {
                    count++;
                    break;
                }
            }
        }
```

- The inner loop starts at bit 1, because bit 0 is the sign bit and is already known to be 0.
- `i < b.getSize()` keeps `i` inside the string. For a one-bit string (`0`), the loop does not run, so `0` is not counted.
- At the first 1 bit, the string is positive: `count++`, then `break` leaves the inner loop. Without `break`, a string such as `0111` would be counted once per 1 bit.
- If the loop ends without a 1 bit, the string is zero (`000`), and `count` does not change.

```cpp
        curr = curr->next();
    }
    return count;
}
```

`curr` moves to the next node. After the last node it is `NULL`, and the loop ends.

## Trace

`main.cpp` builds `000 -> 0011 -> 1101 -> 0101`.

| curr | size > 0 | bit 0 | Inner loop | count after |
|---|---|---|---|---|
| `000` | yes | 0 | bits 1, 2 are 0; loop ends | 0 |
| `0011` | yes | 0 | bit 1 is 0; bit 2 is 1: count, break | 1 |
| `1101` | yes | 1 | skipped | 1 |
| `0101` | yes | 0 | bit 1 is 1: count, break | 2 |

The result is 2.

Then `main.cpp` sets bit 2 of the head to 1, so `000` becomes `001`. Its inner loop finds the 1 at bit 2, and the count is 3. Last, it sets bit 0 of the third node to 0, so `1101` becomes `0101`, which is positive. The count is 4.

The output of `main.cpp` is:

```text
Empty: 0 positive
000 -> 0011 -> 1101 -> 0101: 2 positive
001 -> 0011 -> 1101 -> 0101: 3 positive
001 -> 0011 -> 0101 -> 0101: 4 positive
```

## Common mistakes

- **No size test.** `b[0]` on an empty string reads outside its array. `main.cpp` does not show this mistake, because its list has no empty string. A list made from `Binary("0011")`, `Binary("")` and `Binary("01")` does: the line still prints `2 positive`, but valgrind reports `Invalid read of size 1`.
- **No `break`.** A string with several 1 bits counts once per 1 bit. `0011` and `0101` each have two 1 bits after the sign bit, so the first line with strings prints `4 positive` instead of `2 positive`.
- **Counting every string with sign bit 0.** Zero (`000`) is then counted. In `main.cpp`, the second line then prints `3 positive` instead of `2 positive`.
- **Starting the inner loop at 0.** Bit 0 is already known to be 0, so this does not change the result here, but in a rule where bit 0 is not the sign bit it would. Start at 1 to match the definition.
- **Copying each string** with `Binary b = curr->getData();`. This compiles and does not leak (the copy is freed at the end of each pass), but it makes a new array for every node. A reference avoids it.
- **Moving `head` to walk the list.** After the call the list is lost. Lecture 21 warns about this.
