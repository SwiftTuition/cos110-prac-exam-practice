Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A1-02. Exceptions: `Menu::findFirst` throws `InvalidType` or the right not-found exception (100)

For this question, implement the member function `findFirst` of the `Menu` class in the file `A_1.cpp`. It returns a copy of the first item of a type. It throws an exception when the type name is not valid or when the menu has no item of that type.

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
+ findFirst(string): Item   <- implement
+ operator<<(ostream&, const Menu&): ostream&   {friend}
```

Differences from the partial UML in the exam paper:

- `operator<<` is not drawn, but the exam paper says every class has one.
- `~Exception()` is virtual, so that the classes are polymorphic.
- `operator+` returns `Menu&`. The exam paper shows no return type.
- `getPrice()` returns `float` here. The exam paper shows `string`, which is probably a mistake, because `price` is a `float`.
- The exam paper's `Menu` also has `findLast`, `averagePrice`, `numberAbove`, `numberBelow`, `numberEqual`. This question does not use them.

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

## What `findFirst(string type)` must do

The `string` parameter is a type name. `"Starter"` means `'S'`, `"Main"` means `'M'` and `"Dessert"` means `'D'`. The match is exact and case-sensitive, so `"main"` and `"Drink"` are not valid type names.

1. If `type` is not one of the three valid names, throw `InvalidType(type)`.
2. Otherwise, go through the slots from index 0 upward. Return a copy of the first item whose type matches.
3. If no item matches, throw the not-found class for that type: `StarterNotFound()` for `"Starter"`, `MainNotFound()` for `"Main"`, `DessertNotFound()` for `"Dessert"`.

More rules:

- Check the type name first, before the loop. An invalid name throws `InvalidType` even for an empty menu.
- Return the item itself by value: `return *items[i];`. The copy constructor makes the copy.
- Skip `NULL` slots. A call through a `NULL` pointer stops the program.
- Throw the exception object by value, for example `throw MainNotFound();`. Do not use `new`. The caller catches by reference.
- Do not catch the exception and do not print anything in `findFirst`.

The given `operator<<` functions and the `ExpectedOutput` block apply to this question only. Another question in this bank may print the same class in a different way.

## Build and upload

1. Open a terminal in the `A_1` folder.
2. Run `make A_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`. `-Wall -Werror` turns every warning into an error.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
