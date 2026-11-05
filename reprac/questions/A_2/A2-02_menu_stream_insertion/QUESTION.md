Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A2-02. Operator overloading: `operator<<` for `Menu` (prints empty slots) (100)

For this question, implement the stream insertion operator `operator<<` for the `Menu` class in the file `A_2.cpp`. It is a `friend` function of `Menu`. It prints a heading line and then one line for every slot of the array, also the empty ones.

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
+ operator<<(ostream&, const Item&): ostream&   {friend}

Menu
- maxSize: int
- items: Item**
+ Menu(int)
+ ~Menu()
+ operator+(Item*): Menu&
+ operator<<(ostream&, const Menu&): ostream&   {friend}   <- implement
```

Differences from the partial UML in the exam paper:

- `operator<<` is not drawn, but the exam paper says every class has one.
- `operator+` returns `Menu&`. The exam paper shows no return type.
- `getPrice()` returns `float` here. The exam paper shows `string`, which is probably a mistake, because `price` is a `float`.
- The exam paper's `Menu` also has `findFirst`, `findLast`, `averagePrice`, `numberAbove`, `numberBelow`, `numberEqual`. This question does not use them.

## Given code you will use

- `Item`'s `operator<<` prints `<name> (<type>) R<price>` with no newline, for example `Garlic bread (S) R45.5`. The type is `'S'` (starter), `'M'` (main) or `'D'` (dessert).
- `Menu(int maxSize)` makes an array of `maxSize` pointers. Every slot starts as `NULL`. An empty slot is `NULL`.
- `operator+(Item*)` puts the item in the first `NULL` slot and returns the menu, so `menu + a + b;` works. If the menu is full, it deletes the item. The menu owns its items and deletes them in `~Menu()`. Nothing in this question removes items, so the filled slots are always at the front.

## What `operator<<(ostream& out, const Menu& menu)` must print

1. A heading line: `Menu (max <maxSize>):`.
2. Then one line for each slot, from index 0 to `maxSize - 1`: two spaces, then `[`, the index, `]` and one space, and then
   - the item, printed with `Item`'s `operator<<`, if the slot holds an item;
   - the word `empty`, if the slot is `NULL`.

Every line ends with `endl`, including the last one. Example for a menu of size 3 with two items:

```text
Menu (max 3):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] empty
```

More rules:

- A menu of size 0 prints only `Menu (max 0):`.
- Do not dereference a `NULL` slot.
- Write to `out`, not to `cout`, and return `out`.
- `menu` is a `const` reference. A friend may read `menu.maxSize` and `menu.items`.
- Write the word `friend` only in the class. Do not write it again in `A_2.cpp`.

The given `operator<<` functions and the `ExpectedOutput` block apply to this question only. Another question in this bank may print the same class in a different way.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`. `-Wall -Werror` turns every warning into an error.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
