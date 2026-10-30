# B2-02 Explanation: List::insertAt

## What the function must do

The function `insertAt` puts a new value into the list so that the value sits at index `pos`. Index 0 is the first node. The nodes that were at `pos` and later move one place to the right. If `pos` is 0 or less, the value goes at the front. If `pos` is as large as the list or larger, the value goes at the end. `size` increases by 1.

## How the solution works

A pointer is a variable that holds the address of an object. The operator `->` uses a pointer to reach a member. `NULL` means the pointer points to nothing. `T` is the template type, such as `int` or `string`.

The function builds the new node first:

```cpp
    Node<T>* newNode = new Node<T>(new T(value));
```

- `new T(value)` allocates a copy of the value on the heap.
- `new Node<T>(...)` allocates the node. The node owns the copy, and `~Node()` deletes it later.
- The given constructor sets the link of the new node to `NULL`.

The first branch handles the front of the list:

```cpp
    if (headNode == NULL || pos <= 0) {
        newNode->next() = headNode;
        headNode = newNode;
        size++;
        return;
    }
```

- The test `headNode == NULL` covers an empty list. An empty list has no node to walk from, so the new node must become the head.
- The test `pos <= 0` covers index 0 and every negative index. The question says these insert at the head.
- The operator `||` is true if either test is true.
- `newNode->next() = headNode` links the new node to the old first node. This line must run before the next line. If the order changes, the old head pointer is overwritten and the old nodes are lost.
- `headNode = newNode` makes the new node the first node.
- For an empty list, `headNode` is `NULL`. The new node then points to `NULL` and is the only node.
- `return` ends the function, so the walk below does not run.

The rest of the function handles `pos >= 1` on a list with at least one node:

```cpp
    Node<T>* prev = headNode;
    int count = 1;
    while (prev->next() != NULL && count < pos) {
        prev = prev->next();
        count++;
    }
```

- `prev` must end at the node directly before index `pos`. The function needs this node to change its link.
- `count` is the index of the node after `prev`. `prev` is the head at index 0, so `count` starts at 1.
- The test `count < pos` stops the walk at the right place. It is false when `count` equals `pos`. At that moment `prev` is at index `pos - 1`, the node directly before the new position.
- The test `prev->next() != NULL` protects against a `pos` larger than the list. Without it, `prev` would become `NULL`, and `prev->next()` would read through `NULL`. The program stops with a segmentation fault (SIGSEGV). With it, `prev` stops at the last node, and the new node goes at the end.
- The operator `&&` needs both tests to be true. The test on `prev->next()` runs first, so `NULL` is never dereferenced.

The last lines insert the node:

```cpp
    newNode->next() = prev->next();
    prev->next() = newNode;
    size++;
```

- `newNode->next() = prev->next()` points the new node at the node that follows `prev`. At the end of the list, this value is `NULL`, so the new node becomes the last node.
- `prev->next() = newNode` then points `prev` at the new node.
- The order matters. If `prev->next() = newNode` runs first, the original follower of `prev` is lost. Those nodes can never be reached or freed.
- `size++` keeps `size` equal to the number of nodes.

Memory: the function allocates one node and one value. The destructor of `List` frees them when the list ends. valgrind shows no leak.

## Trace

Call from `main.cpp`: `numbers.insertAt(35, 3);`. Before the call, the list is `10->20->30->40` and `size` is 4.

| Step | `prev` points to | `count` | Test: `prev->next() != NULL` and `count < pos` | Action |
|---|---|---|---|---|
| Setup | node 10 | 1 | not tested yet | The first `if` is false (`pos` is 3). |
| Loop test 1 | node 10 | 1 | true and `1 < 3` is true | `prev` moves to node 20, `count` becomes 2. |
| Loop test 2 | node 20 | 2 | true and `2 < 3` is true | `prev` moves to node 30, `count` becomes 3. |
| Loop test 3 | node 30 | 3 | `3 < 3` is false | The loop stops. |
| Link | node 30 | 3 | | `newNode->next()` becomes node 40. |
| Link | node 30 | 3 | | `prev->next()` becomes the new node. |

The chain is now `10->20->30->35->40`. The call sets `size` to 5.

The earlier call `numbers.insertAt(40, 5)` runs on the one-node list `20`. The loop test fails at once because `prev->next()` is `NULL`. The new node links after node 20 and the list is `20->40`.

The program output is:

```text
20 (size 1)
20->40 (size 2)
20->30->40 (size 3)
10->20->30->40 (size 4)
10->20->30->35->40 (size 5)
10->20->30->35->40->50 (size 6)
```

## Common mistakes

- Checking only `pos == 0` and not `pos <= 0`. A negative `pos` then reaches the walk. The test `count < pos` is false at once, so the loop does not run. The code inserts the node after the head, at index 1, and not at the front. In the main test, `insertAt(10, -3)` gives `20->10->30->40` and not `10->20->30->40`. The edge test calls `insertAt(-1000, -1000)` and fails in the same way.
- Leaving out `prev->next() != NULL` in the loop condition. A `pos` larger than the list moves `prev` to `NULL`. The next `prev->next()` dereferences `NULL`. In the main test, `insertAt(40, 5)` does this: valgrind reports "Invalid read of size 8" and the program stops with a segmentation fault (SIGSEGV).
- Leaving out `headNode == NULL` in the first test. For an empty list with `pos` greater than 0, `prev` starts as `NULL`, and the loop test `prev->next()` reads through `NULL`. The main test does not do this, so it still passes. The edge test inserts at position 3 into an empty list: valgrind reports "Invalid read of size 8" and the program stops with SIGSEGV.
- Writing `prev->next() = newNode` before `newNode->next() = prev->next()`. The new node then points to itself, and the original follower nodes are lost. The print loop never ends. In the main test, the second line prints `20->40->40->40...` without stopping.
- Forgetting `size++` on one path. The list prints correctly, but the printed size is wrong.
