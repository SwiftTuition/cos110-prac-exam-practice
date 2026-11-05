# B2-01 Explanation: BinaryStrings::append

## What the function must do

`append(b)` adds a copy of `b` at the end of the list and adds 1 to `size`. If the list is empty, the new node becomes the head. These are the "empty" and "append" cases of the insertion flowcharts in Lecture 22.

## How the solution works

```cpp
void BinaryStrings::append(const Binary& b) {
    Node<Binary>* newNode = new Node<Binary>(b);
```

- `b` is a `const Binary&`: a reference to the caller's object, which the function may not change.
- `new Node<Binary>(b)` creates a node on the heap. The `Node` constructor takes a `T` by value and stores it in `data`, so the node holds its **own** `Binary`, made with the `Binary` copy constructor. The copy has its own bool array.
- The `Node` constructor sets `nextNode` to `NULL`. So the new node is already a correct last node.
- The list now owns this node. `~BinaryStrings()` deletes it later.

```cpp
    if (head == NULL) {
        head = newNode;
    } else {
```

The empty-list case. There is no last node to link from, so the new node becomes the head. Without this case, the walk below would start with `curr` equal to `NULL`.

```cpp
        Node<Binary>* curr = head;
        while (curr->next() != NULL) {
            curr = curr->next();
        }
        curr->next() = newNode;
    }
```

- `curr` starts at the head. The function never moves `head` itself; the lecture warns that moving `head` to walk the list loses the list.
- The loop condition `curr->next() != NULL` is true while `curr` is not the last node. Lecture 22 detects the end in the same way: "the traversal node's next is pointing to NULL".
- The loop stops **on** the last node, not after it. This matters: the function needs the last node to change its link.
- `next()` returns a reference to the link (`Node<T>*&`). So `curr->next() = newNode;` changes the last node's link itself, not a copy.

```cpp
    size++;
}
```

Every path adds one node, so `size` goes up by 1 in both cases.

## Trace

`main.cpp` starts with an empty list.

1. `append("0101")`: `head == NULL` is true, so `head = newNode`. The list is `0101`, size 1.
2. `append("11")`: the list is not empty. `curr` = node `0101`. `curr->next()` is `NULL`, so the loop does not run. `0101`'s link is set to the new node. The list is `0101 -> 11`, size 2.
3. `prepend("000")` (given): the list is `000 -> 0101 -> 11`, size 3.
4. `append("1")`:

| Loop check | curr | `curr->next()` | Continue? |
|---|---|---|---|
| 1 | `000` | `0101` | yes, `curr` = `0101` |
| 2 | `0101` | `11` | yes, `curr` = `11` |
| 3 | `11` | `NULL` | no |

   `11`'s link is set to the new node. The list is `000 -> 0101 -> 11 -> 1`, size 4.
5. `append(x)` with `x` = `0000`: the walk goes to `1`, and the new node holds a copy of `x`. Then `main.cpp` sets `x[0] = true`. Only `x` changes, because the node has its own array.

The output of `main.cpp` is:

```text
Empty (size 0)
0101 (size 1)
000 -> 0101 -> 11 -> 1 (size 4)
000 -> 0101 -> 11 -> 1 -> 0000 (size 5)
x is now 1000; the list keeps its own copy
```

## Common mistakes

- **No empty-list case.** `curr` starts as `NULL`, and `curr->next()` reads through `NULL`. valgrind reports `Invalid read of size 8`, and the program stops with a segmentation fault (`SIGSEGV`). The mark is 0.
- **Forgetting `size++`.** The list prints correctly but `getSize()` is wrong: `0101 (size 0)`.
- **Walking until `curr == NULL`** (`while (curr != NULL)`). The loop ends after the last node, with `curr` equal to `NULL`. The line `curr->next() = newNode;` then writes through `NULL`, and the program crashes.
- **Moving `head` to walk the list.** After the loop, `head` points to the last node, and every earlier node is lost. valgrind reports `definitely lost`.
- **Storing the caller's object instead of a copy.** With `data: T` this is not possible. Because `data` is a `T` (not a `T*`), the node always holds its own copy. In the HRMS practical, `data` was a `T*`, so a node there was made with `new T(value)`.
