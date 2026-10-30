# B2-07 Explanation: List::indexOf

## What the function must do

The function `indexOf` finds the first node, counting from the head, whose value equals `value`. The function returns the index of that node. The first node has index 0. If the list is empty or no node holds the value, the function returns -1. The function does not change the list.

## How the solution works

A pointer is a variable that holds the address of an object. The operator `->` uses a pointer to reach a member. `NULL` means the pointer points to nothing. `T` is the template type, such as `int` or `string`. The function compares values with `==`, so `T` must support that operator.

The function starts with two variables:

```cpp
    Node<T>* curr = headNode;
    int index = 0;
```

- `curr` is a pointer to the node that the function checks now. It starts at the first node.
- `index` is the position of `curr`. The first node has position 0, so `index` starts at 0.
- The function only reads the nodes. It does not call `new` or `delete`, and it does not change any link.

The loop visits the nodes one at a time:

```cpp
    while (curr != NULL) {
```

- The condition `curr != NULL` is true while `curr` points to a real node.
- For an empty list, `headNode` is `NULL`, so the loop body never runs. The function goes straight to `return -1`.
- The loop ends when `curr` moves past the last node and becomes `NULL`. The program never calls `getData()` through `NULL`.

The check inside the loop:

```cpp
        if (curr->getData() == value) {
            return index;   // early exit: the first match wins
        }
```

- `getData()` returns the value that the node stores. The condition asks if that value equals `value`.
- If the condition is true, the function returns `index` at once. The function leaves the loop, so later nodes are not checked.
- This early `return` is the reason the function reports the first match. If a list has duplicates, the first match has the smallest index. The edge test uses `HR->Sales->HR->Sales`, and the answer for `Sales` is 1.
- Comparison with `==` is exact. For `string`, `"hr"` does not equal `"HR"`. The edge test shows `indexOf(hr): -1`.

The step to the next node:

```cpp
        curr = curr->next();
        index++;
```

- `curr->next()` is the link to the following node. The assignment moves `curr` one node forward.
- `index++` adds 1, so `index` keeps matching the position of `curr`.
- Both lines run only when the current node does not match.

The last line:

```cpp
    return -1;              // empty list, or not found
```

- The line runs only if the loop ended without a match. This happens for an empty list and for a value that is not in the list.
- The value -1 is not a valid index, so the caller can tell "not found" from a real position.

Memory: the function allocates nothing, so valgrind shows no leak.

## Trace

Call from `main.cpp`: `find(departments, string("HR"));`, which calls `list.indexOf(value)`. The list is `Sales->Marketing->HR->Development`.

| Iteration | `curr` points to | `index` | `curr->getData() == "HR"` | Action |
|---|---|---|---|---|
| 1 | Sales | 0 | false | `curr` moves to Marketing, `index` becomes 1. |
| 2 | Marketing | 1 | false | `curr` moves to HR, `index` becomes 2. |
| 3 | HR | 2 | true | The function returns 2. |

The loop stops at iteration 3. The node Development is never checked.

For `Finance`, no node matches. Four iterations run, `curr` becomes `NULL` after Development, the loop ends and the function returns -1.

The program output is:

```text
Sales->Marketing->HR->Development
indexOf(Sales): 0
indexOf(HR): 2
indexOf(Development): 3
indexOf(Finance): -1
```

## Common mistakes

- Leaving out the final `return -1`. The function then reaches the end without a return value for the not-found case. With `-Wall`, g++ warns about the missing return, and `-Werror` turns the warning into an error: "control reaches end of non-void function [-Werror=return-type]". The program does not compile.
- Returning 0 or `size` for "not found". The expected output shows -1, so the output is wrong.
- Writing `while (curr->next() != NULL)`. The loop never checks the last node, so `indexOf(Development)` returns -1 instead of 3. For an empty list, `curr` is `NULL`, and the loop test reads `curr->next()` through `NULL`. The edge test starts with an empty list: valgrind reports "Invalid read of size 8" and the program stops with a segmentation fault (SIGSEGV).
- Not stopping at the first match, for example by saving the index and continuing the loop. The function then returns the last match. The main test has no duplicates, so it still passes. The edge test expects 1 for `Sales` in `HR->Sales->HR->Sales`, and this version returns 3.
- Starting `index` at 1. Every index that is found is then one too large. The answer for "not found" stays -1.
