# B2-09 Explanation: List::clear

## What the function must do

The function `clear` deletes every node of the list. After the call, `headNode` is `NULL` and `size` is 0. The list must still work afterwards. The caller can add values again, and the caller can call `clear` again, also on an empty list. In this question, the given destructor `~List()` calls `clear()`, so a wrong `clear` also breaks the destructor.

## How the solution works

A pointer is a variable that holds the address of an object. The operator `->` uses a pointer to reach a member. `NULL` means the pointer points to nothing. `delete` frees a heap object that `new` created. `T` is the template type.

Each node was created with `new`, and each node owns its value. `~Node()` deletes the value of that node. `~Node()` does not delete the next node. The function must therefore visit every node and call `delete` on it.

The loop starts here:

```cpp
    Node<T>* curr = headNode;
    while (curr != NULL) {
```

- `curr` points to the node that the loop handles. It starts at the first node.
- The condition `curr != NULL` is true while a node remains.
- For an empty list, `headNode` is `NULL`, so the loop body does not run. Calling `clear` on an empty list is safe.

The loop body has three lines:

```cpp
        Node<T>* temp = curr;      // never delete the loop variable itself
        curr = curr->next();
        delete temp;               // ~Node() deletes the data
```

1. `temp = curr` remembers the node that will be deleted.
2. `curr = curr->next()` moves `curr` to the following node. The function reads the link while the node still exists.
3. `delete temp` frees the old node. `~Node()` also frees the value inside it.

The order matters. If `delete` ran before `curr = curr->next()`, the function would read the link of a freed node. That is undefined behaviour, and valgrind reports an invalid read. The function also never deletes the value by hand, because `~Node()` does it, and a second delete would be a double free.

After the loop:

```cpp
    headNode = NULL;
    size = 0;
```

- Every node is deleted, but `headNode` still holds the address of the first deleted node. The assignment `headNode = NULL` removes this dangling pointer. A dangling pointer is a pointer to memory that was freed.
- Without this line, the print function and the destructor would read freed nodes. The destructor calls `clear()` again, and the second call would delete the same nodes twice.
- `size = 0` makes `size` equal to the number of nodes again. The list is empty.
- These two lines let the list work again. `prepend` can add a node to a list with `headNode` `NULL`.

Memory: the function frees every node and every value. The destructor `~List()` calls `clear()`, so the destructor frees a full list with the same code. A list that was cleared has no nodes, so the destructor does nothing more.

## Trace

Call from `main.cpp`: `numbers.clear();`. Before the call, the list is `1->2->3->4` and `size` is 4.

| Iteration | `curr` before | `temp` | `curr` after `curr = curr->next()` | Node deleted |
|---|---|---|---|---|
| 1 | node 1 | node 1 | node 2 | node 1 and its value |
| 2 | node 2 | node 2 | node 3 | node 2 and its value |
| 3 | node 3 | node 3 | node 4 | node 3 and its value |
| 4 | node 4 | node 4 | `NULL` | node 4 and its value |

The loop test `curr != NULL` is false after iteration 4. The function then sets `headNode` to `NULL` and `size` to 0. The print function shows `Empty List`. The later calls `prepend(7)` and `prepend(8)` build the new list `8->7`.

The program output is:

```text
1->2->3->4 (size 4)
Empty List (size 0)
8->7 (size 2)
```

## Common mistakes

- Deleting only the head node, for example `delete headNode;`. The other nodes are never freed. The output is still correct, but valgrind reports "definitely lost" for the other nodes.
- Writing `delete curr;` and then `curr = curr->next();`. The function reads the link of a freed node. That is undefined behaviour, and valgrind reports "Invalid read of size 8". In the test, the given `~Node()` had already set that link to `NULL`, so the loop stopped after the first node, and valgrind also reported the other nodes as "definitely lost".
- Leaving out `headNode = NULL`. The list prints freed nodes after `clear()`. In the main test, the second line is `1 (size 0)` and not `Empty List (size 0)`. The destructor then calls `clear()` again on the same freed nodes. valgrind reports "Invalid read of size 8" and "Invalid free() / delete / delete[] / realloc()".
- Leaving out `size = 0`. The list prints `Empty List`, but `getSize()` still returns the old number. In the main test, the second line is `Empty List (size 4)`, and the expected output shows `(size 0)`.
- Deleting the value as well as the node. `~Node()` already deletes the value, so the value is deleted twice. valgrind reports "Invalid free() / delete / delete[] / realloc()".
