# B2-02 Explanation: BinaryStrings::insertAt

## What the function must do

`insertAt(b, pos)` inserts a copy of `b` so that it becomes the node at position `pos` (the head is position 0). A `pos` of 0 or less inserts at the front. A `pos` at or past the end appends. An empty list gets the new node as its only node. `size` goes up by 1 in every case. These are the rules of the combined `insert(val, pos)` in Lecture 22.

## How the solution works

```cpp
void BinaryStrings::insertAt(const Binary& b, int pos) {
    Node<Binary>* newNode = new Node<Binary>(b);
```

The node holds its own copy of `b` (the `Node` constructor copies the `Binary`). Its link starts as `NULL`.

```cpp
    if (pos <= 0 || head == NULL) {
        newNode->next() = head;
        head = newNode;
        size++;
        return;
    }
```

The front case.

- `pos <= 0`: the question puts every position of 0 or less at the front.
- `head == NULL`: in an empty list, the only place is the front, for any value of `pos`.
- `newNode->next() = head;` links the new node to the old first node (or to `NULL` for an empty list).
- `head = newNode;` makes it the first node. The order matters: if `head` changed first, the old first node would be lost.
- `return;` stops here, so the code below runs only for a non-empty list and `pos >= 1`.

```cpp
    Node<Binary>* prev = head;
    int count = 1;
    while (prev->next() != NULL && count < pos) {
        prev = prev->next();
        count++;
    }
```

The walk finds the node **before** position `pos`. The new node goes after it.

- `prev` starts at the head (position 0). `count` is the position right after `prev`, so it starts at 1.
- `count < pos`: while the place after `prev` is still before `pos`, move on. When `count == pos`, the new node belongs right after `prev`.
- `prev->next() != NULL`: stop at the last node. If `pos` is past the end, the walk ends on the last node, and the new node is appended.
- The `&&` checks `prev->next() != NULL` first. Both tests are needed: without the first, a large `pos` walks `prev` into `NULL`.

```cpp
    newNode->next() = prev->next();
    prev->next() = newNode;
    size++;
}
```

- First, the new node points to the node after `prev` (or to `NULL` at the end of the list).
- Then `prev` points to the new node.
- The order matters. If `prev->next() = newNode;` came first, the rest of the list after `prev` would be lost.

## Trace

`main.cpp` starts with `000 -> 0011 -> 1101` (size 3).

1. `insertAt("1", 0)`: `0 <= 0`, front case. The list is `1 -> 000 -> 0011 -> 1101`, size 4.
2. `insertAt("01", 2)`:

| Loop check | prev | count | `prev->next() != NULL` | `count < 2` | Continue? |
|---|---|---|---|---|---|
| 1 | `1` | 1 | yes | yes | yes: `prev` = `000`, count = 2 |
| 2 | `000` | 2 | yes | no | no |

   The new node goes after `000`: `1 -> 000 -> 01 -> 0011 -> 1101`, size 5. `01` is at position 2.
3. `insertAt("111", 99)` on `1 -> 000 -> 01 -> 0011 -> 1101`: `99 <= 0` is false and `head` is not `NULL`, so the walk runs.

| Loop check | prev | count | `prev->next() != NULL` | `count < 99` | Continue? |
|---|---|---|---|---|---|
| 1 | `1` | 1 | yes | yes | yes: `prev` = `000`, count = 2 |
| 2 | `000` | 2 | yes | yes | yes: `prev` = `01`, count = 3 |
| 3 | `01` | 3 | yes | yes | yes: `prev` = `0011`, count = 4 |
| 4 | `0011` | 4 | yes | yes | yes: `prev` = `1101`, count = 5 |
| 5 | `1101` | 5 | no (`next()` is `NULL`) | yes | no |

   The walk stops because `prev->next()` is `NULL`, not because of `count`. The new node goes after `1101`: `1 -> 000 -> 01 -> 0011 -> 1101 -> 111`, size 6.
4. `insertAt("10", -3)`: `-3 <= 0`, front case: `10 -> 1 -> 000 -> 01 -> 0011 -> 1101 -> 111`, size 7.

One case is not in `main.cpp`: `insertAt(b, 5)` on an empty list. `5 <= 0` is false, but `head == NULL` is true, so the front case runs. `newNode->next()` is `NULL`, `head` is `newNode`, and `size` is 1.

The output of `main.cpp` is:

```text
000 -> 0011 -> 1101 (size 3)
insertAt(1, 0):   1 -> 000 -> 0011 -> 1101 (size 4)
insertAt(01, 2):  1 -> 000 -> 01 -> 0011 -> 1101 (size 5)
insertAt(111, 99): 1 -> 000 -> 01 -> 0011 -> 1101 -> 111 (size 6)
insertAt(10, -3): 10 -> 1 -> 000 -> 01 -> 0011 -> 1101 -> 111 (size 7)
```

## Common mistakes

- **No end-of-list test in the walk** (`while (count < pos)`). For `pos` 99, `prev` becomes `NULL` and `prev->next()` reads through `NULL`. valgrind reports `Invalid read of size 8`, and the program stops with `SIGSEGV`. The mark is 0.
- **Starting `count` at 0.** The walk takes one step too many, so `01` lands at position 3: `1 -> 000 -> 0011 -> 01 -> 1101`. The output is wrong.
- **Linking in the wrong order** (`prev->next() = newNode;` first). The nodes after `prev` are lost. The list prints short, and valgrind reports `definitely lost`.
- **No `head == NULL` in the front test.** For an empty list and `pos` 5, the walk starts with `prev` equal to `NULL` and crashes.
- **Forgetting `size++` in the front case.** The `return;` skips the `size++` at the end, so the size is wrong after every front insert.
