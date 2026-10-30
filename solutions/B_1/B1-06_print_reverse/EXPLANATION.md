# B1-06 Explanation: recursive printReverse

## What the function must do

The function `List<T>::printReverse(curr)` prints the values of a linked list in reverse order. The function starts with the last node and ends with the node `curr`. Each value goes on its own line, with `cout` and `endl`.

For the list `1->2->3`, the call `printReverse(head())` prints `3`, `2` and `1`. A linked list has only forward links, so the function cannot walk backward. If `curr` is `NULL`, the function prints nothing. The function must not change the list.

## How the solution works

```cpp
template <class T>
void List<T>::printReverse(Node<T>* curr) {
```

The line `template <class T>` makes `T` a placeholder for the type of the stored values. The parameter `curr` is a pointer to a `Node<T>`. A pointer holds the address of a node, and `NULL` means it points to nothing. The function allocates no memory and frees none. The code sits between `#define B_1_CPP` and `#endif`, because `List.h` includes `B_1.cpp`.

```cpp
if (curr == NULL) {
    return;
}
```

This is the base case. The value `NULL` appears after the last node, and it also appears as the head of an empty list. In both situations there is nothing to print, so the function returns. The type `void` means the function returns no value, so `return;` has no value. Without this base case, every call would make another call, so the recursion could never end. g++ 13 sees this and reports `infinite recursion detected`. Under `-Wall -Werror` the build fails.

```cpp
printReverse(curr->next());
cout << curr->getData() << endl;
```

This is the recursive case. The expression `curr->next()` uses the arrow `->` to call `next()` on the node that `curr` points to. The call gives the pointer to the following node. Each call moves one node forward, so the calls move toward `NULL`, which is the base case.

The order of the two lines is what reverses the output. The function first calls itself for the rest of the list. That call prints all later nodes, from the last one backward. Only after that call returns does the function print its own value with `cout << curr->getData() << endl;`. The call `getData()` returns the value stored in the node. The function does not change any pointer, so the list stays the same.

## Trace

In `main.cpp`, the list is `1->2->3`. The call is `printReverse(list.head())`.

| Call | curr points to | Branch taken | Prints |
|---|---|---|---|
| 1 | node 1 | recursive case, calls call 2 first | nothing yet |
| 2 | node 2 | recursive case, calls call 3 first | nothing yet |
| 3 | node 3 | recursive case, calls call 4 first | nothing yet |
| 4 | `NULL` | base case, returns | nothing |

The calls return in the order 4, 3, 2, 1. After each return, the caller runs its print line:

- Call 3 returns from call 4, then prints `3`.
- Call 2 returns from call 3, then prints `2`.
- Call 1 returns from call 2, then prints `1`.

The call `printReverse(list.head()->next())` starts at node 2. This call prints `3` and then `2`. The call on the empty list is a base case at once and prints nothing.

The output of `main.cpp` is:

```text
1->2->3
Reverse:
3
2
1
Reverse from the second node:
3
2
Reverse of an empty list:
(end)
```

## Common mistakes

- **Printing before the recursive call.** If `cout << curr->getData() << endl;` comes first, the values appear in forward order: `1`, `2`, `3`. The output is wrong, and the edge tests with a list of strings and a list of 10 numbers show this error.
- **No check for `NULL`.** Without the `if`, every call makes another call, so the recursion can never end. g++ 13 reports `infinite recursion detected`, and under `-Wall -Werror` the build fails. The mark is 0.
- **Printing without `endl`.** The values appear on one line, for example `321`. The expected output has one value on each line.
- **Calling `printReverse(curr)` instead of `printReverse(curr->next())`.** The argument never changes, so the recursion never ends. The program compiles, but at run time valgrind reports `Stack overflow` and the program stops with a segmentation fault (`SIGSEGV`). Nothing after `Reverse:` is printed.
- **Changing the list.** QUESTION.md says not to change the list. The last edge test prints the list again after the call and expects the same list and the same size.
- **A loop or a helper function.** QUESTION.md states that either one scores 0.
