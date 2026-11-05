# B2-04 Explanation: BinaryStrings::remove (first equal string)

## What the function must do

`remove(b)` finds the first node whose string equals `b`, unlinks it, deletes it, subtracts 1 from `size` and returns `true`. If no string is equal, it returns `false` and changes nothing. `Binary` has no `operator==`, so the function compares the strings itself: equal means the same size and the same bit at every index. This follows the combined `remove(val)` flowchart of Lecture 23, with a bit-by-bit comparison in place of `==`.

## How the solution works

```cpp
bool BinaryStrings::remove(const Binary& b) {
    Node<Binary>* prev = NULL;
    Node<Binary>* curr = head;
```

Two pointers walk the list together. `curr` is the node being checked. `prev` is the node before it, or `NULL` while `curr` is the head. Lecture 23 uses two pointers "such that it is possible to relink the rest of the list correctly".

```cpp
    while (curr != NULL) {
        Binary& data = curr->getData();
        bool same = (data.getSize() == b.getSize());
```

- The loop runs once for each node and ends after the last one. For an empty list it does not run, and the function returns `false`.
- `data` is a reference to the string in the node. No copy is made.
- `same` starts as the size test. Strings of different sizes are never equal, so `011` and `11` are different even though both have the value 3.

```cpp
        for (int i = 0; same && i < b.getSize(); i++) {
            if (data[i] != b[i]) {
                same = false;
            }
        }
```

- The inner loop runs only while `same` is true. If the sizes differ, `same` is already false and the loop does not run at all. This is what stops the loop from reading a bit past the end of the shorter string.
- The loop stops at the first bit that differs, because `same` becomes false.
- `b` is a `const Binary&`, so `b[i]` uses the `const` version of `operator[]`. `data[i]` uses the normal version.
- For two empty strings, the sizes match (0 and 0), the loop does not run, and `same` stays true.

```cpp
        if (same) {
            if (prev == NULL) {
                head = curr->next();
            } else {
                prev->next() = curr->next();
            }
            delete curr;
            size--;
            return true;
        }
```

- `prev == NULL` means `curr` is the head. The head moves to the second node.
- Otherwise `prev` skips `curr` and links to the node after it. If `curr` was the last node, `prev` gets a `NULL` link.
- `delete curr;` frees the node, and the node's `Binary` destructor frees its bool array.
- `return true;` stops at the first match, so later equal strings stay.

```cpp
        prev = curr;
        curr = curr->next();
    }
    return false;
}
```

No match at this node: both pointers move one node forward. If the loop ends, no string matched.

## Trace

`main.cpp` starts with `0101 -> 0011 -> 101 -> 0011` (size 4). The first call is `remove("0011")`.

| Step | prev | curr | Size test | Bit test | Result |
|---|---|---|---|---|---|
| 1 | `NULL` | `0101` | 4 == 4 | i = 0: 0 and 0, same; i = 1: `0101` has 1, `0011` has 0, differ, so `same` = false and the loop stops | move on |
| 2 | `0101` | `0011` | 4 == 4 | i = 0: 0 and 0; i = 1: 0 and 0; i = 2: 1 and 1; i = 3: 1 and 1; `same` stays true; i = 4: `4 < 4` is false, so the loop ends | match |

`prev` is `0101`, so `0101` is linked to `101`. The first `0011` is deleted. The list is `0101 -> 101 -> 0011`, size 3, and the second `0011` stays.

`remove("11")`: the list holds sizes 4, 3 and 4, and `11` has size 2. So `same` is false at once for every node. The bit loop never runs. The result is `false`.

`remove("101")`: `0101` has size 4 (no), then `101` matches. The list is `0101 -> 0011`.

`remove("0101")`: the head matches. `prev` is `NULL`, so `head` moves to `0011`.

`remove("0011")`: the only node matches. `head` becomes `NULL`. The next `remove("0011")` finds an empty list and returns `false`.

The output of `main.cpp` is:

```text
0101 -> 0011 -> 101 -> 0011 (size 4)
remove(0011): true   0101 -> 101 -> 0011 (size 3)
remove(11): false  0101 -> 101 -> 0011 (size 3)
remove(101): true   0101 -> 0011 (size 2)
remove(0101): true   0011 (size 1)
remove(0011): true   Empty (size 0)
remove(0011): false  Empty (size 0)
```

## Common mistakes

- **No size test.** The bit loop runs to `b.getSize()`. When the stored string is shorter than `b`, `data[i]` reads past its array. `main.cpp` does not show this mistake. A call such as `remove("11")` on a list that holds only `1` does: the result is still `false`, but valgrind reports `Invalid read of size 1`.
- **Comparing only up to the shorter size.** No invalid read, but `1` and `11` count as equal, and the wrong node is removed.
- **Comparing decimal values.** `011` and `11` then count as equal. The question defines equal as the same size and the same bits.
- **Unlinking without `delete`.** valgrind reports `definitely lost`.
- **Removing every equal string.** The function must stop at the first match. `main.cpp` has `0011` twice, and the second one must stay. With this mistake, the first `remove(0011)` line prints `0101 -> 101 (size 2)`, so the output does not match the `ExpectedOutput` block.
- **Forgetting the head case.** If the function always runs `prev->next() = ...`, removing the head writes through `NULL` and the program crashes.
- **Writing `curr->getData() == b`.** `Binary` has no `operator==`, so this does not compile. The build fails and the mark is 0.
