# B2-04 Explanation: List::removeAt

## What the function must do

The function `removeAt` removes the node at index `pos`. Index 0 is the first node. If `pos` is negative or not smaller than the number of nodes, the function changes nothing and returns `false`. Otherwise the function unlinks the node, deletes it, subtracts 1 from `size` and returns `true`.

## How the solution works

A pointer is a variable that holds the address of an object. The operator `->` uses a pointer to reach a member. `NULL` means the pointer points to nothing. `T` is the template type, such as `int` or `string`.

The function starts with the range check:

```cpp
    if (pos < 0 || pos >= size) {
        return false;
    }
```

- `pos < 0` rejects negative indexes. A negative index has no node.
- `pos >= size` rejects an index at or past the end. The valid indexes are 0 to `size - 1`.
- The operator `||` is true if either test is true.
- An empty list has `size` equal to 0. Every `pos` then fails one of the two tests, so the function returns `false`.
- After this check, the list has at least one node and `pos` names an existing node. The code below does not need to test for `NULL` again.

The second branch removes the head:

```cpp
    if (pos == 0) {
        Node<T>* temp = headNode;
        headNode = headNode->next();
        delete temp;
        size--;
        return true;
    }
```

- The condition `pos == 0` selects the first node. The first node has no node before it, so the walk below cannot handle it.
- `temp` saves the address of the first node.
- `headNode = headNode->next()` moves the head to the second node. For a one-node list, `next()` is `NULL`, so the list becomes empty.
- `delete temp` frees the old first node. This line comes after the head moves. If `delete` ran first, `headNode->next()` would read a freed node.
- `~Node()` deletes the value that the node owns. The function does not delete the value itself, because that would delete it twice.
- `size--` keeps `size` equal to the number of nodes.

The remaining case has `pos` of at least 1. The function finds the node before index `pos`:

```cpp
    Node<T>* prev = headNode;
    for (int i = 0; i < pos - 1; i++) {
        prev = prev->next();
    }
```

- `prev` starts at index 0.
- The loop condition `i < pos - 1` makes the loop run `pos - 1` times. After that, `prev` sits at index `pos - 1`, the node directly before the target.
- The function needs this node to change its link.
- The loop does not test `prev->next()` for `NULL`. The range check at the top guarantees that index `pos` exists, so each step stays inside the list.

The last lines remove the node:

```cpp
    Node<T>* curr = prev->next();
    prev->next() = curr->next();
    delete curr;
    size--;
    return true;
```

- `curr` is the node at index `pos`. This node will be removed.
- `prev->next() = curr->next()` links the node before `curr` to the node after `curr`. The chain now skips `curr`. If `curr` is the last node, `curr->next()` is `NULL`, so `prev` becomes the last node.
- `delete curr` frees the node and its value. The link change must come first, because the function reads `curr->next()` before the node is freed.
- `size--` and `return true` finish the removal.

Memory: each successful call frees one node and its value. The destructor of `List` frees the nodes that remain.

## Trace

Call from `main.cpp`: `tryRemoveAt(numbers, 2);`. Before the call, the list is `10->20->30->40->50` and `size` is 5.

| Step | `i` | `prev` points to | Action |
|---|---|---|---|
| Range check | | | `2 < 0` is false and `2 >= 5` is false. Continue. |
| Head check | | | `pos == 0` is false. Continue. |
| Setup | | node 10 | `prev = headNode`. |
| Loop test | 0 | node 10 | `0 < 1` is true. `prev` becomes node 20. |
| Loop test | 1 | node 20 | `1 < 1` is false. The loop ends. |
| After loop | | node 20 | `curr` is node 30. |
| Link | | node 20 | `prev->next()` becomes node 40. The chain is `10->20->40->50`. |
| End | | node 20 | `delete curr` frees node 30. `size` becomes 4. Return `true`. |

The next call, `removeAt(0)`, uses the head branch and gives `20->40->50`. The call `removeAt(5)` fails the test `pos >= size` and returns `false`. The call `removeAt(-1)` fails the test `pos < 0` and returns `false`.

The program output is:

```text
10->20->30->40->50 (size 5)
removeAt(2): true -> 10->20->40->50 (size 4)
removeAt(0): true -> 20->40->50 (size 3)
removeAt(2): true -> 20->40 (size 2)
removeAt(5): false -> 20->40 (size 2)
removeAt(-1): false -> 20->40 (size 2)
```

## Common mistakes

- Writing the range check as `pos > size`. The value `pos == size` then passes the check. On an empty list, `removeAt(0)` reaches the head branch and reads `headNode->next()` through `NULL`. On a list with nodes, `curr` becomes `NULL` and `curr->next()` reads through `NULL`. The main test still passes. The first edge call, `removeAt(0)` on an empty list, makes valgrind report "Invalid read of size 8", and the program stops with a segmentation fault (SIGSEGV).
- Leaving out `pos < 0`. A negative `pos` skips the head branch, and the loop does not run. The function then removes the second node. In the main test, `removeAt(-1)` returns `true` and the list becomes `20`. On a one-node list, `curr` is `NULL`. The edge test calls `removeAt(-1)` on a one-node list: valgrind reports "Invalid read of size 8" and the program stops with SIGSEGV.
- Not handling `pos == 0` separately. The loop limit `pos - 1` is then -1, so the loop does not run and `prev` stays at the head. The code removes the second node, not the first. In the main test, `removeAt(0)` gives `10->40->50`. On a one-node list, `curr` is `NULL`, and the edge test stops with SIGSEGV after valgrind reports "Invalid read of size 8".
- Calling `delete curr` before `prev->next() = curr->next()`. The function then reads a freed node, which is undefined behaviour. valgrind reports "Invalid read of size 8". In the main test, the nodes after the removed node were cut off (`removeAt(2)` printed `10->20`), valgrind reported a leak, and the program then stopped with SIGSEGV.
- Deleting the value as well as the node, for example `delete &curr->getData();` before `delete curr;`. `~Node()` deletes the value too, so the value is deleted twice. valgrind reports "Invalid free() / delete / delete[] / realloc()".
- Forgetting `size--`. The list prints correctly, but the printed size is wrong. If `size--` is missing in the head branch, the edge test removes the only node of a one-node list, and `size` stays 1. The next `removeAt(0)` passes the range check and reads `headNode->next()` while `headNode` is `NULL`. valgrind reports "Invalid read of size 8" and the program stops with SIGSEGV.
