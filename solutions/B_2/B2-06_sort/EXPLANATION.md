# B2-06 Explanation: List::sort

## What the function must do

The function `sort` puts the values in ascending order, with the smallest value at the head. The node data is read-only, because `getData()` returns a `const T&` and `Node` has no setter. The function therefore moves whole nodes by changing links. It creates no node and deletes no node. `size` does not change.

## How the solution works

A pointer is a variable that holds the address of an object. The operator `->` uses a pointer to reach a member. `NULL` means the pointer points to nothing. `T` is the template type. The function compares values with `<` and `<=`, so `T` must support them.

The method is insertion sort. The function builds a second chain called the sorted part. It takes the nodes of the original list one at a time and links each node into the right place in the sorted part. The original list is the unsorted part.

```cpp
    Node<T>* sorted = NULL;           // head of the sorted part
    Node<T>* curr = headNode;
```

- `sorted` points to the first node of the sorted part. The sorted part is empty at the start, so `sorted` is `NULL`.
- `curr` points to the node that the function moves next. It starts at the first node of the original list.

The outer loop runs once for each node:

```cpp
    while (curr != NULL) {
        Node<T>* temp = curr->next(); // remember the rest of the unsorted part
```

- The condition `curr != NULL` is false for an empty list, so the function does nothing and `headNode` stays `NULL`.
- `temp` saves the node after `curr`. The code below changes `curr->next()`. Without `temp`, the unsorted part would be lost.

The first case puts `curr` at the front of the sorted part:

```cpp
        if (sorted == NULL || curr->getData() < sorted->getData()) {
            curr->next() = sorted;
            sorted = curr;
        } else {
```

- `sorted == NULL` is true for the first node. The sorted part is empty, so `curr` becomes its only node.
- `curr->getData() < sorted->getData()` is true when `curr` holds a value smaller than the current first sorted value. The new node must then come before all sorted nodes.
- The operator `||` stops at the first true test. When `sorted` is `NULL`, the second test does not run, so the program never reads `sorted->getData()` through `NULL`.
- `curr->next() = sorted` points `curr` at the old front of the sorted part.
- `sorted = curr` makes `curr` the new front. The order matters. If the two lines swap, the old front is lost.

The second case finds the place inside or at the end of the sorted part:

```cpp
            Node<T>* prev = sorted;
            while (prev->next() != NULL && prev->next()->getData() <= curr->getData()) {
                prev = prev->next();
            }
            curr->next() = prev->next();
            prev->next() = curr;
        }
```

- `prev` starts at the first sorted node. The first sorted node is known to be not larger than `curr`, because case 1 was false.
- The test `prev->next() != NULL` stops the walk at the last sorted node. Without it, `prev->next()->getData()` would dereference `NULL`.
- The test `prev->next()->getData() <= curr->getData()` asks if the node after `prev` still belongs before `curr`. If so, `prev` moves forward.
- The walk stops when the next sorted node is larger than `curr`, or when the sorted part ends. The walk uses `<=`, so `curr` goes after sorted nodes that hold an equal value.
- `curr->next() = prev->next()` points `curr` at the node that follows `prev`. At the end of the sorted part, that value is `NULL`, so `curr` becomes the last node with a `NULL` link.
- `prev->next() = curr` then links `prev` to `curr`. The order matters. If this line runs first, the nodes after `prev` are lost.

The end of the outer loop and the function:

```cpp
        curr = temp;
    }
    headNode = sorted;
```

- `curr = temp` moves to the next node of the unsorted part.
- After the loop, every node is in the sorted part. `headNode = sorted` makes the sorted part the list.
- The last node of the sorted part keeps a `NULL` link. A node placed at the end copies `NULL` from `prev->next()`, and no later step changes it.

Memory: the function calls neither `new` nor `delete`. Every node is reused, so valgrind shows no leak.

## Trace

Call from `main.cpp`: `numbers.sort();`. Before the call, the list is `0->5->3->6->-1`.

| Iteration | `curr` | `temp` | Case | Sorted part after the iteration |
|---|---|---|---|---|
| 1 | 0 | 5 | `sorted == NULL`, case 1 | `0` |
| 2 | 5 | 3 | `5 < 0` is false. `prev` is 0 and `prev->next()` is `NULL`. | `0->5` |
| 3 | 3 | 6 | `3 < 0` is false. `prev` is 0. `5 <= 3` is false, so `prev` stays. | `0->3->5` |
| 4 | 6 | -1 | `6 < 0` is false. `prev` moves 0, 3, 5. Then `prev->next()` is `NULL`. | `0->3->5->6` |
| 5 | -1 | `NULL` | `-1 < 0` is true, case 1 | `-1->0->3->5->6` |

After iteration 5, `curr` becomes `NULL` and the loop ends. The assignment `headNode = sorted` makes node -1 the head.

The program output is:

```text
0->5->3->6->-1 (size 5)
-1->0->3->5->6 (size 5)
```

## Common mistakes

- Skipping `temp`. After `curr->next() = sorted` or `curr->next() = prev->next()`, the function cannot find the rest of the unsorted part. The outer loop ends early and nodes are lost. If the last line of the loop is `curr = curr->next();`, the main test prints `0 (size 5)` after the sort, and valgrind reports "definitely lost".
- Creating new nodes for the sorted part, for example `new Node<T>(new T(curr->getData()))`. The sorted list may print correctly. The edge test checks that the same nodes are reused, so it prints `Same nodes: no`. If the old nodes are not deleted, valgrind also reports "definitely lost".
- Leaving out `headNode = sorted`. The head still points to the old first node, whose link now leads into the sorted part. The printed list is wrong and the nodes before it in the sorted order are lost. The main test prints `0->3->5->6`, and valgrind reports "definitely lost" for node -1.
- Leaving out `prev->next() != NULL` in the inner loop. When `curr` is larger than every sorted value, `prev->next()` is `NULL` and the test `prev->next()->getData()` reads through `NULL`. In the main test, the second node (5) does this: valgrind reports "Invalid read of size 8" and the program stops with a segmentation fault (SIGSEGV).
- Leaving out `sorted == NULL` in case 1. The first node then reads `sorted->getData()` through `NULL`. valgrind reports "Invalid read of size 8" and the program stops with SIGSEGV.
- Trying to swap the data between nodes. `getData()` returns a `const T&` and `Node` has no setter. A line such as `a->getData() = b->getData();` does not compile: g++ reports "assignment of read-only location".
