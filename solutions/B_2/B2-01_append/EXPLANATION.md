# B2-01 Explanation: List::append

## What the function must do

The function `append` adds one value at the end of a singly linked list. A singly linked list is a chain of nodes. Each node stores a value and a pointer to the next node. The new node must come after the current last node. The order of the other nodes stays the same, and `size` increases by 1.

## How the solution works

A pointer is a variable that holds the address of an object. The operator `->` uses a pointer to reach a member of the object. `NULL` is the value of a pointer that points to nothing. In `List<T>`, `T` is a template type. The compiler replaces `T` with a real type such as `int` or `string`.

The function starts here:

```cpp
template <class T>
void List<T>::append(T value) {
```

The function takes `value` by copy. The next line builds the new node:

```cpp
    Node<T>* newNode = new Node<T>(new T(value));
```

- `new T(value)` allocates a copy of the value on the heap.
- `new Node<T>(...)` allocates the node. The node stores the pointer to that copy.
- The node owns the copy. `~Node()` deletes it, so the function never calls `delete`.
- The given `Node` constructor sets `nextNode` to `NULL`. The new node is therefore a valid last node already.

The first branch handles the empty list:

```cpp
    if (headNode == NULL) {
        headNode = newNode;
        size++;
        return;
    }
```

- The condition `headNode == NULL` is true only when the list has no nodes.
- An empty list has no last node, so the walk below would dereference `NULL`. Dereference means to use `->` on the pointer. In the tests, the program then stops with a segmentation fault (SIGSEGV).
- The assignment `headNode = newNode` makes the new node the first node and the last node.
- `size++` keeps `size` equal to the number of nodes.
- `return` leaves the function, so the walk below does not run.

If the list has at least one node, the function finds the last node:

```cpp
    Node<T>* curr = headNode;
    while (curr->next() != NULL) {
        curr = curr->next();
    }
```

- `curr` starts at the first node. This is safe, because the `if` above ended the function for an empty list.
- `curr->next()` returns the link to the next node. The condition `curr->next() != NULL` asks if another node follows `curr`.
- If a node follows, `curr = curr->next()` moves one step forward.
- The loop stops when `curr->next()` is `NULL`. At that point `curr` is the last node.
- The loop tests `curr->next()` and not `curr`. If the loop tested `curr != NULL`, it would end after the last node. The function would then have no node to link from.
- A list with one node skips the loop body. `curr` stays at the head, which is also the last node.

The last two lines attach the node:

```cpp
    curr->next() = newNode;
    size++;
```

- `next()` returns a reference to the link (`Node<T>*&`). A reference is another name for an existing variable. The assignment therefore changes the real link inside the last node.
- The old last node now points to the new node. The new node still has `NULL` as its link, so it is the new last node.
- `head` does not change. The other nodes do not change.
- `size++` adds 1 for the new node.

Memory: each call allocates two blocks, the node and its value. The destructor of `List` frees both when the list ends. valgrind reports no leak.

## Trace

Call from `main.cpp`: `numbers.append(30);`. Before the call, the list is `10->20` and `size` is 2.

| Step | `curr` points to | `curr->next()` | Action |
|---|---|---|---|
| Setup | node 10 | node 20 | The `if` is false. `newNode` holds 30. `curr = headNode`. |
| Loop test 1 | node 10 | node 20 (not `NULL`) | `curr = curr->next()`, so `curr` is node 20. |
| Loop test 2 | node 20 | `NULL` | The loop stops. |
| After loop | node 20 | `NULL` | `curr->next() = newNode`. The chain is `10->20->30`. |
| End | node 20 | node 30 | `size++`, so `size` is 3. |

The earlier calls in `main.cpp` use the other branch. `numbers.append(10)` runs on an empty list. The `if` is true, so `headNode` becomes the new node and the function returns. The call `numbers.append(20)` then walks from node 10, which is the last node already, and links node 20 after it.

The program output is:

```text
Empty List (size 0)
10 (size 1)
10->20->30 (size 3)
5->10->20->30->40 (size 5)
```

## Common mistakes

- Walking with `while (curr != NULL)` and then writing to `curr->next()`. After the loop, `curr` is `NULL`. The write dereferences `NULL`. In the main test, the second call (`append(20)`) does this. valgrind reports "Invalid write of size 8" and the program stops with a segmentation fault (SIGSEGV).
- Leaving out the check `headNode == NULL`. The first call on an empty list reads `curr->next()` while `curr` is `NULL`. valgrind reports "Invalid read of size 8" and the program stops with SIGSEGV. Both the main test and the edge test start with an empty list, so both fail.
- Forgetting `size++` on one of the two paths. The list prints correctly, but the text `(size N)` shows the wrong number.
- Building the node with `new Node<T>(&value)`. `value` is a local variable, so the node keeps the address of a variable that stops existing when `append` returns. That is undefined behaviour. In the test, the printed values are wrong (every appended node showed the same number), and `~Node()` deletes a stack address, so valgrind reports "Invalid free() / delete / delete[] / realloc()".
- Setting `headNode = newNode` in the non-empty case. The old nodes become unreachable, so the list loses its values. In the main test, the list prints only `30` and then `40`, and valgrind reports "definitely lost: 48 bytes in 3 blocks". In the edge test, `names.head()->next()` is `NULL`, so the test reads through `NULL` and stops with SIGSEGV.
