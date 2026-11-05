Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A1-08. Exceptions: `Menu::printSummary` catches each exception type in the right order (100)

For this question, implement the member function `printSummary` of the `Menu` class in the file `A_1.cpp`. It calls two given functions that can throw, prints one summary line, and catches every exception. Different exception types must print different lines.

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
+ findFirst(string): Item
+ numberAbove(string, float): int
+ printSummary(string, float): bool   <- implement
+ operator<<(ostream&, const Menu&): ostream&   {friend}
```

Differences from the partial UML in the exam paper:

- `Menu::printSummary` (the target) is not in the exam paper. The exam's catching code needs the same skill: `catch` blocks by reference, in the right order.
- `operator<<` is not drawn, but the exam paper says every class has one.
- `~Exception()` is virtual, so that the classes are polymorphic.
- `operator+` returns `Menu&`. The exam paper shows no return type.
- `getPrice()` returns `float` here. The exam paper shows `string`, which is probably a mistake, because `price` is a `float`.
- The exam paper's `Menu` also has `findLast`, `averagePrice`, `numberBelow`, `numberEqual`. This question does not use them.

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
- `findFirst(string type)` returns a copy of the first item of that type. It throws `InvalidType(type)` for a type name that is not `"Starter"`, `"Main"` or `"Dessert"`. It throws `StarterNotFound()`, `MainNotFound()` or `DessertNotFound()` when there is no item of that type.
- `numberAbove(string type, float value)` returns the number of items of that type with a price greater than `value`. It throws `InvalidType(type)` for a bad type name and `NothingAboveMinimumValue()` when the count is 0.

## What `printSummary(string type, float minPrice)` must do

Inside a `try` block, call `findFirst(type)` and then `numberAbove(type, minPrice)`. Then print one line and return:

| Case | What is printed | Return |
|---|---|---|
| no exception | `<type>: first is <item>, <count> above R<minPrice>` and a newline | `true` |
| `findFirst` throws `DessertNotFound` | print `No desserts yet. ` (with a space at the end), then call `e.printException()` | `false` |
| `findFirst` throws `StarterNotFound` or `MainNotFound` (another `NotFoundException`) | print `Not on the menu. ` (with a space at the end), then call `e.printException()` | `false` |
| `numberAbove` throws `NothingAboveMinimumValue` | print `Nothing above R<minPrice>. ` (with a space at the end), then call `e.printException()` | `false` |
| a call throws any other `Exception` (for example `InvalidType`) | print `Request failed. ` (with a space at the end), then call `e.printException()` | `false` |

`<item>` is the item printed with `Item`'s `operator<<`. `printException()` prints `Exception: <msg>` and the newline. Print `<minPrice>` with the default `float` output: `100` prints as `100` and `45.5` prints as `45.5`.

Example lines:

```text
Main: first is Beef burger (M) R120, 1 above R100
No desserts yet. Exception: Item not found
```

More rules:

- No exception may leave `printSummary`. An uncaught exception stops the program abnormally, and the mark is 0.
- Catch each type by reference (with `&`). Here, catching by value gives a `-Wcatch-value` warning, and `-Werror` makes it an error. The warning appears because `Exception` has a virtual destructor in this question. If the exam's `Exception` has no virtual function, `catch (Exception e)` compiles without a warning. It still copies only the `Exception` part of the object. Always catch by reference.
- Print the summary line only when both calls worked. If `numberAbove` throws, nothing of the summary line may be printed.
- Order matters. `DessertNotFound` is also a `NotFoundException`, and every class is also an `Exception`. If a `catch` block for a base class comes before the block for its derived class, g++ gives a warning, and `-Werror` makes it an error.

The given `operator<<` functions and the `ExpectedOutput` block apply to this question only. Another question in this bank may print the same class in a different way.

## Build and upload

1. Open a terminal in the `A_1` folder.
2. Run `make A_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`. `-Wall -Werror` turns every warning into an error.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.

Hints: `HINTS.md` in this folder.
