# A3-02: Assignment operator: `Menu::operator=` (tutor notes)

## The answer

```cpp
#include "Menu.h"

Menu& Menu::operator=(const Menu& other) {
    if (this == &other) {
        return *this;
    }

    for (int i = 0; i < maxSize; i++) {
        delete items[i];
    }
    delete[] items;

    maxSize = other.maxSize;
    items = new Item*[maxSize];
    for (int i = 0; i < maxSize; i++) {
        if (other.items[i] == NULL) {
            items[i] = NULL;
        } else {
            items[i] = new Item(*other.items[i]);
        }
    }

    return *this;
}
```

The four steps:

1. **Self-assignment check.** `this == &other` is true only for `a = a;`. Without it, step 2 deletes `a`'s items and array. In step 3, `other` is `a`, so `other.items` is the new array, whose slots were never set. valgrind reports `Conditional jump or move depends on uninitialised value(s)`, and `a`'s items are lost.
2. **Free the old memory.** The first loop deletes every item (`delete` on a `NULL` slot does nothing, so no `if` is needed). Then `delete[] items;` frees the array of pointers. Deleting only the array leaks every item.
3. **Deep copy.** `maxSize = other.maxSize;` must come before `new Item*[maxSize]`, otherwise the new array has the old size. In the loop, the condition `other.items[i] == NULL` is true for an empty slot: the copy gets `NULL` too. Otherwise `new Item(*other.items[i])` calls the `Item` copy constructor, so the copy gets its own item. `items[i] = other.items[i];` would copy only the address, so both menus would delete the same item.
4. **`return *this;`** so that `a = b = c;` works.

## A trace of `a = b;` in main (part 1)

Before: `a` has `maxSize` 2 (`Soup`, empty). `b` has `maxSize` 4 (`Garlic bread`, `Beef burger`, `Malva pudding`, empty).

- Step 1: `this` is `&a`, `&other` is `&b`: different, carry on.
- Step 2: `i = 0` deletes `Soup`; `i = 1` deletes `NULL` (nothing happens). Then the 2-slot array is freed.
- Step 3: `maxSize` becomes 4, a new 4-slot array is made. `i = 0`: `b`'s slot holds Garlic bread, so a new copy goes in. `i = 1`: Beef burger, copied. `i = 2`: Malva pudding, copied. `i = 3`: `NULL`, so `items[3] = NULL`.
- Step 4: returns `a`.

Part 2 adds `Veg curry` to `b`; `a` still prints `[3] empty`, which shows the arrays are separate.

## Mistakes that cost marks

- `items = other.items;` (shallow array): both menus share one array. Part 2 shows `Veg curry` in `a` too, and at the end both destructors delete the same items: valgrind reports invalid frees.
- `items[i] = other.items[i];` (shallow slots): each item is deleted twice at the end.
- No self-assignment check: "uninitialised value(s)" errors in part 3, and part 3 prints every slot as `empty`.
- Only `delete[] items;`: every old item leaks.
- Forgetting `maxSize = other.maxSize;`: the new array has the old size. With `a` (size 2) = `b` (size 4), Malva pudding (slot 2) is not copied: wrong output. In part 4, the loop then reads past the end of `c`'s 1-slot array: invalid reads.
