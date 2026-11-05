Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A1-04. Exceptions: `Menu::averagePrice` throws `NothingMatchingFilter` (100)

For this question, implement the member function `averagePrice` of the `Menu` class in the file `A_1.cpp`. It returns the average price of the items of one type. It throws an exception when the type name is not valid or when the menu has no item of that type.

## UML (only the classes this question needs)

```text
Exception
- msg: string
+ Exception(string)
+ ~Exception()   {virtual}
+ printException(): void
+ operator<<(ostream&, const Exception&): ostream&   {friend}

InvalidType : Exception
+ InvalidType(string)

NothingMatchingFilter : Exception
+ NothingMatchingFilter(string)

NothingAboveMinimumValue : NothingMatchingFilter
+ NothingAboveMinimumValue()

NothingBelowMaximumValue : NothingMatchingFilter
+ NothingBelowMaximumValue()

NotFoundException : Exception
+ NotFoundException()

StarterNotFound : NotFoundException
+ StarterNotFound()

MainNotFound : NotFoundException
+ MainNotFound()

DessertNotFound : NotFoundException
+ DessertNotFound()

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
+ averagePrice(string): float   <- implement
+ operator<<(ostream&, const Menu&): ostream&   {friend}
```

Differences from the partial UML in the exam paper:

- `operator<<` is not drawn, but the exam paper says every class has one.
- `~Exception()` is virtual, so that the classes are polymorphic.
- `operator+` returns `Menu&`. The exam paper shows no return type.
- `getPrice()` returns `float` here. The exam paper shows `string`, which is probably a mistake, because `price` is a `float`.
- The exam paper's `Menu` also has `findFirst`, `findLast`, `numberAbove`, `numberBelow`, `numberEqual`. This question does not use them.

## Given code you will use

- `Item`'s `operator<<` prints `<name> (<type>) R<price>` with no newline, for example `Garlic bread (S) R45.5`. The type is `'S'` (starter), `'M'` (main) or `'D'` (dessert).
- `Menu(int maxSize)` makes an array of `maxSize` pointers. Every slot starts as `NULL`. An empty slot is `NULL`.
- `operator+(Item*)` puts the item in the first `NULL` slot and returns the menu, so `menu + a + b;` works. If the menu is full, it deletes the item. The menu owns its items and deletes them in `~Menu()`. Nothing in this question removes items, so the filled slots are always at the front.
- `Menu`'s `operator<<` prints `Menu (max <maxSize>):` and then one line per slot: two spaces, then `[`, the index, `]` and one space, then the item, or `empty` for a `NULL` slot.
- The exception classes are given. `printException()` prints `Exception: <msg>` and a newline. The messages are:

| Class | Message stored in `msg` |
|---|---|
| `InvalidType(t)` | `Invalid type: t` |
| `NothingMatchingFilter(f)` | `Nothing matching filter: f` |
| `NothingAboveMinimumValue()` | `Nothing matching filter: above minimum value` |
| `NothingBelowMaximumValue()` | `Nothing matching filter: below maximum value` |
| `NotFoundException()`, `StarterNotFound()`, `MainNotFound()`, `DessertNotFound()` | `Item not found` |

  In the table, `t` and `f` stand for the text that the constructor receives. The three not-found classes have the same message. Only the `catch` that catches them tells them apart.

## What `averagePrice(string type)` must do

The `string` parameter is a type name. `"Starter"` means `'S'`, `"Main"` means `'M'` and `"Dessert"` means `'D'`. The match is exact and case-sensitive, so `"main"` and `"Drink"` are not valid type names.

1. If `type` is not one of the three valid names, throw `InvalidType(type)`.
2. Otherwise, add up the prices of the items of that type and count them.
3. If the count is 0, throw `NothingMatchingFilter(type)`. The message then names the type, for example `Nothing matching filter: Dessert`.
4. Otherwise, return the total divided by the count. Keep the total in a `float`, so that the decimals of the prices are kept.

More rules:

- Check the type name first, before the loop. An invalid name throws `InvalidType` even for an empty menu.
- Skip `NULL` slots.
- An item with the price 0 still counts as an item.
- Throw the exception object by value. Do not catch it and do not print anything in `averagePrice`.

The given `operator<<` functions and the `ExpectedOutput` block apply to this question only. Another question in this bank may print the same class in a different way.

## Build and upload

1. Open a terminal in the `A_1` folder.
2. Run `make A_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`. `-Wall -Werror` turns every warning into an error.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
