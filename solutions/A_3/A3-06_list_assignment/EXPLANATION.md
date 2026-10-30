# A3-06 Explanation: List<T>::operator=

## What the function must do

The statement `a = b;` must make list `a` hold new nodes with copies of the values of list `b`, in the same order. The function first deletes the old nodes of `a`. The function then builds a new chain of nodes, one node for each node in `b`. After the call, `a` and `b` share no node and no data, and `size` equals the size of `b`.

## How the solution works

`List<T>` is a **class template**. The name `T` is a template parameter: a placeholder for the type of the stored values, such as `int` or `string`. The compiler creates a separate version of the code for each type that the program uses.

A list has `Node<T>* headNode` (a pointer to the first node, or `NULL` for an empty list) and `int size`. Each `Node<T>` has `T* data` (a pointer to the value) and `Node<T>* nextNode` (a pointer to the next node). A node owns its `data`: `~Node()` deletes `data`, but does not delete the next node.

```cpp
template <class T>
List<T>& List<T>::operator=(const List<T>& other) {
```

The first line says that the function is a template. `T` is the type of the values. The parameter `other` is a reference to the right-hand list. The word `const` means the function does not change `other`. The function returns `List<T>&`, a reference to the left-hand list.

```cpp
    if (this == &other) {
        return *this;
    }
```

`this` is a pointer to the current list. `&other` is the address of the right-hand list. The condition is true for `a = a;`. The check must come first, because the next step deletes the nodes that `other` would supply. In `a = a`, `other` is the current list itself. Without the check, the function deletes every node and sets `headNode` to `NULL`. Then `other.headNode` is `NULL` too, because `other` is the same object. The copy loop does not run, and the list becomes empty. If the condition is true, the function returns `*this` (the current list) and changes nothing.

```cpp
    Node<T>* curr = headNode;
    while (curr != NULL) {
        Node<T>* temp = curr;
        curr = curr->next();
        delete temp;
    }
    headNode = NULL;
    size = 0;
```

This step frees the old nodes. `curr` points at the node that the loop visits. The condition `curr != NULL` stops the loop after the last node. An empty list has `headNode` equal to `NULL`, so the loop does not run, and the function does not dereference `NULL`.

Inside the loop, the order of the three lines matters. `temp = curr` saves the current node. `curr = curr->next()` moves `curr` to the next node. `delete temp` then deletes the saved node and its data. The function must move `curr` before it deletes. If the function deleted the node first, `curr->next()` would read a deleted node.

After the loop, every old node is gone, but `headNode` still holds the address of the first deleted node. The line `headNode = NULL;` removes this pointer to freed memory. The line `size = 0;` makes the list empty. The copy step starts with an empty list.

```cpp
    Node<T>* tail = NULL;
    Node<T>* otherCurr = other.headNode;
```

`tail` points at the last node of the new chain. It starts as `NULL` because the new chain has no node. `otherCurr` points at the node of `other` that the loop visits. The function reads `other.headNode` directly. A member function of `List<T>` is allowed to read the private members of another `List<T>`.

```cpp
    while (otherCurr != NULL) {
        Node<T>* newNode = new Node<T>(new T(otherCurr->getData()));
```

The condition `otherCurr != NULL` stops the loop after the last node of `other`. If `other` is empty, the loop does not run, and the current list stays empty. `otherCurr->getData()` gives the value of the node. `new T(...)` creates a new value from a copy of it. `new Node<T>(...)` creates a new node that owns this new value. The new node does not share the value with `other`.

```cpp
        if (tail == NULL) {
            headNode = newNode;
        } else {
            tail->next() = newNode;
        }
        tail = newNode;
        size++;
        otherCurr = otherCurr->next();
    }
```

The `if` handles the first node. If `tail == NULL`, the chain has no node yet, so the new node becomes `headNode`. Otherwise, `tail->next() = newNode;` links the new node after the last node. The function `next()` returns a reference to `nextNode`, so the assignment changes the real pointer. The line `tail = newNode;` makes the new node the last node. `size++` counts the node. `otherCurr = otherCurr->next();` moves to the next node of `other`.

The function adds each new node at the end. This keeps the order of `other`. The function `prepend` adds at the front. A loop that calls `prepend` while it walks from the head would reverse the order.

```cpp
    return *this;
}
```

The function returns the current list. For `a = b = c;`, C++ runs `b = c` first, and then `a = b`.

## Trace

The call is `a = b;` from `main.cpp`. Before the call, `a` is `9` with size 1. List `b` is `1->2->3` with size 3. The new nodes are `1'`, `2'` and `3'`.

| Step | Code | `curr` or `otherCurr` | `tail` | `headNode` of `a` | `size` |
|---|---|---|---|---|---|
| Before | none | none | none | `9` | 1 |
| 1 | `this == &other`: the addresses differ, so the condition is false | none | none | `9` | 1 |
| 2 | delete loop: `temp` saves node `9`, `curr` becomes `NULL`, `delete temp` frees node `9` and its data; the loop ends | `curr` is `NULL` | none | freed | 1 |
| 3 | `headNode = NULL; size = 0;` | none | none | `NULL` | 0 |
| 4 | `tail = NULL;` and `otherCurr` points at node `1` of `b` | `1` | `NULL` | `NULL` | 0 |
| 5 | copy loop, round 1: `newNode` is `1'`; `tail == NULL`, so `headNode = newNode`; `tail = 1'`; `size++` | `2` (after the move) | `1'` | `1'` | 1 |
| 6 | round 2: `newNode` is `2'`; `tail` is not `NULL`, so `tail->next() = newNode`; `tail = 2'`; `size++` | `3` | `2'` | `1'->2'` | 2 |
| 7 | round 3: `newNode` is `3'`; `tail->next() = newNode`; `tail = 3'`; `size++` | `NULL` | `3'` | `1'->2'->3'` | 3 |
| 8 | `otherCurr != NULL` is false; the loop ends; `return *this;` | `NULL` | `3'` | `1'->2'->3'` | 3 |

The nodes of `b` do not change. When `main.cpp` runs `b.prepend(0)`, only `b` gets a new node. List `a` stays `1->2->3`.

The output of `main.cpp` is:

```text
a: 9 (size 1)
b: 1->2->3 (size 3)
a after a = b: 1->2->3 (size 3)
b after b.prepend(0): 0->1->2->3 (size 4)
a has not changed: 1->2->3 (size 3)
```

## Common mistakes

- **Copy with `prepend`.** A loop that calls `prepend(otherCurr->getData())` while it walks from the head adds every value at the front. The list prints `3->2->1`, and the expected output shows `1->2->3`. The output then differs from the expected output.
- **Delete a node, then read `next()`.** The code `delete curr; curr = curr->next();` reads a deleted node. Valgrind reports "Invalid read of size 8". The solution saves the node in `temp` first.
- **Forget `headNode = NULL;` and `size = 0;`.** The old size stays, and `size++` adds to it. In `main.cpp`, list `a` prints `(size 4)` instead of `(size 3)`. When `other` is empty, `headNode` also keeps the address of a deleted node. In the edge test (test 4, `y = empty`), the list prints a value from a deleted node, and valgrind reports "Invalid read of size 8" and "Invalid free() / delete / delete[]".
- **Link the nodes of `other` instead of new nodes.** The code `tail->next() = otherCurr;` makes the two lists share nodes. Both destructors then delete the same nodes, and valgrind reports invalid frees. The code `new Node<T>(new T(otherCurr->getData()))` makes a new node with its own value.
- **No self-assignment check.** For `x = x;`, the function deletes all the nodes and sets `headNode` to `NULL`. Because `other` is the same list, the copy loop finds no node to copy. Valgrind reports no error, but the list is now empty. Test 1 prints `1. x = x: Empty List (size 0)` instead of `5->6 (size 2)`.
