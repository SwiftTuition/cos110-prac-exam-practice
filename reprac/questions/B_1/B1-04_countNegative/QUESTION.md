Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# B1-04. Recursion: `BinaryStrings::countNegative` (100)

For this question, implement the function `countNegative` of the class `BinaryStrings` **using recursion**, in the file `B_1.cpp`. All the other functions are given in the other files.

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
+ countNegative(Node<Binary>*): int   <- implement
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

Not on the partial UML in the exam paper: `countNegative` (the target), the `operator<<` functions (not drawn; the exam paper says every class has one), and the `{const}` markers. The real exam's complete UML may add members like these.

## What is given

- `getHead()` returns the first node of the list, or `NULL` for an empty list.
- `next()` returns the next node, or `NULL` after the last node.
- `getData()` returns a reference to the `Binary` stored in the node. So `curr->getData()[0]` is bit 0 of that string, and `curr->getData().getSize()` is its number of bits.
- `Binary(string)`: each `'1'` becomes `true`; every other character becomes `false`. `array[0]` is the leftmost bit.
- `operator<<` for `BinaryStrings` prints `Empty`, or the strings joined by ` -> `, for example `100 -> 0011 -> 1101`. It prints no newline.

## What `countNegative(curr)` must do

In this question bit 0 is a sign bit: 1 means negative, 0 means not negative. A binary string is **negative** when it has at least one bit and its bit 0 is `true` (1).

- It returns the number of negative strings from the node `curr` to the end of the list.
- Example: for the list `100 -> 0011 -> 1101 -> 0101`, `countNegative(getHead())` returns 2.
- If `curr` is `NULL`, return 0. (This also covers an empty list.)
- An empty string (0 bits) has no bit 0. It is not negative. Do not read bit 0 of an empty string.
- Do not change the list or any bit.

## Rules

- You must use recursion. **No loops (`for`, `while`, `do`) and no helper functions. Using either scores 0.** The function must call itself. It may call the given functions. It may not call any other function that you write.
- Your code must compile with `-std=c++98 -Wall -Werror` and must not leak memory.

The `operator<<` functions and the `ExpectedOutput` block apply to this question only. Other questions may print the same class differently.

## Build and upload

1. Open a terminal in the `B_1` folder.
2. Run `make B_1`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `B_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example with a segmentation fault), the mark is 0.
