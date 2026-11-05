Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A2-05. Operator overloading: `Menu::operator[]` returns `Item*&` (100)

For this question, implement the subscript operator `operator[]` of the `Menu` class in the file `A_2.cpp`. It gives the caller access to one slot of the `items` array. The return type is a reference to the pointer in that slot. So the caller can read the slot, and the caller can store a new pointer in it.

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
+ operator[](int): Item*&   <- implement
+ operator<<(ostream&, const Menu&): ostream&   {friend}
```

Differences from the partial UML in the exam paper:

- `Menu::operator[]` (the target) is not in the exam paper. It uses the same skill as the exam's operators: an operator that returns a reference.
- `operator<<` is not drawn, but the exam paper says every class has one.
- `operator+` returns `Menu&`. The exam paper shows no return type.
- `getPrice()` returns `float` here. The exam paper shows `string`, which is probably a mistake, because `price` is a `float`.
- The exam paper's `Menu` also has `findFirst`, `findLast`, `averagePrice`, `numberAbove`, `numberBelow`, `numberEqual`. This question does not use them.

## Given code you will use

- `Item`'s `operator<<` prints `<name> (<type>) R<price>` with no newline, for example `Garlic bread (S) R45.5`. The type is `'S'` (starter), `'M'` (main) or `'D'` (dessert).
- `Menu(int maxSize)` makes an array of `maxSize` pointers. Every slot starts as `NULL`. An empty slot is `NULL`.
- `operator+(Item*)` puts the item in the first `NULL` slot and returns the menu, so `menu + a + b;` works. If the menu is full, it deletes the item. The menu owns its items and deletes them in `~Menu()`. Nothing in this question removes items, so the filled slots are always at the front.
- `Menu`'s `operator<<` prints `Menu (max <maxSize>):` and then one line per slot: two spaces, then `[`, the index, `]` and one space, then the item, or `empty` for a `NULL` slot.

## What `operator[](int index)` must do

Return the slot `items[index]` itself, as an `Item*&`.

- `menu[i]` then reads the pointer in slot `i`. It can be `NULL`.
- `menu[i] = p;` stores the pointer `p` in slot `i` of the array.

More rules:

- The index is always between 0 and `maxSize - 1` in this question. Do not check it, and do not throw.
- Do not make a new pointer or a new item. Do not delete anything.
- Return a reference to the array element, not to a local variable. If you return a reference to a local variable, g++ gives a `-Wreturn-local-addr` warning, and `-Werror` makes it an error.
- The caller is responsible for the old item when it overwrites a slot. `main.cpp` deletes it first (`delete menu[0];`).

The given `operator<<` functions and the `ExpectedOutput` block apply to this question only. Another question in this bank may print the same class in a different way.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`. `-Wall -Werror` turns every warning into an error.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
