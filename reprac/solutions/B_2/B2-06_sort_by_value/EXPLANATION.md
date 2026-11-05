# B2-06 Explanation: BinaryStrings::sort by decimal value

## What the function must do

`sort()` puts the strings in ascending order of decimal value, smallest at the head. `array[0]` is the most significant bit, so `0101` is 5 and `011` is 3. Equal values keep their original order (a stable sort). The function moves whole nodes by changing links. It creates no node, deletes no node, and does not copy strings between nodes. `size` does not change.

## Part 1: the helper

```cpp
static int decimalValue(const Binary& b) {
    int value = 0;
    for (int i = 0; i < b.getSize(); i++) {
        value = value * 2;
        if (b[i]) {
            value = value + 1;
        }
    }
    return value;
}
```

- The question allows a helper in `B_2.cpp`. `static` keeps the name inside this file, so it cannot clash with a name in another `.cpp` file.
- The loop reads from the left. Each new bit doubles the value so far and adds the bit. For `0101`: 0, 0, 1, 2, 5.
- `b` is a `const Binary&`, so `b[i]` uses the `const` `operator[]`, and `getSize()` is `const`. Both exist in the given class.
- An empty string never enters the loop, so its value is 0.

## Part 2: the sort (insertion sort by relinking)

The function builds a second chain, the **sorted part**. It takes the nodes of the old list one at a time and links each one into the right place in the sorted part.

```cpp
    Node<Binary>* sorted = NULL;
    Node<Binary>* curr = head;
    while (curr != NULL) {
        Node<Binary>* temp = curr->next();
        int value = decimalValue(curr->getData());
```

- `sorted` is the first node of the sorted part. It starts empty (`NULL`).
- `curr` is the node being moved. For an empty list the loop does not run.
- `temp` saves the rest of the old list. The code below changes `curr->next()`, and without `temp` the rest would be lost.
- `value` is `curr`'s value, worked out once.

```cpp
        if (sorted == NULL || value < decimalValue(sorted->getData())) {
            curr->next() = sorted;
            sorted = curr;
        } else {
```

Case 1: `curr` goes in front of the sorted part.

- `sorted == NULL`: the sorted part is empty, so `curr` becomes its only node.
- `value < ...`: `curr` is **strictly** smaller than the first sorted value. If it is equal, it must not go in front, because an equal value that came earlier must stay earlier.
- `||` stops at the first true test, so `sorted->getData()` is never read through `NULL`.
- `curr->next() = sorted;` then `sorted = curr;`. In the other order, the old sorted part would be lost.

```cpp
            Node<Binary>* prev = sorted;
            while (prev->next() != NULL && decimalValue(prev->next()->getData()) <= value) {
                prev = prev->next();
            }
            curr->next() = prev->next();
            prev->next() = curr;
        }
        curr = temp;
    }
    head = sorted;
```

Case 2: `curr` goes after some sorted node.

- `prev` starts at the first sorted node. Case 1 was false, so that node's value is `<=` `value`.
- `prev->next() != NULL`: stop at the last sorted node. Without it, the next test reads through `NULL`.
- `<= value`: move past every node with a smaller **or equal** value. So `curr` lands after the equal values that came before it. This `<=` and the strict `<` in case 1 make the sort stable.
- `curr->next() = prev->next();` and then `prev->next() = curr;` link `curr` in after `prev`. At the end of the sorted part, `prev->next()` is `NULL`, so `curr` gets a `NULL` link and becomes the last node.
- `curr = temp;` moves to the next node of the old list.
- After the loop, every node is in the sorted part. `head = sorted;` makes it the list.

## Trace

`main.cpp` starts with `0101 -> 11 -> 1000 -> 011 -> 0`. The values are 5, 3, 8, 3, 0.

| Iteration | curr (value) | Case | Walk of prev | Sorted part after |
|---|---|---|---|---|
| 1 | `0101` (5) | `sorted == NULL`: case 1 | - | `0101` |
| 2 | `11` (3) | `3 < 5`: case 1 | - | `11 -> 0101` |
| 3 | `1000` (8) | `8 < 3` false: case 2 | `11`, then `0101` (5 <= 8), then `next()` is `NULL` | `11 -> 0101 -> 1000` |
| 4 | `011` (3) | `3 < 3` false: case 2 | at `11`: next is `0101`, `5 <= 3` false, stop | `11 -> 011 -> 0101 -> 1000` |
| 5 | `0` (0) | `0 < 3`: case 1 | - | `0 -> 11 -> 011 -> 0101 -> 1000` |

Iteration 4 shows the tie rule: `011` has the same value as `11`. Case 1 needs a strict `<`, so `011` does not go in front. The walk stops after `11`, so `011` stays after `11`, as in the old order.

After iteration 5, `temp` was `NULL`, so the loop ends. `head = sorted` makes `0` the head. The empty list in `main.cpp` skips the loop, and `head` stays `NULL`.

The output of `main.cpp` is:

```text
0101 -> 11 -> 1000 -> 011 -> 0 (size 5)
0 -> 11 -> 011 -> 0101 -> 1000 (size 5)
Empty (size 0)
```

## Common mistakes

- **Not stable** (`<=` in case 1 and `<` in the walk). Equal values swap order. The second line of `main.cpp` then prints `0 -> 011 -> 11 -> 0101 -> 1000 (size 5)`.
- **Swapping the strings with `=`.** `Binary`'s `operator=` is private here, so `i->getData() = j->getData();` does not compile: g++ reports that `operator=` is private. The mark is 0. If a header does not declare `operator=` at all, the compiler makes one that copies the array **pointer**. Two strings then share one array, the destructors free it twice (`Invalid free()`), and one array leaks.
- **Forgetting `head = sorted;`.** `head` still points to `0101`, which now links to `1000` only. The list prints `0101 -> 1000`, and `0`, `11` and `011` are lost: valgrind reports `definitely lost`.
- **Skipping `temp`.** After `curr->next()` changes, `curr = curr->next();` follows the new link into the sorted part, so nodes are lost or visited twice.
- **No `prev->next() != NULL` test.** When `curr` is larger than every sorted value, the walk reads `decimalValue(NULL->getData())`: `SIGSEGV`, mark 0.
- **Sorting by size or by the number of 1 bits.** `1000` has fewer 1 bits than `011` but a larger value.
- **Creating new nodes for the sorted list.** The question says the same nodes must be used, and the marking program checks this. If the old nodes are not deleted, valgrind also reports a leak.
