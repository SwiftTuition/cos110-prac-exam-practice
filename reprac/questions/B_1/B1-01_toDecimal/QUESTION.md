Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# B1-01. Recursion: `Binary::toDecimal` (100)

For this question, implement the function `toDecimal` of the class `Binary` **using recursion**, in the file `B_1.cpp`. All the other functions of `Binary` are given in `Binary.cpp`.

## UML (only the class this question needs)

```text
Binary
- array: bool*
- size: int
+ Binary(string)
+ Binary(const Binary&)
+ ~Binary()
+ operator[](int): bool&
+ operator[](int): const bool&   {const}
+ getSize(): int   {const}
+ toDecimal(int): int   <- implement
+ operator<<(ostream&, const Binary&): ostream&   {friend}
```

Not on the partial UML in the exam paper: `toDecimal` (the target), `operator<<` (not drawn; the exam paper says every class has one), and the `{const}` markers. The real exam's complete UML may add members like these.

## What is given

- `Binary(string)` sets `size` to the length of the string and creates `array` with `new bool[size]`. Each `'1'` becomes `true`. Every other character becomes `false`.
- `array[0]` holds the **leftmost** character of the string. In this question it is the most significant bit.
- `operator<<` prints the bits from index 0 to the end, for example `1011`. It prints no newline.
- `operator=` is private and not defined in this question. Do not assign one `Binary` to another.
- Inside `Binary` you can use `array` and `size` directly.

## What `toDecimal(index)` must do

It returns the decimal (base 10) value of the bits from index 0 up to **and including** `index`, read as an unsigned binary number.

- Example: for `1011`, `toDecimal(3)` returns 11 (the whole string), `toDecimal(1)` returns 2 (the bits `10`) and `toDecimal(0)` returns 1 (the bit `1`).
- To get the value of the whole string, call `toDecimal(getSize() - 1)`.
- Invalid input: if `index` is less than 0, or `index` is greater than or equal to `size`, return 0.
- Do not change any bit.
- The tests use at most 31 bits, so the value fits in an `int`.

Hint: the value of the bits up to `index` is two times the value of the bits up to `index - 1`, plus the bit at `index` (1 or 0). When `index` reaches -1, no bits are left and the value is 0.

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
