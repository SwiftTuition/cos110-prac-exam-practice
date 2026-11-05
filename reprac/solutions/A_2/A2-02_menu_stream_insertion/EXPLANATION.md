# A2-02 Explanation: operator<< for Menu

## What the function must do

The function prints a whole menu: a heading with the array size, then one line per slot. A slot with an item shows the item. A `NULL` slot shows the word `empty`. Every slot gets a line, so the output also shows where the free places are.

```text
Menu (max 3):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] empty
```

## How the solution works

```cpp
ostream& operator<<(ostream& out, const Menu& menu) {
    out << "Menu (max " << menu.maxSize << "):" << endl;
    for (int i = 0; i < menu.maxSize; i++) {
        out << "  [" << i << "] ";
        if (menu.items[i] == NULL) {
            out << "empty";
        } else {
            out << *menu.items[i];
        }
        out << endl;
    }
    return out;
}
```

**The signature.** `out` is the caller's stream. `menu` is a `const` reference: the function reads the menu and changes nothing. The function is a `friend` of `Menu`, so it may read the private members `menu.maxSize` and `menu.items`.

**The heading.** `out << "Menu (max " << menu.maxSize << "):" << endl;` prints the size of the array, not the number of items. It ends with `endl`.

**The loop.**

- `for (int i = 0; i < menu.maxSize; i++)` visits every slot from 0 to `maxSize - 1`. For a menu of size 0, the condition `0 < 0` is false at once, so only the heading is printed.
- `out << "  [" << i << "] ";` prints the start of the line: two spaces, the index in square brackets, a space. This part is the same for a full slot and an empty slot, so it comes before the `if`.

**The condition.**

- `menu.items[i] == NULL` is true for an empty slot. The function then prints `empty`.
- Otherwise the slot holds an address. `*menu.items[i]` follows the pointer and gives the `Item`. `out << *menu.items[i]` then calls the given `operator<<` for `Item`, which prints `<name> (<type>) R<price>`.
- The star is required. `out << menu.items[i]` without the star prints the pointer, which is a memory address such as `0x4e1f0c0`.
- The `NULL` check must come before the star. Using `*` on a `NULL` pointer is undefined behaviour and usually crashes the program.

**The end of the line.** `out << endl;` comes after the `if`, so both kinds of line end the same way.

**The return.** `return out;` gives the stream back, so `cout << menu << "(end)" << endl;` works.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

`main.cpp` makes a menu of size 4 and prints it three times.

**First `cout << menu;`.** All four slots are `NULL`.

| `i` | `menu.items[i] == NULL` | line |
|---|---|---|
| 0 | true | `  [0] empty` |
| 1 | true | `  [1] empty` |
| 2 | true | `  [2] empty` |
| 3 | true | `  [3] empty` |

**Second `cout << menu;`.** `operator+` has stored Garlic bread in slot 0 and Beef burger in slot 1.

| `i` | `menu.items[i] == NULL` | line |
|---|---|---|
| 0 | false | `  [0] Garlic bread (S) R45.5` |
| 1 | false | `  [1] Beef burger (M) R120` |
| 2 | true | `  [2] empty` |
| 3 | true | `  [3] empty` |

**Third print, `cout << menu << "(end)" << endl;`.** After `main` adds two more items, all four slots hold items, so the condition is false four times. After the loop, `return out;` returns `cout`, and `main` prints `(end)` on the next line.

## Common mistakes

- **No `NULL` check**, as in `out << "  [" << i << "] " << *menu.items[i] << endl;` for every slot. The first print of `main.cpp` already reaches a `NULL` slot. Valgrind reports an invalid read, and the program stops with a segmentation fault after `Menu (max 4):`. The mark is 0.
- **Skipping the empty slots.** If the function prints only the slots that hold items, the lines `  [i] empty` are missing. The first print of `main.cpp` shows only the heading. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Printing the pointer.** `out << menu.items[i];` prints an address in hexadecimal instead of the item. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Writing to `cout` instead of `out`.** `main.cpp` looks right, because it prints to `cout`. `main.cpp` does not show this mistake. Code that writes a menu into an `ostringstream` does: with `cout`, the text appears on the screen at once, and the string stream stays empty.
- **`i <= menu.maxSize`.** The loop reads `menu.items[maxSize]`, one slot past the array. Valgrind reports an invalid read.
- **Printing a count of items in the heading.** The heading shows `maxSize`, the length of the array, even for an empty menu: `Menu (max 4):`.
