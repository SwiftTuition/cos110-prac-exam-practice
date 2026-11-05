# B2-05 Explanation: BinaryStrings::reverse

## What the function must do

`reverse()` puts the nodes in the opposite order by reversing every link. It creates no node and deletes no node. The strings themselves do not change, and `size` does not change.

## How the solution works

The function walks the list once with three pointers:

- `curr`: the node whose link is being reversed.
- `prev`: the node before `curr` in the old order. After the link is reversed, `curr` points to it.
- `temp`: the node after `curr` in the old order. It is saved before the link changes.

```cpp
void BinaryStrings::reverse() {
    Node<Binary>* prev = NULL;
    Node<Binary>* curr = head;
```

`prev` starts as `NULL`, because the old head becomes the new last node, and the last node's link must be `NULL`.

```cpp
    while (curr != NULL) {
        Node<Binary>* temp = curr->next();
        curr->next() = prev;
        prev = curr;
        curr = temp;
    }
```

- `curr != NULL`: the loop runs once per node. For an empty list it does not run.
- `temp = curr->next();` saves the rest of the list. The next line overwrites `curr`'s link, and without `temp` the rest of the list would be lost.
- `curr->next() = prev;` reverses the link. `next()` returns a reference, so this changes the node's own link.
- `prev = curr;` and `curr = temp;` move both pointers one node forward in the old order.

```cpp
    head = prev;
}
```

When the loop ends, `curr` is `NULL` and `prev` is the old last node. That node is the new head. For an empty list, `prev` is still `NULL`, so `head` stays `NULL`.

No `new` and no `delete`: the same nodes are reused, so the memory does not change.

## Trace

`main.cpp` starts with `000 -> 0011 -> 1101 -> 0101`.

| Iteration | curr | temp | Link set | prev after | Reversed part |
|---|---|---|---|---|---|
| 1 | `000` | `0011` | `000` -> `NULL` | `000` | `000` |
| 2 | `0011` | `1101` | `0011` -> `000` | `0011` | `0011 -> 000` |
| 3 | `1101` | `0101` | `1101` -> `0011` | `1101` | `1101 -> 0011 -> 000` |
| 4 | `0101` | `NULL` | `0101` -> `1101` | `0101` | `0101 -> 1101 -> 0011 -> 000` |

After iteration 4, `curr` is `NULL` and the loop ends. `head = prev` makes `0101` the head.

The second `reverse()` in `main.cpp` puts the list back in the first order. The empty list stays `Empty`.

A list with one node `a` is not in `main.cpp`, but the loop handles it. Iteration 1: `curr != NULL` is true. `temp` = `NULL`, `a->next()` = `NULL`, `prev` = `a`, and `curr` = `NULL`. Next check: `curr != NULL` is false, so the loop ends. `head` = `a`, so the list is unchanged.

The output of `main.cpp` is:

```text
000 -> 0011 -> 1101 -> 0101 (size 4)
0101 -> 1101 -> 0011 -> 000 (size 4)
000 -> 0011 -> 1101 -> 0101 (size 4)
Empty (size 0)
```

## Common mistakes

- **Forgetting `head = prev;`.** `head` still points to the old first node, which is now the last node with a `NULL` link. The list prints as `000` only, and the other three nodes are lost: valgrind reports `definitely lost`.
- **No `temp`** (`curr = curr->next();` after the link has changed). `curr->next()` is now the previous node, or `NULL` on the first pass. The loop ends after one node, and the rest of the list is lost. valgrind reports `definitely lost`.
- **Making a new reversed list with `new` and not deleting the old nodes.** The output can look right, but the old nodes leak. The question says the same nodes must be used, and the marking program checks this.
- **Swapping the strings instead of the links.** `Binary`'s `operator=` is private here, so `a->getData() = b->getData();` does not compile. If `Binary` did not declare `operator=`, the compiler would make one. That one copies the array pointer, so two strings would delete the same array (`Invalid free()`).
- **Reversing the bits inside each string.** The question reverses the order of the nodes only.
