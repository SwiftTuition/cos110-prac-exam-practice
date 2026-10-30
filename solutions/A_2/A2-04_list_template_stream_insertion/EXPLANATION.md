# A2-04 Explanation: template operator<< for List<T>

## What the function must do

The function prints a linked list of any value type `T`. The values appear in order from the head node to the last node, with `->` between two values.

An empty list prints the text `Empty List`. The function prints no `->` after the last value and no newline.

## How the solution works

```cpp
template <class T>
ostream& operator<<(ostream& out, const List<T>& list) {
    if (list.headNode == NULL) {
        out << "Empty List";
        return out;
    }
    Node<T>* curr = list.headNode;
    // Stop at the last node, so that no "->" is printed after it.
    while (curr->next() != NULL) {
        out << curr->getData() << "->";
        curr = curr->next();
    }
    out << curr->getData();
    return out;
}
```

**The template line.** `template <class T>` makes the function a template. The compiler writes one real function for each type `T` that the program uses. In `main.cpp`, `T` is `int` and `string`. The same text works for both, because `out << curr->getData()` uses the `operator<<` of the value type.

The `List.h` file already declares the function and contains the `friend` line with `<>`. The definition in `A_2.cpp` has no `<>` and no `friend`. The file keeps its include guard, and the code stays between `#define A_2_CPP` and `#endif`.

**Parameters.** `out` is a reference to the output stream. `list` is a `const` reference to the list, so the function reads the list but does not change it. The function is a friend, so it may read the private member `list.headNode`.

**The empty check.** `if (list.headNode == NULL)` checks whether the list has any node. A pointer holds the address of an object. `NULL` means the pointer holds no address. An empty list has `headNode` equal to `NULL`.

- If the check is true, the function prints `Empty List` and returns `out` at once.
- The check must come first. The later line `curr->next()` follows `curr`. If `curr` were `NULL`, this would follow a `NULL` pointer, which is undefined behaviour.

**The walking pointer.** `Node<T>* curr = list.headNode;` copies the head pointer into a new pointer `curr`. The function moves `curr` along the list. The pointer `list.headNode` stays unchanged. The parameter `list` is `const`, so the function must not change `list.headNode`.

**The loop condition.** `while (curr->next() != NULL)` is true while the current node has a next node. The function `next()` returns the pointer to the next node. After the last node, `next()` returns `NULL`.

- The loop stops on the last node, not after it. The last node is therefore not printed inside the loop.
- This is the reason that the function prints no `->` after the last value. Each loop pass prints a value and `->`, because another value always follows.
- If the list has one node, the condition is false at once. The loop body never runs.

**Loop body.** `out << curr->getData() << "->";` prints the value in the current node, then the arrow. `getData()` returns a reference to the stored value. The next line `curr = curr->next();` moves `curr` to the next node. The move happens after the print, so the function prints the current node before it leaves it.

**After the loop.** `out << curr->getData();` prints the last node. At this point `curr` points to the last node, because the loop stopped there. The function adds no arrow and no newline. `return out;` returns the stream for chaining.

The function allocates nothing. The `List` destructor frees the nodes, and each `Node` destructor frees its data.

## Trace

The call is `cout << numbers << endl;` in `main.cpp`. The calls `prepend(3)`, `prepend(2)` and `prepend(1)` put each new node at the front. The list is then:

```text
headNode -> [1] -> [2] -> [3] -> NULL
```

| Step | `curr` points to | `curr->next() != NULL` | Output added | `curr` after |
|---|---|---|---|---|
| Start | node 1 | not applicable | none (`headNode` is not `NULL`) | node 1 |
| Loop pass 1 | node 1 | true (next is node 2) | `1->` | node 2 |
| Loop pass 2 | node 2 | true (next is node 3) | `2->` | node 3 |
| Loop test | node 3 | false (next is `NULL`) | none | node 3 |
| After the loop | node 3 | not applicable | `3` | node 3 |

The function returns `out`. Then `main` prints `endl`. For the empty list `numbers` that `main` prints first, the check `list.headNode == NULL` is true and the output is `Empty List`.

The ExpectedOutput of `main.cpp` is:

```text
Empty List
1->2->3
Thandi->Sipho (size 2)
```

## Common mistakes

1. **Printing `->` after the last value.** A loop of the form `while (curr != NULL)` that prints a value and an arrow on each pass gives `1->2->3->`. The output of `main` then differs from the expected output.
2. **Skipping the empty check.** For an empty list, `curr` is `NULL`. The call `curr->next()` then dereferences `NULL`. This is undefined behaviour. In `main`, the first print is the empty list `numbers`. Valgrind reports `Invalid read of size 8`, and the program stops with a segmentation fault (`SIGSEGV`) before it prints anything.
3. **Writing to `cout` instead of `out`.** The edge test sends two lists to an `ostringstream`. Text sent to `cout` never reaches it. The output of the edge test then differs from the expected output.
4. **Changing the file layout.** The question states that `A_2.cpp` already has `#include "List.h"`. An added `#include "List.cpp"`, or code after `#endif`, gives a redefinition error. A compile error gives the mark 0.
