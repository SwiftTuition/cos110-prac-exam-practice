# B2-03 Explanation: BinaryStrings::removeAt

## What the function must do

`removeAt(pos)` removes the node at position `pos` (the head is position 0), deletes it, subtracts 1 from `size` and returns `true`. For a position outside 0 to `size - 1` it changes nothing and returns `false`. These are the "front" and "middle/rear" removal cases of Lecture 23.

## How the solution works

```cpp
bool BinaryStrings::removeAt(int pos) {
    if (pos < 0 || pos >= size) {
        return false;
    }
```

- The valid positions are 0 to `size - 1`. `pos >= size` covers the position right after the end (`pos == size`) and every larger one.
- An empty list has `size` 0, so every `pos` is invalid there. No separate `head == NULL` test is needed.
- This test trusts `size`. The given code keeps `size` equal to the number of nodes, and this function keeps it that way.

```cpp
    Node<Binary>* temp = NULL;
    if (pos == 0) {
        temp = head;
        head = head->next();
    } else {
```

The front case (Lecture 23, RemoveFromFront): `temp` remembers the first node, and the head moves to the second node. If the list had one node, `head` becomes `NULL`, which is an empty list.

```cpp
        Node<Binary>* prev = head;
        for (int i = 0; i < pos - 1; i++) {
            prev = prev->next();
        }
        temp = prev->next();
        prev->next() = temp->next();
    }
```

The middle and rear cases.

- The loop moves `prev` `pos - 1` times, so `prev` stops on the node **before** position `pos`. A single forward link cannot reach back, so the function must stop one node early.
- `temp = prev->next();` is the node to remove. It exists, because `pos <= size - 1`.
- `prev->next() = temp->next();` makes `prev` skip `temp`. If `temp` was the last node, `temp->next()` is `NULL`, so `prev` becomes the new last node with a `NULL` link.

```cpp
    delete temp;
    size--;
    return true;
}
```

- `delete temp;` runs `~Node()`, which is empty, and then destroys the node's `data`. That runs `~Binary()`, which frees the bool array. So one `delete` frees both the node and its string.
- `~Node()` does not delete the next node, so the rest of the list is safe. The node is unlinked first, so nothing points to the deleted memory.
- `size--` keeps `size` equal to the number of nodes.

## Trace

`main.cpp` starts with `1 -> 000 -> 0011 -> 1101 -> 0101` (size 5).

| Call | Valid? | Case | prev | temp | List after | Returns |
|---|---|---|---|---|---|---|
| `removeAt(2)` | 0 <= 2 < 5 | middle, loop runs once | `000` | `0011` | `1 -> 000 -> 1101 -> 0101` | true |
| `removeAt(0)` | yes | front | - | `1` | `000 -> 1101 -> 0101` | true |
| `removeAt(2)` | 2 < 3 | rear, loop runs once | `1101` | `0101` | `000 -> 1101` | true |
| `removeAt(5)` | 5 >= 2 | - | - | - | unchanged | false |
| `removeAt(-1)` | -1 < 0 | - | - | - | unchanged | false |
| `removeAt(1)` | 1 < 2 | rear, loop runs 0 times (`pos - 1` is 0) | `000` | `1101` | `000` | true |
| `removeAt(0)` | yes | front | - | `000` | `Empty` | true |
| `removeAt(0)` | 0 >= 0 | - | - | - | `Empty` | false |

For the first call, the loop `for (i = 0; i < 1; i++)` runs once and moves `prev` from `1` to `000`. Then `temp` is `0011`, and `000` is linked to `1101`.

The loop can also run more than once. For a call such as `removeAt(3)` on a list `a -> b -> c -> d`, `pos - 1` is 2:

- `i` = 0: `0 < 2` is true, so `prev` moves from `a` to `b`.
- `i` = 1: `1 < 2` is true, so `prev` moves from `b` to `c`.
- `i` = 2: `2 < 2` is false, so the loop ends with `prev` on `c`.

Then `temp` is `d`, the node at position 3.

The output of `main.cpp` is:

```text
1 -> 000 -> 0011 -> 1101 -> 0101 (size 5)
removeAt(2): true   1 -> 000 -> 1101 -> 0101 (size 4)
removeAt(0): true   000 -> 1101 -> 0101 (size 3)
removeAt(2): true   000 -> 1101 (size 2)
removeAt(5): false  000 -> 1101 (size 2)
removeAt(-1): false  000 -> 1101 (size 2)
removeAt(1): true   000 (size 1)
removeAt(0): true   Empty (size 0)
removeAt(0): false  Empty (size 0)
```

## Common mistakes

- **Unlinking without `delete`.** The output is right, but every removed node and its bool array are lost. valgrind reports `definitely lost`, and the memory mark is lost.
- **`pos > size` instead of `pos >= size`.** With an empty list, `removeAt(0)` gets through (0 is not greater than 0), and `head = head->next();` reads through `NULL`. With a non-empty list, `removeAt(size)` (for example, `removeAt(2)` on a list of 2 nodes) leaves `temp` as `NULL`, and `temp->next()` reads through `NULL`. Both stop with `SIGSEGV`, mark 0. `main.cpp` ends with `removeAt(0)` on an empty list to catch this.
- **Deleting before unlinking.** `delete temp;` followed by `prev->next() = temp->next();` reads a deleted node. valgrind reports `Invalid read`.
- **Deleting the Binary's array as well**, for example through a pointer to `temp->getData()`. The node's destructor already frees it, so this is a double free (`Invalid free()`).
- **Walking `pos` steps instead of `pos - 1`.** `prev` then stops on the node to remove, and the wrong node is deleted.
- **Forgetting `size--`.** The printed list is right, but `getSize()` is wrong, and later calls trust a wrong `size`.
