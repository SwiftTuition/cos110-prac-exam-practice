Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A2-07. Operator overloading: `Menu::operator+=` grows the array when the menu is full (100)

For this question, implement the member operator `operator+=` of the `Menu` class in the file `A_2.cpp`. Like the given `operator+`, it adds one item to the menu. Unlike `operator+`, it never deletes the item: when the menu is full, it makes the array one slot bigger.

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
+ operator+=(Item*): Menu&   <- implement
+ operator<<(ostream&, const Menu&): ostream&   {friend}
```

Differences from the partial UML in the exam paper:

- `Menu::operator+=` (the target) is not in the exam paper. Like the exam's `operator+`, it manages the `Item**` array.
- `operator<<` is not drawn, but the exam paper says every class has one.
- `operator+` returns `Menu&`. The exam paper shows no return type.
- `getPrice()` returns `float` here. The exam paper shows `string`, which is probably a mistake, because `price` is a `float`.
- The exam paper's `Menu` also has `findFirst`, `findLast`, `averagePrice`, `numberAbove`, `numberBelow`, `numberEqual`. This question does not use them.

## Given code you will use

- `Item`'s `operator<<` prints `<name> (<type>) R<price>` with no newline, for example `Garlic bread (S) R45.5`. The type is `'S'` (starter), `'M'` (main) or `'D'` (dessert).
- `Menu(int maxSize)` makes an array of `maxSize` pointers. Every slot starts as `NULL`. An empty slot is `NULL`.
- `operator+(Item*)` puts the item in the first `NULL` slot and returns the menu, so `menu + a + b;` works. If the menu is full, it deletes the item. The menu owns its items and deletes them in `~Menu()`. Nothing in this question removes items, so the filled slots are always at the front.
- `Menu`'s `operator<<` prints `Menu (max <maxSize>):` and then one line per slot: two spaces, then `[`, the index, `]` and one space, then the item, or `empty` for a `NULL` slot.
- `~Menu()` deletes the items in slots 0 to `maxSize - 1`, then the array. It uses the current value of `maxSize`.

## What `operator+=(Item* item)` must do

1. If the menu has a `NULL` slot, store `item` in the first one (the lowest index) and stop.
2. Otherwise (the menu is full):
   1. Make a new array of `maxSize + 1` pointers.
   2. Copy the pointers from the old array into slots 0 to `maxSize - 1` of the new array. Do this before you change `maxSize`.
   3. Store `item` in the last slot, index `maxSize`.
   4. Delete the old array with `delete[]`. Do not delete the items: the new array points to them now.
   5. Make `items` point to the new array and add 1 to `maxSize`.
3. In both cases, return the menu itself (`*this`).

More rules:

- The menu owns every item given to it. `operator+=` never deletes the item it is given.
- The new array grows by exactly one slot.
- Copy the pointers, not the items. Do not call `new Item(...)`.

The given `operator<<` functions and the `ExpectedOutput` block apply to this question only. Another question in this bank may print the same class in a different way.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`. `-Wall -Werror` turns every warning into an error.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
