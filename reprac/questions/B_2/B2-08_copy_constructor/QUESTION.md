Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# B2-08. Linked lists: `BinaryStrings` copy constructor (100)

For this question, implement the copy constructor of the class `BinaryStrings` in the file `B_2.cpp`. It makes a deep copy of a list. All the other functions are given in the other files.

## UML (only the classes this question needs)

```text
BinaryStrings
- head: Node<Binary>*
- size: int
+ BinaryStrings()
+ BinaryStrings(const BinaryStrings&)   <- implement
+ ~BinaryStrings()
+ prepend(const Binary&): void
+ getHead(): Node<Binary>*&
+ calculatePos(): int
+ getSize(): int
+ operator<<(ostream&, const BinaryStrings&): ostream&   {friend}

Node<T>
- data: T
- nextNode: Node<T>*
+ Node(T)
+ ~Node()
+ getData(): T&
+ next(): Node<T>*&

Binary
- array: bool*
- size: int
+ Binary(string)
+ Binary(const Binary&)
+ ~Binary()
+ operator[](int): bool&
+ operator[](int): const bool&   {const}
+ getSize(): int   {const}
+ operator<<(ostream&, const Binary&): ostream&   {friend}
```

Not on the partial UML in the exam paper: the copy constructor (the target), `BinaryStrings::getSize` (added so that the tests can print `size`), the `operator<<` functions (not drawn; the exam paper says every class has one), and the `{const}` markers. The real exam's complete UML may add members like these.

## What is given

- `Node<T>` stores its own **copy** of the data (`data: T`, not `T*`). `new Node<Binary>(b)` makes a node that holds a copy of `b`. The copy is made by the `Binary` copy constructor.
- `~Node()` is empty. It does **not** delete the next node. When a node is deleted, the `Binary` inside it is destroyed too, and that frees its bool array. So `delete curr;` is all that is needed to free one node and its string.
- `next()` returns a reference to the pointer to the next node (the link), so `curr->next() = ...;` changes the link.
- `getData()` returns a reference to the `Binary` in the node. `curr->getData()[i]` is bit `i` of that string, and `curr->getData().getSize()` is its number of bits.
- `prepend(b)` puts a new node at the front and adds 1 to `size`.
- The destructor `~BinaryStrings()` deletes every node.
- `size` must always equal the number of nodes. `getSize()` returns it.
- `operator<<` prints `Empty`, or the strings joined by ` -> `, for example `000 -> 0011 -> 1101`. It prints no newline. An empty string prints nothing. For example, a list of `0101`, an empty string and `11` prints as follows (two spaces between the arrows):

  ```text
  0101 ->  -> 11
  ```

- `Binary(string)`: each `'1'` becomes `true`; every other character becomes `false`. `array[0]` is the leftmost bit.
- Inside `BinaryStrings` you can use `head` and `size` directly.
- `operator=` of `Binary` and `operator=` of `BinaryStrings` are private and not defined in this question. Do not use them.

## What `BinaryStrings(const BinaryStrings& other)` must do

- Make a **deep copy**: the new list has its own new nodes, one for each node of `other`, holding copies of the same strings in the **same order**.
- The two lists share no node and no bool array. A change to one list (a bit, a new node) must not change the other. Each list's destructor deletes only its own nodes.
- `size` of the new list equals the number of nodes.
- A copy of an empty list is empty: `head` is `NULL` and `size` is 0.
- The last node's `next()` must be `NULL`.
- Remember to set `head` and `size` first. A constructor starts with undefined values in its members.
- `prepend` adds at the front, so copying with `prepend` alone gives the reverse order.
- The copy constructor is also called when a `BinaryStrings` is passed **by value**.

## Rules

- C++98 only: use `NULL`. Do not use `nullptr`, `auto` or `to_string`.
- Your code must compile with `-std=c++98 -Wall -Werror`. A warning stops the build.
- Memory is marked. valgrind must show no errors and no leaks.
- You may not change any header, so write everything in `B_2.cpp`. A small helper function in `B_2.cpp` is allowed. The ban on helpers applies only to the B_1 recursion questions. Make it `static` so that its name stays inside `B_2.cpp`. In the exam, follow the question text.

The `operator<<` functions and the `ExpectedOutput` block apply to this question only. Other questions may print the same class differently.

## Build and upload

1. Open a terminal in the `B_2` folder.
2. Run `make B_2`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `B_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example with a segmentation fault), the mark is 0.
