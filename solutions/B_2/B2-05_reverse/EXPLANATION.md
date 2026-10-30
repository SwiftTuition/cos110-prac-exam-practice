# B2-05 Explanation: List::reverse

## What the function must do

The function `reverse` changes the order of the nodes so that the last node becomes the first node. The function does this by changing the links only. It creates no node and deletes no node. `size` does not change. An empty list and a one-node list stay as they are.

## How the solution works

A pointer is a variable that holds the address of an object. The operator `->` uses a pointer to reach a member. `NULL` means the pointer points to nothing. `next()` returns a reference to the link of a node, so an assignment to `curr->next()` changes the real link.

The function uses two walking pointers:

```cpp
    Node<T>* prev = NULL;
    Node<T>* curr = headNode;
```

- `curr` is the node that the loop works on. It starts at the first node.
- `prev` is the node that came before `curr` in the original list. At the start there is no such node, so `prev` is `NULL`.
- The first node will become the last node. A last node must have `NULL` as its link. The start value of `prev` supplies that `NULL`.

The loop turns each link around:

```cpp
    while (curr != NULL) {
```

- The condition `curr != NULL` is true while a node remains to process. The loop ends when `curr` moves past the last node.
- For an empty list, `headNode` is `NULL`, so the loop body never runs. For a one-node list, the loop body runs once.

Each pass has four lines:

```cpp
        Node<T>* temp = curr->next();   // remember the rest of the list
        curr->next() = prev;            // turn this link around
        prev = curr;
        curr = temp;
```

1. `temp = curr->next()` saves the address of the node after `curr`. The next line overwrites this link, so the function must save it first. Without `temp`, the rest of the list is lost.
2. `curr->next() = prev` points `curr` back at the node before it. This reverses one link.
3. `prev = curr` moves `prev` forward. `curr` is now the front of the reversed part.
4. `curr = temp` moves `curr` to the next unprocessed node.

The order of these four lines matters. Line 2 destroys the old forward link, and line 1 keeps a copy of it. Lines 3 and 4 must run after line 2, because line 2 uses the old `prev` and the old `curr`. Line 3 must run before line 4, because line 3 copies the old `curr` and line 4 changes `curr`.

After the loop:

```cpp
    headNode = prev;                    // the old last node is the new head
```

- When the loop ends, `curr` is `NULL` and `prev` is the old last node.
- `headNode` still points to the old first node, which is now the last node. The assignment moves `headNode` to the old last node.
- For an empty list, `prev` is `NULL`, so `headNode` stays `NULL`.
- The function does not change `size`, because the number of nodes is the same.

Memory: the function calls neither `new` nor `delete`. Every node stays in use, so valgrind shows no leak.

## Trace

Call from `main.cpp`: the first `numbers.reverse();`. Before the call, the list is `1->2->3->4->5`.

| Iteration | `curr` | `temp` | After `curr->next() = prev` | `prev` after | `curr` after |
|---|---|---|---|---|---|
| Start | node 1 | | | `NULL` | node 1 |
| 1 | node 1 | node 2 | `1->NULL` | node 1 | node 2 |
| 2 | node 2 | node 3 | `2->1->NULL` | node 2 | node 3 |
| 3 | node 3 | node 4 | `3->2->1->NULL` | node 3 | node 4 |
| 4 | node 4 | node 5 | `4->3->2->1->NULL` | node 4 | node 5 |
| 5 | node 5 | `NULL` | `5->4->3->2->1->NULL` | node 5 | `NULL` |

The loop test `curr != NULL` is false after iteration 5. The line `headNode = prev` then makes node 5 the head. The list is `5->4->3->2->1`.

The second `numbers.reverse();` repeats the same steps on this list and restores `1->2->3->4->5`.

The program output is:

```text
1->2->3->4->5 (size 5)
5->4->3->2->1 (size 5)
1->2->3->4->5 (size 5)
```

## Common mistakes

- Leaving out `temp`, for example by writing `curr = curr->next();` as the last line. After `curr->next() = prev`, that link already points back, so the function cannot find the next node. In the main test, the loop stops after one pass. The list prints `1 (size 5)`, the other nodes are lost, and valgrind reports "definitely lost".
- Leaving out `headNode = prev`. The head still points to the old first node. That node is now the last node and its link is `NULL`. In the main test, the program prints `1 (size 5)`. The other nodes are never freed, so valgrind reports "definitely lost".
- Starting with `prev` set to `headNode` and not to `NULL`. The old first node then points to itself. The list has a cycle, and the print loop never ends. In the main test, the second line prints `5->4->3->2->1->1->1...` without stopping.
- Building a new list with `new` and then deleting the old nodes. The question forbids this because the marking program checks that the same nodes are used. The edge test compares node addresses, so new nodes give `no` in the lines "Same head node", "Old tail is the new head" and "Old head is the new tail". The edge test also reads a deleted node through its saved pointer, so valgrind reports "Invalid read of size 8".
- Looping with `while (curr->next() != NULL)`. The loop skips the last node, so the last node is not linked into the reversed list. In the main test, the list prints `4->3->2->1`, and valgrind reports a leak for the lost node. For an empty list, `curr` is `NULL` and `curr->next()` reads through `NULL`. The edge test starts with an empty list: valgrind reports "Invalid read of size 8" and the program stops with a segmentation fault (SIGSEGV).
