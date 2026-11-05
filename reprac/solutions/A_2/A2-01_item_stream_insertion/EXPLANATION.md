# A2-01 Explanation: operator<< for Item

## What the function must do

The function defines what `cout << anItem` prints. For one item it prints the name, the type in round brackets and the price after an `R`:

```text
Garlic bread (S) R45.5
```

It prints no newline. It writes to the stream it is given and returns that stream.

## How the solution works

```cpp
ostream& operator<<(ostream& out, const Item& item) {
    out << item.name << " (" << item.type << ") R" << item.price;
    return out;
}
```

**The signature.**

- `operator<<` is a normal function, not a member of `Item`. For `cout << bread`, C++ calls `operator<<(cout, bread)`. The stream is the left operand, so it is the first parameter.
- `ostream& out` is a reference to the caller's stream. The function writes into that stream. A copy of a stream is not allowed, so it must be a reference.
- `const Item& item` is a reference to the item. `const` means the function only reads it. The reference avoids a copy and also accepts a temporary object, such as `Item('S', "Bread of the day", 0)`.
- The function is a `friend` of `Item` (see `Item.h`). A friend may read the private members `item.name`, `item.type` and `item.price`. The word `friend` stays in the class. It is not written in `A_2.cpp`.

**The body.**

- `out << item.name` prints the name. The name may contain spaces, such as `Garlic bread`. A `string` prints all its characters.
- `" ("` prints a space and an opening bracket.
- `item.type` is a `char`. It prints as one letter, such as `S`.
- `") R"` prints the closing bracket, a space and the letter `R`.
- `item.price` is a `float`. The stream prints it in its default format: no zeros at the end of the number and no more than 6 digits in total. So 120 prints as `120`, 45.5 as `45.5`, and 60.25 as `60.25`.
- No `endl`. The caller decides about the newline.
- The body reads `item.name`, `item.type` and `item.price` directly. This works with any `Item.h`, because the function is a friend. Calling `item.getName()` and the other getters also works here, because they are `const` in this `Item.h`. If a getter is not `const`, it cannot be called on the `const Item&`, and the build fails. Check the header in the exam.

**`return out;`** returns the same stream. This makes chains work. `cout << burger << " | " << pudding` runs as `operator<<(operator<<(operator<<(cout, burger), " | "), pudding)`. Each call returns `cout`, and the next `<<` writes to it.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

`main.cpp` makes three items and prints them.

| Statement | Calls of this function | Printed |
|---|---|---|
| `cout << bread << endl;` | `out` is `cout`, `item` is bread | `Garlic bread (S) R45.5`, then `endl` from `main` |
| `cout << burger << " \| " << pudding << endl;` | first with burger, returns `cout`; then `" \| "`; then with pudding | `Beef burger (M) R120 \| Malva pudding (D) R60.25` |

For the first call, the pieces are:

| Piece | Output so far |
|---|---|
| `item.name` | `Garlic bread` |
| `" ("` | `Garlic bread (` |
| `item.type` | `Garlic bread (S` |
| `") R"` | `Garlic bread (S) R` |
| `item.price` | `Garlic bread (S) R45.5` |

Then `cout << menu;` runs the given `operator<<` for `Menu`. It calls this function once for each slot that holds an item: slot 0 (the copy of `bread` made by `new Item(bread)`) and slot 1 (Veg curry). Slot 2 is `NULL`, so the menu prints `empty` and does not call this function.

## Common mistakes

- **Ending with `endl`.** Every item then ends its own line. `cout << burger << " | " << pudding` prints `Beef burger (M) R120` and ` | Malva pudding (D) R60.25` on two lines, and `main`'s own `endl` adds empty lines. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Writing to `cout` instead of `out`.** The output of `main.cpp` looks right, because `main` only prints to `cout`. `main.cpp` does not show this mistake. Code that writes items into an `ostringstream` does, for example `text << Item('D', "Ice cream", 35) << ";" << Item('S', "Soup", 50);` and then `cout << "[" << text.str() << "]" << endl;`. With `cout` inside the function, the items appear on the screen at once, and the string stream gets only the `;`. The line becomes `Ice cream (D) R35Soup (S) R50[;]` instead of `[Ice cream (D) R35;Soup (S) R50]`.
- **Printing the price with `fixed << setprecision(2)`.** The prices then print as `R45.50` and `R120.00`. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block. The settings also stay on the stream after the function returns, so later output changes too.
- **Writing `friend` in `A_2.cpp`.** `friend` is allowed only inside a class. Outside the class it is a compile error.
- **A missing `return out;`.** g++ warns that a non-void function does not return a value, and `-Werror` stops the build.
