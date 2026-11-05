Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A1-07. Exceptions: `Menu::numberEqual` counts items and throws `NothingMatchingFilter` (100)

For this question, implement the member function `numberEqual` of the `Menu` class in the file `A_1.cpp`. It counts the items of one type whose price is exactly equal to a value. It throws an exception when the type name is not valid or when the count is 0.

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
+ numberEqual(string, float): int   <- implement
+ operator<<(ostream&, const Menu&): ostream&   {friend}
```

Differences from the partial UML in the exam paper:

- `operator<<` is not drawn, but the exam paper says every class has one.
- `~Exception()` is virtual, so that the classes are polymorphic.
- `operator+` returns `Menu&`. The exam paper shows no return type.
- `getPrice()` returns `float` here. The exam paper shows `string`, which is probably a mistake, because `price` is a `float`.
- The exam paper's `Menu` also has `findFirst`, `findLast`, `averagePrice`, `numberAbove`, `numberBelow`. This question does not use them.

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

## What `numberEqual(string type, float value)` must do

The `string` parameter is a type name. `"Starter"` means `'S'`, `"Main"` means `'M'` and `"Dessert"` means `'D'`. The match is exact and case-sensitive, so `"main"` and `"Drink"` are not valid type names.

1. If `type` is not one of the three valid names, throw `InvalidType(type)`.
2. Otherwise, count the items of that type whose price is exactly equal to `value` (the test is `price == value`).
3. If the count is 0, throw `NothingMatchingFilter(type)`.
4. Otherwise, return the count.

More rules:

- Check the type name first, before the loop. An invalid name throws `InvalidType` even for an empty menu.
- Skip `NULL` slots.
- Count only items of the given type. An item of another type does not count, even when its price is exactly equal to `value`.
- Throw the exception object by value. Do not catch it and do not print anything in `numberEqual`.
- Throw `NothingMatchingFilter(type)`, not one of its two subclasses. Its message names the type, for example `Nothing matching filter: Main`.
- The prices in this question have an exact `float` value (for example `95.5`), so `==` on two prices is safe here.

The given `operator<<` functions and the `ExpectedOutput` block apply to this question only. Another question in this bank may print the same class in a different way.

## Build and upload

1. Open a terminal in the `A_1` folder.
2. Run `make A_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`. `-Wall -Werror` turns every warning into an error.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
