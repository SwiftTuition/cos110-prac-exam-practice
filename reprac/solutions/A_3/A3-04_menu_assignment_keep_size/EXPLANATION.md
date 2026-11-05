# A3-04: Assignment operator: `Menu::operator=` that keeps its own size (tutor notes)

## The answer

```cpp
#include "Menu.h"

Menu& Menu::operator=(const Menu& other) {
    if (this == &other) {
        return *this;
    }

    // Empty this menu. The array stays: its size (maxSize) does not change.
    for (int i = 0; i < maxSize; i++) {
        delete items[i];
        items[i] = NULL;
    }

    // Copy slot i of other into slot i of this menu, for every slot that both menus have.
    for (int i = 0; i < maxSize && i < other.maxSize; i++) {
        if (other.items[i] != NULL) {
            items[i] = new Item(*other.items[i]);
        }
    }

    return *this;
}
```

- The self-assignment check is the same as always.
- The first loop deletes each item **and sets the slot to `NULL`**. The array itself is kept, so its slots would otherwise still hold the addresses of deleted items. If `b` has fewer items than `a` has slots, those slots are printed and later deleted again.
- The second loop runs while `i` is a slot of **both** menus: `i < maxSize && i < other.maxSize`. The first half stops it at the end of this menu's array; the second half stops it at the end of `other`'s array. Inside, the `if` skips `other`'s empty slots: those slots of this menu are already `NULL` from the first loop.
- `return *this;`

## A trace of `a = b;` in main (part 1)

`a` has 2 slots (`Soup`, empty). `b` has 4 (`Garlic bread`, `Beef burger`, `Malva pudding`, empty).

- First loop: `Soup` deleted, slot 0 set to `NULL`; slot 1 already `NULL`.
- `i = 0`: `0 < 2` and `0 < 4`, so copy Garlic bread to slot 0. `i = 1`: `1 < 2` and `1 < 4`, so copy Beef burger to slot 1. `i = 2`: `2 < 2` is false, so the loop stops. Malva pudding is not copied.

## Mistakes that cost marks

- Not setting the slots to `NULL` after deleting: part 2 (`b = c`, with `b` keeping 4 slots and `c` holding one item) prints deleted items: invalid reads.
- A loop condition with only `i < other.maxSize`: when `other` is bigger, the code writes past the end of this menu's array (invalid write).
- Replacing the array and copying `maxSize` (the usual version): `a` prints 4 slots instead of 2, so the output is wrong.
