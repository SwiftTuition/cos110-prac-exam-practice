Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# B1-06. Recursion: `BinaryStrings::printReverse` (100)

For this question, implement the function `printReverse` of the class `BinaryStrings` **using recursion**, in the file `B_1.cpp`. All the other functions are given in the other files.

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
+ printReverse(Node<Binary>*): void   <- implement
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

Not on the partial UML in the exam paper: `printReverse` (the target), the `operator<<` functions (not drawn; the exam paper says every class has one), and the `{const}` markers. The real exam's complete UML may add members like these.

## What is given

- `getHead()` returns the first node of the list, or `NULL` for an empty list.
- `next()` returns the next node, or `NULL` after the last node.
- `getData()` returns a reference to the `Binary` stored in the node.
- `operator<<` for a `Binary` prints its bits, for example `0011`. An empty string prints nothing. It prints no newline.
- `operator<<` for `BinaryStrings` prints `Empty`, or the strings joined by ` -> `, for example `000 -> 0011 -> 1101`.

## What `printReverse(curr)` must do

It prints the strings from the **last** node of the list back to the node `curr`.

- Print each string with `cout`, followed by `endl`. So each string is on its own line, and nothing else is printed. An empty string gives an empty line.
- Example: for the list `000 -> 0011 -> 1101 -> 0101`, `printReverse(getHead())` prints `0101`, `1101`, `0011` and `000`, each on its own line.
- If `curr` is `NULL`, print nothing. (This also covers an empty list.)
- Do not change the list.

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
