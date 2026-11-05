# B2-08 Explanation: BinaryStrings copy constructor

## What the function must do

`BinaryStrings(const BinaryStrings& other)` makes a deep copy of `other`: new nodes, holding copies of the same strings, in the same order. The two lists share no node and no bool array, so each destructor frees only its own memory. `size` equals the number of nodes. A copy of an empty list is empty.

## Why a deep copy

The compiler can make a copy constructor by itself, but that one copies the members one by one. It would copy the `head` **pointer**, so both lists would use the same nodes. A change to one list would show in the other, and both destructors would delete the same nodes. That is a double free. In this question you write the copy constructor, so it must copy the nodes.

## How the solution works

```cpp
BinaryStrings::BinaryStrings(const BinaryStrings& other) : head(NULL), size(0) {
```

- `other` is a `const` reference. It must be a reference: a copy constructor that takes its parameter by value would need to call itself to make that parameter.
- The initialiser list sets `head` to `NULL` and `size` to 0 first. A constructor starts with undefined values in its members. For an empty `other`, the loop below never runs, so without this line `head` would keep an undefined value.

```cpp
    Node<Binary>* tail = NULL;
    Node<Binary>* curr = other.head;
```

- `tail` is the last node of the **new** list. It lets the function append each new node in one step, without walking the new list every time.
- `curr` walks `other`. A member function can read the private `head` of another object of the same class.
- `other` is `const`, so `other.head` cannot be changed. The nodes it points to are not `const`, so `curr->getData()` and `curr->next()` can be called.

```cpp
    while (curr != NULL) {
        Node<Binary>* newNode = new Node<Binary>(curr->getData());
```

- The loop runs once for each node of `other`.
- `new Node<Binary>(curr->getData())` makes a new node. The `Node` constructor copies the `Binary` with the `Binary` copy constructor, which copies the bool array. This is the deep copy of the string.

```cpp
        if (tail == NULL) {
            head = newNode;
        } else {
            tail->next() = newNode;
        }
        tail = newNode;
        size++;
        curr = curr->next();
    }
}
```

- `tail == NULL` is true only for the first node. The first new node becomes the head.
- For every later node, the old last node links to it.
- `tail = newNode;` moves the end marker. The new node's link is already `NULL` (set by the `Node` constructor), so the last node of the copy always ends the list.
- `size++` counts the nodes as they are made. `size = other.size;` would also work, but counting keeps `size` correct even if `other.size` were wrong.
- `curr = curr->next();` moves on in `other`.

## Trace

`main.cpp` copies `list` = `000 -> 0011 -> 1101`.

| Iteration | curr (in other) | New node | tail before | Link set | New list | size |
|---|---|---|---|---|---|---|
| 1 | `000` | copy of `000` | `NULL` | `head` = new node | `000` | 1 |
| 2 | `0011` | copy of `0011` | `000` | `000` -> new node | `000 -> 0011` | 2 |
| 3 | `1101` | copy of `1101` | `0011` | `0011` -> new node | `000 -> 0011 -> 1101` | 3 |

After iteration 3, `curr` is `NULL` and the loop ends.

Then `main.cpp` changes the copy: bit 0 of the copy's head becomes 1 (`000` becomes `100`), and `1` is prepended. The original list does not change, because it has its own nodes and arrays. The empty list's copy runs no iteration: `head` stays `NULL` and `size` stays 0.

The output of `main.cpp` is:

```text
list: 000 -> 0011 -> 1101 (size 3)
copy: 000 -> 0011 -> 1101 (size 3)
after changing the copy:
list: 000 -> 0011 -> 1101 (size 3)
copy: 1 -> 100 -> 0011 -> 1101 (size 4)
copy of an empty list: Empty (size 0)
```

## Common mistakes

- **Shallow copy** (`head = other.head; size = other.size;`). Both lists use the same nodes. Changing the copy's head changes the original: `main.cpp` then prints `list: 100 -> 0011 -> 1101` after the change. At the end, both destructors delete the same nodes: valgrind reports `Invalid read of size 8` and `Invalid free() / delete / delete[]`.
- **Copying with `prepend`.** The copy comes out in reverse order: `1101 -> 0011 -> 000`.
- **Not setting `head` and `size` first.** For the empty list, `head` keeps whatever value was left on the stack. In `main.cpp` the line prints `copy of an empty list:  (size 0)` without `Empty`, and valgrind reports `Invalid read of size 8` and `Invalid free()`. The exact messages depend on that left-over value.
- **Sharing the strings.** Because `data` is a `T`, a new node always holds its own copy of the `Binary`, so this cannot happen by accident here. In the HRMS practical, `data` was a `T*`, and copying the pointer shared the data.
- **Walking the new list to its end for each node** (an `append` inside the loop). The result is correct, but each append walks the whole new list. `tail` avoids this.
- **Taking `other` by value** (`BinaryStrings(BinaryStrings other)`). This does not match the declaration in the header. g++ reports `no declaration matches 'BinaryStrings::BinaryStrings(BinaryStrings)'`. A copy constructor must take its parameter by reference.
