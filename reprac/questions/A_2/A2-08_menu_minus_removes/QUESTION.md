Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A2-08. Operator overloading: `Menu::operator-(string)` removes an item by name (100)

For this question, implement the member operator `operator-` of the `Menu` class in the file `A_2.cpp`. It removes the first item with a given name and keeps the filled slots at the front of the array.

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
+ operator-(string): Menu&   <- implement
+ operator<<(ostream&, const Menu&): ostream&   {friend}
```

Differences from the partial UML in the exam paper:

- `Menu::operator-` (the target) is not in the exam paper. Like the exam's `operator+`, it manages the `Item**` array.
- `operator<<` is not drawn, but the exam paper says every class has one.
- `operator+` returns `Menu&`. The exam paper shows no return type.
- `getPrice()` returns `float` here. The exam paper shows `string`, which is probably a mistake, because `price` is a `float`.
- The exam paper's `Menu` also has `findFirst`, `findLast`, `averagePrice`, `numberAbove`, `numberBelow`, `numberEqual`. This question does not use them.

## Given code you will use

- `Item`'s `operator<<` prints `<name> (<type>) R<price>` with no newline, for example `Garlic bread (S) R45.5`. The type is `'S'` (starter), `'M'` (main) or `'D'` (dessert).
- `Menu(int maxSize)` makes an array of `maxSize` pointers. Every slot starts as `NULL`. An empty slot is `NULL`.
- `operator+(Item*)` puts the item in the first `NULL` slot and returns the menu. If the menu is full, it deletes the item. The menu owns its items and deletes them in `~Menu()`.
- `Menu`'s `operator<<` prints `Menu (max <maxSize>):` and then one line per slot: two spaces, then `[`, the index, `]` and one space, then the item, or `empty` for a `NULL` slot.

## What `operator-(string name)` must do

1. Find the first item (the lowest index) whose name is equal to `name`.
2. If there is one:
   1. Delete that item.
   2. Move every pointer after it one slot towards index 0, so that there is no empty slot between two items.
   3. Set the last slot, `items[maxSize - 1]`, to `NULL`.
3. If no item has that name, do not change the menu.
4. In both cases, return the menu itself (`*this`).

Example: a menu of size 4 holds `Garlic bread`, `Beef burger`, `Malva pudding` and one empty slot. After `menu - "Beef burger";` it holds `Garlic bread`, `Malva pudding` and two empty slots.

More rules:

- Remove one item only. If a later item has the same name, it stays.
- The names must match exactly (`==` on two `string`s).
- Do not call `getName()` on a `NULL` slot.
- Do not read `items[maxSize]`: the valid indexes are 0 to `maxSize - 1`.

The given `operator<<` functions and the `ExpectedOutput` block apply to this question only. Another question in this bank may print the same class in a different way.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`. `-Wall -Werror` turns every warning into an error.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
