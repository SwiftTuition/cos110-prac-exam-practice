Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# B1-03. Recursion: `Binary::isPalindrome` (100)

For this question, implement the function `isPalindrome` of the class `Binary` **using recursion**, in the file `B_1.cpp`. All the other functions of `Binary` are given in `Binary.cpp`.

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
+ isPalindrome(int, int): bool   <- implement
+ operator<<(ostream&, const Binary&): ostream&   {friend}
```

Not on the partial UML in the exam paper: `isPalindrome` (the target), `operator<<` (not drawn; the exam paper says every class has one), and the `{const}` markers. The real exam's complete UML may add members like these.

## What is given

- `Binary(string)` sets `size` to the length of the string and creates `array` with `new bool[size]`. Each `'1'` becomes `true`. Every other character becomes `false`.
- `array[0]` holds the leftmost character of the string.
- `operator<<` prints the bits from index 0 to the end, for example `1001`. It prints no newline.
- `operator=` is private and not defined in this question. Do not assign one `Binary` to another.
- Inside `Binary` you can use `array` and `size` directly.

## What `isPalindrome(start, end)` must do

A palindrome reads the same from left to right and from right to left. The function checks the bits from index `start` to index `end`, both included.

- It returns `true` if the bits in that range form a palindrome, and `false` if they do not.
- Examples: `1001` with `(0, 3)` gives `true`. `1011` with `(0, 3)` gives `false`. `1011` with `(0, 2)` checks `101` and gives `true`.
- A range with one bit (`start` equals `end`) or with no bits (`start` is greater than `end`) is a palindrome: return `true`.
- Invalid input: if `start` is less than 0, or `end` is greater than or equal to `size`, return `false`. Check this before anything else.
- Do not change any bit.

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
