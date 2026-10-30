# B2-11 Explanation: List copy constructor

## What the function must do

The copy constructor builds a new list from an existing list `other`. The new list is a deep copy. A deep copy has its own new nodes, and each new node holds its own new copy of the value. The new list has the same values in the same order and the same `size`. The two lists share nothing, so a change to one list does not change the other. Copying an empty list gives an empty list.

## How the solution works

A pointer is a variable that holds the address of an object. The operator `->` uses a pointer to reach a member. `NULL` means the pointer points to nothing. `T` is the template type. A constructor runs when an object is created. In `List<int> copy(original);`, the compiler calls the copy constructor with `original` as `other`. The compiler also calls it when a list is passed to a function by value. The type `const List<T>&` is a reference to a list that the constructor must not change.

The constructor starts here:

```cpp
template <class T>
List<T>::List(const List<T>& other) : headNode(NULL), size(0) {
```

- The part after the colon is the initializer list. It sets `headNode` to `NULL` and `size` to 0 before the body runs.
- A new object has no values in its members yet. Without these initial values, `headNode` and `size` hold unknown data. The body then adds to a wrong `size`, and an empty copy has an unknown head.
- With these values, the new list is a valid empty list. The body only needs to add nodes.

Two pointers support the loop:

```cpp
    Node<T>* tail = NULL;              // last node of the new list
    Node<T>* curr = other.headNode;
```

- `tail` points to the last node of the new list. The new list is empty, so `tail` is `NULL`.
- `curr` points to the node of `other` that the loop copies. It starts at the first node of `other`.
- The constructor may read `other.headNode` directly, because `other` has the same class. The constructor does not change `other`.
- The function keeps `tail` so that it does not need to walk the new list again for each new node.

The loop:

```cpp
    while (curr != NULL) {
```

- The condition `curr != NULL` is true while `other` has a node left to copy.
- For an empty `other`, `curr` is `NULL` at the start. The body never runs, and the new list stays empty with `size` 0.

The new node:

```cpp
        Node<T>* newNode = new Node<T>(new T(curr->getData()));
```

- `curr->getData()` returns the value of the old node.
- `new T(curr->getData())` allocates a new value and copies the old value into it.
- `new Node<T>(...)` allocates a new node that owns this new value.
- The old node and the new node therefore share no memory. This is the deep copy.

The link step has two cases:

```cpp
        if (tail == NULL) {
            headNode = newNode;        // first node of the copy
        } else {
            tail->next() = newNode;    // link after the current last node
        }
```

- The test `tail == NULL` is true only for the first node. The copy has no last node yet, so `headNode` must point to the new node.
- For later nodes, `tail` is the current last node. `tail->next() = newNode` links the new node after it. The reference returned by `next()` lets the assignment change the real link.
- Appending in this way keeps the order of `other`. The new node's own link is `NULL` from the `Node` constructor, so the new last node ends the chain.

The updates at the end of each pass:

```cpp
        tail = newNode;
        size++;
        curr = curr->next();
```

- `tail = newNode` makes the new node the last node. The next pass links after it.
- `size++` counts the new node. The copy ends with the same `size` as `other`.
- `curr = curr->next()` moves to the next node of `other`.

Memory: each pass allocates one node and one value. The destructor of the new list frees them. The destructor of `other` frees the old ones. The two destructors free different memory, so valgrind shows no error.

## Trace

Call from `main.cpp`: `List<int> copy(original);`. The list `original` is `1->2->3`.

| Step | `curr` (in `original`) | `tail` (in `copy`) | Action | `copy` after the step | `size` |
|---|---|---|---|---|---|
| Setup | node 1 | `NULL` | `headNode` is `NULL`, `size` is 0. | empty | 0 |
| Pass 1 | node 1 | `NULL` | New node with 1. `tail == NULL`, so `headNode` points to it. | `1` | 1 |
| Pass 2 | node 2 | node 1 (copy) | New node with 2. `tail->next()` points to it. | `1->2` | 2 |
| Pass 3 | node 3 | node 2 (copy) | New node with 3. `tail->next()` points to it. | `1->2->3` | 3 |
| End | `NULL` | node 3 (copy) | The loop test is false. | `1->2->3` | 3 |

After the copy, `original.prepend(0)` changes only `original`, and `copy.prepend(9)` changes only `copy`. The two lists use different nodes.

The program output is:

```text
original: 1->2->3 (size 3)
copy:     1->2->3 (size 3)
original: 0->1->2->3 (size 4)
copy:     9->1->2->3 (size 4)
```

## Common mistakes

- Copying only the pointer, for example `headNode = other.headNode; size = other.size;`. This is a shallow copy. Both lists use the same nodes. When both destructors run, the same nodes are deleted twice. The main test still prints the expected lines, but valgrind reports "Invalid read of size 8" and "Invalid free() / delete / delete[] / realloc()". The edge test also checks `one.head() != oneCopy.head()` and prints `no`, but it expects `yes`.
- Building the copy with `prepend` inside the loop. The copy is then in reverse order, for example `3->2->1`. The output is wrong.
- Forgetting `size++`. The values are copied, but the printed size is wrong. The main test prints `copy:     1->2->3 (size 0)`.
- Leaving out the initializer list `headNode(NULL), size(0)`. The values of `headNode` and `size` are then unknown. Using them is undefined behaviour. In the main test, the copy printed a wrong size (a large number such as 73731), and valgrind reported "Conditional jump or move depends on uninitialised value(s)". A copy of an empty list also keeps the unknown `headNode`, so printing or destroying it uses an unknown address. The edge test copies an empty list.
- Not updating `tail`. Then `tail` stays `NULL`, so every pass sets `headNode = newNode`. The copy keeps only the last node, and the earlier nodes are lost. The main test prints `copy:     3 (size 3)`, and valgrind reports "definitely lost".
- Looping with `while (curr->next() != NULL)`. The loop skips the last value of `other`, so the copy is one node short. For an empty `other`, `curr` is `NULL`, and the loop test reads `curr->next()` through `NULL`. The edge test starts by copying an empty list: valgrind reports "Invalid read of size 8" and the program stops with a segmentation fault (SIGSEGV).
