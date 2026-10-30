# B2-03 Explanation: List::remove

## What the function must do

The function `remove` searches the list from the head for the first node whose value equals `value`. If the function finds the node, it removes the node from the chain, deletes it, subtracts 1 from `size` and returns `true`. If the list is empty or no node matches, the function changes nothing and returns `false`. Only the first match is removed.

## How the solution works

A pointer is a variable that holds the address of an object. The operator `->` uses a pointer to reach a member. `NULL` means the pointer points to nothing. `T` is the template type, so the function compares values with `==` and `T` must support that operator.

The function has four cases. The first case handles the empty list:

```cpp
    if (headNode == NULL) {
        return false;
    }
```

- The condition checks for an empty list. The next case calls `headNode->getData()`. If `headNode` is `NULL`, that call reads through `NULL`, and the program stops with a segmentation fault (SIGSEGV).
- An empty list has nothing to remove, so the function returns `false`.

The second case handles a match at the head:

```cpp
    if (headNode->getData() == value) {
        Node<T>* temp = headNode;
        headNode = headNode->next();
        delete temp;    // ~Node() deletes the data
        size--;
        return true;
    }
```

- `getData()` returns the stored value. The condition asks if the first node holds `value`.
- The head needs its own case because no node comes before it. The usual rule "make the previous node skip this node" has no previous node here. The function must change `headNode` itself.
- `temp` remembers the node that will be deleted. A local pointer variable holds this address.
- `headNode = headNode->next()` moves the head to the second node. For a one-node list, `next()` is `NULL`, so the list becomes empty.
- `delete temp` frees the old head. The order matters. If `delete temp` ran first, `headNode->next()` would read freed memory.
- `~Node()` also deletes the value that the node owns. The function does not delete the value by hand, because that would cause a double delete.
- `size--` and `return true` finish the removal.

The third case searches the rest of the list:

```cpp
    Node<T>* prev = headNode;
    Node<T>* curr = headNode->next();
    while (curr != NULL) {
```

- `prev` points to the node before `curr`. The function needs `prev` to link around the removed node.
- `curr` starts at the second node. The head was already checked in case 2.
- The condition `curr != NULL` stops the loop after the last node. For a one-node list, `curr` is `NULL` at the start, so the loop does not run and the function reaches `return false`. The loop never reads `curr->getData()` through `NULL`.

Inside the loop:

```cpp
        if (curr->getData() == value) {
            prev->next() = curr->next();
            delete curr;
            size--;
            return true;
        }
        prev = curr;
        curr = curr->next();
```

- The `if` checks if the current node holds `value`.
- `prev->next() = curr->next()` links the node before `curr` to the node after `curr`. The chain now skips `curr`. If `curr` is the last node, `curr->next()` is `NULL`, so `prev` becomes the last node.
- `delete curr` then frees the node and its value. The link must change first. After `delete`, the program cannot read `curr->next()` safely.
- If the node does not match, `prev = curr` and `curr = curr->next()` move both pointers one node forward. `prev` is assigned first, so it takes the old `curr` before `curr` changes.

The fourth case runs when the loop ends without a match:

```cpp
    return false;
```

The list is unchanged, `size` is unchanged, and the function reports that nothing was removed.

Memory: the function frees exactly one node and its value for each successful removal. The destructor of `List` frees any node that remains.

## Trace

Call from `main.cpp`: `tryRemove(numbers, 3);`. Before the call, the list is `1->2->3->4->5` and `size` is 5.

| Step | `prev` | `curr` | Check | Result |
|---|---|---|---|---|
| Case 1 | | | `headNode == NULL` is false | Continue. |
| Case 2 | | | head holds 1, and `1 == 3` is false | Continue. |
| Setup | node 1 | node 2 | `curr != NULL` is true | Enter the loop. |
| Iteration 1 | node 1 | node 2 | `2 == 3` is false | `prev` becomes node 2, `curr` becomes node 3. |
| Iteration 2 | node 2 | node 3 | `3 == 3` is true | `prev->next()` becomes node 4. The chain is `1->2->4->5`. |
| End | node 2 | node 3 | | `delete curr` frees node 3 and its value. `size` becomes 4. Return `true`. |

The later calls use other cases. The call `remove(1)` takes case 2 and moves `headNode` to node 2. The call `remove(5)` finds the last node in the loop, and `prev->next()` becomes `NULL`. The call `remove(9)` runs the loop to the end and returns `false`.

The program output is:

```text
1->2->3->4->5 (size 5)
remove(3): true -> 1->2->4->5 (size 4)
remove(1): true -> 2->4->5 (size 3)
remove(5): true -> 2->4 (size 2)
remove(9): false -> 2->4 (size 2)
```

## Common mistakes

- Skipping the head case. A match at the head has no node before it. If the code starts with `prev = NULL` and `curr = headNode`, a match at the head runs `prev->next()` with `prev` equal to `NULL`. In the main test, `remove(1)` does this. valgrind reports "Invalid write of size 8" and the program stops with a segmentation fault (SIGSEGV). If the loop starts at the second node and there is no head case, `remove(1)` returns `false` and the output is wrong.
- Writing a search loop that reads `curr->getData()` or `curr->next()` without testing `curr` for `NULL`. The edge test catches this. In that test, a one-node list searches for a value that is not there. `curr` starts as `headNode->next()`, which is `NULL`, and the loop reads `curr->getData()` through `NULL`. valgrind reports "Invalid read of size 8" and the program stops with SIGSEGV.
- Calling `delete curr` before `prev->next() = curr->next()`. The program then reads a freed node, which is undefined behaviour. valgrind reports "Invalid read of size 8". In the test, the nodes after the removed node were cut off the list (`remove(3)` printed `1->2`), and valgrind also reported a leak.
- Forgetting `size--`. The list prints correctly but shows the wrong size.
- Removing every match instead of the first. The duplicate test `7->8->7` expects `8->7` after the first call, and the output differs.
