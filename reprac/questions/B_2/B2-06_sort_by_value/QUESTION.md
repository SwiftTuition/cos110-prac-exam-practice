Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# B2-06. Linked lists: `BinaryStrings::sort` by decimal value (100)

For this question, implement the function `sort` of the class `BinaryStrings` in the file `B_2.cpp`. It sorts the binary strings by their decimal value, smallest first. All the other functions are given in the other files.

## UML (only the classes this question needs)

```text
BinaryStrings
- head: Node<Binary>*
- size: int
+ BinaryStrings()
+ ~BinaryStrings()
+ prepend(const Binary&): void
+ getHead(): Node<Binary>*&
+ calculatePos(): int
+ getSize(): int
+ sort(): void   <- implement
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

Not on the partial UML in the exam paper: `sort` (the target), `BinaryStrings::getSize` (added so that the tests can print `size`), the `operator<<` functions (not drawn; the exam paper says every class has one), and the `{const}` markers. The real exam's complete UML may add members like these.

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
- `operator=` of `Binary`, and the copy constructor and `operator=` of `BinaryStrings`, are private and not defined in this question. Do not use them.

## What `sort()` must do

The decimal value of a string reads the bits as an unsigned binary number, with `array[0]` (the leftmost bit) as the most significant bit. So `0101` is 5, `11` is 3, `011` is 3, `1000` is 8, and `0` and the empty string are 0.

- After the call, the values are in ascending order (smallest at the head).
- Strings with **equal** values keep their original order. Example: `11` comes before `011` if it was before `011` in the list.
- Move whole nodes by changing the links (`next()` of the nodes and `head`). Do not create new nodes and do not delete nodes. The marking program checks that the same nodes are still used.
- Do not swap the data between nodes. `Binary` has no usable `operator=` here, because it is private.
- The last node's `next()` must be `NULL` after the sort.
- `size` does not change. An empty list and a list with one node stay the same.
- The tests use strings of at most 31 bits, so each value fits in an `int`.
- Example: `0101 -> 11 -> 1000 -> 011 -> 0` becomes `0 -> 11 -> 011 -> 0101 -> 1000`.

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
