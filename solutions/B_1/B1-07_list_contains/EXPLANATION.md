# B1-07 Explanation: recursive contains

## What the function must do

The function `List<T>::contains(curr, value)` searches a linked list for a value. The function looks at the node `curr` and at every node after it. The function returns `true` if one of these nodes holds a value equal to `value`. Otherwise the function returns `false`.

Nodes before `curr` are not searched. If `curr` is `NULL`, the answer is `false`. This also covers an empty list. The function compares values with `==`, so strings must match exactly: `"hr"` is not equal to `"HR"`.

## How the solution works

```cpp
template <class T>
bool List<T>::contains(Node<T>* curr, T value) {
```

The line `template <class T>` makes `T` a placeholder for the type of the stored values. The parameter `curr` is a pointer to a `Node<T>`. A pointer holds the address of a node, and `NULL` means it points to nothing. The parameter `value` is a copy of the value to find. The function allocates no memory and frees none. The code sits between `#define B_1_CPP` and `#endif`, because `List.h` includes `B_1.cpp`.

```cpp
if (curr == NULL) {
    return false;
}
```

This is the first base case. The value `NULL` appears after the last node, and it also appears as the head of an empty list. The function has then looked at every node without a match, so the value is not in the list. This `if` must come before any use of `curr`. Without it, the next line would call `getData()` through a `NULL` pointer when the search reaches the end of the list. This is undefined behaviour.

```cpp
if (curr->getData() == value) {
    return true;
}
```

This is the second base case. The arrow `->` calls `getData()` on the node that `curr` points to. The call returns the stored value. If that value equals `value`, the search is finished, so the function returns `true`. The function makes no further call. The search stops at the first match, and the later nodes are not visited.

```cpp
return contains(curr->next(), value);
```

This is the recursive case. The current node does not hold the value, so the answer depends on the rest of the list. The call `curr->next()` gives the pointer to the following node. Each call moves one node forward, so the calls move toward `NULL`, which is the first base case. The function returns the answer of this call without a change.

## Trace

In `main.cpp`, the list is `5->10->15`. The first call is `contains(list.head(), 10)`.

| Call | curr points to | Value in node | Branch taken | Result |
|---|---|---|---|---|
| 1 | node 5 | 5, not equal to 10 | recursive case | waits for call 2 |
| 2 | node 10 | 10, equal to 10 | second base case | returns `true` |

Call 1 returns the `true` that it receives, so the answer is `true`.

The second call is `contains(list.head(), 7)`. No node holds 7.

| Call | curr points to | Value in node | Branch taken | Result |
|---|---|---|---|---|
| 1 | node 5 | 5, not equal to 7 | recursive case | waits for call 2 |
| 2 | node 10 | 10, not equal to 7 | recursive case | waits for call 3 |
| 3 | node 15 | 15, not equal to 7 | recursive case | waits for call 4 |
| 4 | `NULL` | none | first base case | returns `false` |

The calls return in the order 4, 3, 2, 1. Each call returns the `false` that it receives, so the answer is `false`.

The output of `main.cpp` is:

```text
5->10->15
Contains 10: true
Contains 7: false
Contains 15 (the last node): true
Contains 5, from the second node: false
Empty list contains 5: false
```

## Common mistakes

- **Testing `getData()` before `curr == NULL`.** For an empty list or for a missing value, the function calls `getData()` through a null pointer. This is undefined behaviour. In the test run, valgrind reported `Invalid read of size 8`, and the program stopped with a segmentation fault (`SIGSEGV`) at the main test `Contains 7`, because 7 is not in the list. The main test also uses an empty list, and the edge test calls `contains(NULL, 7)`.
- **Returning `false` when the first node does not match.** Code such as `else { return false; }` checks only the first node. The main test `Contains 15 (the last node)` then prints `false`.
- **Returning `true` in the `NULL` base case.** Every search then ends with `true`, so `Contains 7` prints `true`.
- **Writing `=` instead of `==`.** The function `getData()` returns a `const` reference, so an assignment to the result is a compile error: `assignment of read-only location`. The mark is 0.
- **Calling `contains(curr->next(), value);` without `return`.** The compiler warns that control reaches the end of a non-void function. Under `-Wall -Werror` this stops the build.
- **A loop or a helper function.** QUESTION.md states that either one scores 0.
