# A3-03: Copy constructor: `Menu::Menu(const Menu&)` (tutor notes)

## The answer

```cpp
#include "Menu.h"

Menu::Menu(const Menu& other) {
    maxSize = other.maxSize;
    items = new Item*[maxSize];
    for (int i = 0; i < maxSize; i++) {
        if (other.items[i] == NULL) {
            items[i] = NULL;
        } else {
            items[i] = new Item(*other.items[i]);
        }
    }
}
```

A copy constructor builds a new object, so it has no old memory to free and no self-assignment to check. It is step 3 of `operator=` alone: set `maxSize`, make a new array, and copy each slot. The `if` matters here as it does in `operator=`: `new Item*[maxSize]` does not set the slots to `NULL`, so an empty slot that is skipped holds a random address, and `~Menu()` then deletes it.

`Menu c = b;` looks like an assignment, but `c` is being created on that line, so the copy constructor runs, not `operator=`.

## Mistakes that cost marks

- `items = other.items;`: both menus share one array; the second destructor frees everything again (invalid frees).
- Skipping `NULL` slots without setting them to `NULL`: valgrind reports uninitialised values, and the destructor deletes random addresses.
- Writing a return type on a constructor: a compile error.
