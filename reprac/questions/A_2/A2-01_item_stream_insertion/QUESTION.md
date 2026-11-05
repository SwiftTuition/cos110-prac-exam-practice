Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A2-01. Operator overloading: `operator<<` for `Item` (100)

For this question, implement the stream insertion operator `operator<<` for the `Item` class in the file `A_2.cpp`. It is a `friend` function of `Item`. It prints one item on the stream it is given.

## UML (only the classes this question needs)

```text
Item
- type: char
- name: string
- price: float
+ Item(char, string, float)
+ Item(const Item&)
+ ~Item()
+ getType(): char   {const}
+ getName(): string   {const}
+ getPrice(): float   {const}
+ operator<<(ostream&, const Item&): ostream&   {friend}   <- implement

Menu
- maxSize: int
- items: Item**
+ Menu(int)
+ ~Menu()
+ operator+(Item*): Menu&
+ operator<<(ostream&, const Menu&): ostream&   {friend}
```

Differences from the partial UML in the exam paper:

- `operator<<` is not drawn, but the exam paper says every class has one.
- `operator+` returns `Menu&`. The exam paper shows no return type.
- `getPrice()` returns `float` here. The exam paper shows `string`, which is probably a mistake, because `price` is a `float`.
- The exam paper's `Menu` also has `findFirst`, `findLast`, `averagePrice`, `numberAbove`, `numberBelow`, `numberEqual`. This question does not use them.

## Given code you will use

- `Menu(int maxSize)` makes an array of `maxSize` pointers. Every slot starts as `NULL`. An empty slot is `NULL`.
- `operator+(Item*)` puts the item in the first `NULL` slot and returns the menu, so `menu + a + b;` works. If the menu is full, it deletes the item. The menu owns its items and deletes them in `~Menu()`. Nothing in this question removes items, so the filled slots are always at the front.
- `Menu`'s `operator<<` prints `Menu (max <maxSize>):` and then one line per slot: two spaces, then `[`, the index, `]` and one space, then the item, or `empty` for a `NULL` slot. It uses `Item`'s `operator<<` for each item.

## What `operator<<(ostream& out, const Item& item)` must print

Print the name, a space, the type in round brackets, a space, the letter `R` and the price:

```text
<name> (<type>) R<price>
```

For example `Garlic bread (S) R45.5` and `Beef burger (M) R120`.

More rules:

- Print the price with the default `float` output of the stream. Do not use `fixed` or `setprecision`. `120` prints as `120` and `45.5` prints as `45.5`.
- Print no newline. The caller adds `endl` when it wants one.
- Write to `out`, not to `cout`, and return `out`. The caller may pass another stream, for example an `ostringstream`. This is a stream that keeps the text in a `string` instead of showing it on the screen.
- Read `item.name`, `item.type` and `item.price` directly. A friend may read private members. This works whatever the header says about `const` getters. A getter that is not `const` cannot be called on the `const Item&`.
- Write the word `friend` only in the class. Do not write it again in `A_2.cpp`.

The given `operator<<` functions and the `ExpectedOutput` block apply to this question only. Another question in this bank may print the same class in a different way.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`. `-Wall -Werror` turns every warning into an error.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
