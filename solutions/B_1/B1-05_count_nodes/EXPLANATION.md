# B1-05 Explanation: recursive countNodes

## What the function must do

The function `List<T>::countNodes(curr)` counts the nodes of a linked list from the node `curr` to the end of the list. The count includes `curr` itself. The call `list.countNodes(list.head())` counts the whole list. The call `list.countNodes(list.head()->next())` counts every node except the first.

If `curr` is `NULL`, there are no nodes, so the answer is `0`. This also covers an empty list, because `head()` returns `NULL` for an empty list. The function must not use `size` or `getSize()`, because those count the whole list.

## How the solution works

```cpp
template <class T>
int List<T>::countNodes(Node<T>* curr) {
```

The line `template <class T>` makes `T` a placeholder for the type of the stored values, such as `int` or `string`. The name `List<T>::countNodes` says that the function belongs to the class `List<T>`. The parameter `curr` is a pointer to a `Node<T>`. A pointer holds the address of a node, and `NULL` means it points to nothing. The function only reads the list. The function allocates no memory and frees none.

The whole definition sits between `#define B_1_CPP` and `#endif`. The header `List.h` includes `B_1.cpp` at the bottom, so the template code is visible where the template is used.

```cpp
if (curr == NULL) {
    return 0;
}
```

This is the base case. A linked list ends with a node whose `next()` is `NULL`. When `curr` is `NULL`, the function has moved past the last node, so no nodes are left to count. This `if` also protects the empty list, where the first call receives `NULL`. Without the base case, every call would make another call, so the recursion could never end. g++ 13 sees this and reports `infinite recursion detected`. Under `-Wall -Werror` the build fails.

```cpp
return 1 + countNodes(curr->next());
```

This is the recursive case. The expression `curr->next()` uses the arrow `->` to call `next()` on the node that `curr` points to. The call gives the pointer to the following node. The call `countNodes(curr->next())` counts all nodes after the current one, and the `1` counts the current node. Each call moves one node forward, so the calls move toward the end of the list, where `curr` is `NULL`. The addition runs after the recursive call returns.

## Trace

In `main.cpp`, the list is `10->20->30->40`. The call is `countNodes(list.head())`.

| Call | curr points to | Branch taken | Result |
|---|---|---|---|
| 1 | node 10 | recursive case | waits for call 2 |
| 2 | node 20 | recursive case | waits for call 3 |
| 3 | node 30 | recursive case | waits for call 4 |
| 4 | node 40 | recursive case | waits for call 5 |
| 5 | `NULL` | base case | returns `0` |

The calls return in the order 5, 4, 3, 2, 1:

- Call 4 returns `1 + 0 = 1`.
- Call 3 returns `1 + 1 = 2`.
- Call 2 returns `1 + 2 = 3`.
- Call 1 returns `1 + 3 = 4`.

The call `countNodes(list.head()->next())` starts at node 20. This call makes 4 calls, with the last call on `NULL`, and returns `3`. The call `empty.countNodes(empty.head())` starts at `NULL`, so call 1 is the base case and returns `0`.

The output of `main.cpp` is:

```text
10->20->30->40
Nodes from the head: 4
Nodes from the second node: 3
Nodes in an empty list: 0
```

## Common mistakes

- **Using `size` or `getSize()`.** QUESTION.md forbids both, because they give the length of the whole list. A call that starts at the second node would still give `4` for this list, not `3`.
- **Stopping at the last node without a check of `curr`.** A base case such as `curr->next() == NULL` reads `next()` through `curr`. For an empty list, `curr` is `NULL`, so this reads through a null pointer. This is undefined behaviour. In the test run, valgrind reported `Invalid read of size 8`, and the program stopped with a segmentation fault (`SIGSEGV`) at the empty list in `main.cpp`. The edge test `countNodes(NULL)` covers this too.
- **Leaving out the `1`.** The line `return countNodes(curr->next());` adds nothing for each node, so the function returns `0` for every list.
- **Calling `countNodes(curr)` instead of `countNodes(curr->next())`.** The argument never changes, so the recursion never ends. The program compiles, but at run time valgrind reports `Stack overflow` and the program stops with a segmentation fault (`SIGSEGV`).
- **Placing code after `#endif`.** QUESTION.md states that this gives a redefinition error. g++ reports `redefinition of 'int List<T>::countNodes(Node<T>*)'`.
- **A loop or a helper function.** QUESTION.md states that either one scores 0.
