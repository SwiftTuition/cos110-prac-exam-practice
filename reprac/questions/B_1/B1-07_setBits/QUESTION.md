Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# B1-07. Recursion: `Binary::setBits` (100)

For this question, implement the function `setBits` of the class `Binary` **using recursion**, in the file `B_1.cpp`. The given constructor `Binary(string)` calls your function to fill the bool array. All the other functions of `Binary` are given in `Binary.cpp`.

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
+ setBits(string, int): void   <- implement
+ operator<<(ostream&, const Binary&): ostream&   {friend}
```

Not on the partial UML in the exam paper: `setBits` (the target), `operator<<` (not drawn; the exam paper says every class has one), and the `{const}` markers. The real exam's complete UML may add members like these.

## What is given

- The constructor (in `Binary.cpp`):
  ```cpp
  Binary::Binary(string bits) {
      size = (int)bits.length();
      array = new bool[size];
      setBits(bits, 0);
  }
  ```
  So every `Binary` object in `main.cpp` is filled by your `setBits`. The array already exists when `setBits` is called. Do not create or delete it.
- `operator<<` prints the bits from index 0 to the end, for example `1011`. It prints no newline.
- `operator=` is private and not defined in this question. Do not assign one `Binary` to another.
- Inside `Binary` you can use `array` and `size` directly.

## What `setBits(bits, index)` must do

It sets `array[index]`, `array[index + 1]`, and so on, from the characters at the **same positions** in `bits`.

- A `'1'` gives `true`. Every other character gives `false`.
- It stops when `index` reaches `size` or `bits.length()`, the smaller of the two. Bits after that keep their old values.
- Bits before `index` keep their old values.
- Examples: for a `Binary` that holds `0000`, `setBits("11", 0)` gives `1100`. Then `setBits("0110", 2)` gives `1110` (only bits 2 and 3 change). `setBits("111111", 0)` gives `1111` (the string is longer than the array).
- Invalid input: if `index` is less than 0, change nothing.
- `bits.length()` is unsigned. Under `-Wall -Werror`, comparing it with an `int` stops the build. Cast it: `(int)bits.length()`.

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
