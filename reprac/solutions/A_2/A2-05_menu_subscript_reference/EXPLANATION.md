# A2-05 Explanation: Menu::operator[] returning Item*&

## What the function must do

`menu[i]` gives access to slot `i` of the array `items`. The return type `Item*&` is a reference to a pointer. A reference is another name for an existing variable. So `menu[i]` is another name for the array element `items[i]` itself. The caller can read it (`*menu[1]`, `menu[2] == NULL`) and can also store a new pointer in it (`menu[2] = new Item(...)`).

The function is not in the exam paper.

## How the solution works

```cpp
Item*& Menu::operator[](int index) {
    return items[index];
}
```

**Reading the return type.** Read `Item*&` from the right: a reference (`&`) to a pointer (`*`) to an `Item`. The array `items` has the type `Item**`, so each element `items[index]` has the type `Item*`. Returning it as `Item*&` returns the element, not a copy of the address in it.

**Why one line is enough.** `items[index]` is an element of the array. The array lives on the heap until `~Menu()` deletes it, so the reference stays valid after the function returns.

**What the caller can do with it.**

| Expression in `main.cpp` | Meaning |
|---|---|
| `*menu[1]` | `menu[1]` is the pointer in slot 1; the star gives the `Item` |
| `menu[2] == NULL` | reads the pointer in slot 2 and compares it with `NULL` |
| `menu[2] = new Item(...)` | stores a new address in slot 2 of the array |
| `delete menu[0];` | deletes the item that slot 0 points to; the slot still holds the old address |
| `menu[0] = new Item(...)` | stores a new address in slot 0 |

The assignment `menu[2] = ...` works only because the function returns a reference. With a return type of `Item*`, `menu[2]` would be a temporary copy of the address, and assigning to it would not compile.

**What the function does not do.** It does not check the index (the question says the index is always valid). It does not make or delete anything. Managing the items stays with the caller and with `~Menu()`.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

`main.cpp` makes `Menu menu(3);` and adds Garlic bread (slot 0) and Beef burger (slot 1). Slot 2 is `NULL`.

| Step | Statement | Slot 0 | Slot 1 | Slot 2 | Printed |
|---|---|---|---|---|---|
| 1 | `cout << "Slot 1: " << *menu[1] << endl;` | Garlic bread | Beef burger | `NULL` | `Slot 1: Beef burger (M) R120` |
| 2 | `if (menu[2] == NULL)` is true | Garlic bread | Beef burger | `NULL` | `Slot 2 is empty` |
| 3 | `menu[2] = new Item('D', "Malva pudding", 60);` | Garlic bread | Beef burger | Malva pudding | |
| 4 | `delete menu[0];` | (deleted; old address) | Beef burger | Malva pudding | |
| 5 | `menu[0] = new Item('S', "Soup", 50);` | Soup | Beef burger | Malva pudding | |
| 6 | `cout << menu;` | | | | the three items |

In step 3, the function returns a reference to `items[2]`, and the assignment writes the address of the new item into the array. In step 4, `menu[0]` gives the pointer in slot 0, and `delete` frees Garlic bread. Step 5 overwrites the old address at once, so the slot never keeps a pointer to freed memory.

At the end, `~Menu()` deletes Soup, Beef burger and Malva pudding. Every `new` has one `delete`.

## Common mistakes

- **Returning a reference to a local variable**, as in `Item* slot = items[index]; return slot;`. `slot` is destroyed when the function ends, so the reference would point to nothing. g++ reports "reference to local variable 'slot' returned" (`-Wreturn-local-addr`), and `-Werror` stops the build. The mark is 0.
- **Returning a separate `static` pointer for an empty slot**, as in `static Item* none = NULL; if (items[index] == NULL) return none;`. Reading still looks right. But `menu[2] = new Item(...)` then writes into `none`, not into the array. Malva pudding never reaches the menu: the print shows `[2] empty`, and the item is never deleted. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block. `main.cpp` does not show the leak. Two assignments to empty slots do: the second assignment overwrites `none`, and valgrind reports the first item as `definitely lost`.
- **Return type `Item*` in `A_2.cpp`.** It does not match the declaration `Item*& operator[](int index);` in `Menu.h`, so the build fails.
- **Returning `*items[index]`.** That is an `Item`, not an `Item*`. The types do not match, and the build fails.
- **Checking the range and returning `NULL`.** A reference cannot refer to the literal `NULL`. If a range check is needed, the function must throw an exception instead.
