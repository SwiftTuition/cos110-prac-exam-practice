Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# B1-05. Recursion: `BinaryStrings::calculatePos` with a node and a bit index (100)

For this question, implement the function `calculatePos` of the class `BinaryStrings` **using recursion**, in the file `B_1.cpp`. All the other functions are given in the other files.

This question changes the UML on purpose. The partial UML in the exam paper shows `calculatePos(): int` with no parameters. A function with no parameters has nothing to change from one call to the next, so it cannot walk the list by recursion. Here `calculatePos` takes the node to start from and the bit to check. The no-parameter version is not in this question. If the exam keeps it and allows a helper, this same body goes in the helper, and `calculatePos()` calls it once.

## UML (only the classes this question needs)

```text
BinaryStrings
- head: Node<Binary>*
- size: int
+ BinaryStrings()
+ ~BinaryStrings()
+ prepend(const Binary&): void
+ getHead(): Node<Binary>*&
+ calculatePos(Node<Binary>*, int): int   <- implement
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

Not on the partial UML in the exam paper: the two parameters of `calculatePos` (see above), the `operator<<` functions (not drawn; the exam paper says every class has one), and the `{const}` markers. The exam paper does not say what "Pos" means. In this question it means "positive", as defined below. The real exam's complete UML and question text decide.

## What is given

- `getHead()` returns the first node of the list, or `NULL` for an empty list.
- `next()` returns the next node, or `NULL` after the last node.
- `getData()` returns a reference to the `Binary` stored in the node. So `curr->getData()[i]` is bit `i` of that string, and `curr->getData().getSize()` is its number of bits.
- `Binary(string)`: each `'1'` becomes `true`; every other character becomes `false`. `array[0]` is the leftmost bit.
- `operator<<` for `BinaryStrings` prints `Empty`, or the strings joined by ` -> `. It prints no newline.

## What `calculatePos(curr, index)` must do

Bit 0 is a sign bit. A binary string is **positive** when bit 0 is `false` (0) **and** at least one other bit is `true` (1). So `0011` is positive. `000` (zero), `1101` (negative), `0`, `1` and the empty string are not positive.

- It returns the number of positive strings from the node `curr` to the end of the list.
- `index` is the bit of `curr` that this call checks. The first call is `calculatePos(getHead(), 1)`. The bits of `curr` before `index` are not checked again.
- When the function moves to the next node, it starts again at bit 1 of that node.
- Example: for `000 -> 0011 -> 1101 -> 0101`, `calculatePos(getHead(), 1)` returns 2.
- If `curr` is `NULL`, return 0. (This also covers an empty list.)
- Invalid input: if `index` is less than 1, return 0.
- If `index` is greater than or equal to the number of bits of `curr`'s string, the check has passed the last bit without finding a 1. This string is not positive. Continue with the next node, at bit 1.
- If bit `index` is `true` and bit 0 is `false`, count this string once and continue with the next node, at bit 1.
- If bit `index` is `false`, check the next bit of the same string: `index + 1`.
- Never read a bit outside a string. An empty string has no bit 0.
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
