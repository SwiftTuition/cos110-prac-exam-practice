Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A2-06. Operator overloading: `Item::operator==` and `Item::operator<` (100)

For this question, implement two comparison operators of the `Item` class in the file `A_2.cpp`: `operator==` and `operator<`. Both are `const` member functions.

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
+ operator==(const Item&): bool   {const}   <- implement
+ operator<(const Item&): bool   {const}   <- implement
+ operator<<(ostream&, const Item&): ostream&   {friend}
```

Differences from the partial UML in the exam paper:

- `Item::operator==` and `Item::operator<` (the targets) are not in the exam paper. They are operators written as member functions, like the exam's `Menu::operator+`.
- `operator<<` is not drawn, but the exam paper says every class has one.
- `getPrice()` returns `float` here. The exam paper shows `string`, which is probably a mistake, because `price` is a `float`.

## Given code you will use

- `Item`'s `operator<<` prints `<name> (<type>) R<price>` with no newline, for example `Garlic bread (S) R45.5`. The type is `'S'` (starter), `'M'` (main) or `'D'` (dessert).

## What the two operators must do

1. `a == b` is `true` when the two items have the same type, the same name and the same price. Otherwise it is `false`.
2. `a < b` is `true` when the price of `a` is less than the price of `b`. Only the price decides. If the prices are equal, the result is `false`.

More rules:

- Both functions are `const`: write `const` after the parameter list, as in `Item.h`. They must not change either item.
- The parameter is `const Item& other`. Compare the members of the object itself (the left operand) with the members of `other` (the right operand).
- The prices in this question have an exact `float` value (for example `95.5`), so `==` on two prices is safe here.

The given `operator<<` functions and the `ExpectedOutput` block apply to this question only. Another question in this bank may print the same class in a different way.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`. `-Wall -Werror` turns every warning into an error.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.

Hints: `HINTS.md` in this folder.
