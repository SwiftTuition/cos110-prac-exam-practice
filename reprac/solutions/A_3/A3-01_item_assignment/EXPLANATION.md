# A3-01: Assignment operator: `Item::operator=` (tutor notes)

## The answer

```cpp
#include "Item.h"

Item& Item::operator=(const Item& other) {
    if (this == &other) {
        return *this;
    }
    type = other.type;
    name = other.name;
    price = other.price;
    return *this;
}
```

- `Item& Item::operator=(const Item& other)`: the return type is a reference to an `Item`, the class name and `::` come before `operator=`, and the parameter is a `const` reference (copying the parameter would call the copy constructor for nothing).
- `if (this == &other)`: `this` is the address of the item on the left of `=`; `&other` is the address of the item on the right. They are equal only for `a = a;`. For an `Item` nothing goes wrong without this check (nothing is deleted), but writing it every time builds the habit that `Menu::operator=` needs.
- The three assignments copy each member. `name` is a `string`, and `string` has its own `operator=`, so this copies the characters.
- `return *this;`: `this` is a pointer, `*this` is the item itself. Returning it lets `a = b = c;` work: `b = c` runs first and returns `b`, then `a = b` runs.

## The test

`main.cpp` checks `a = b` (all three members, printed with `<<` and with the getters), `a = a`, and `a = b = c`. `main_edge.cpp` assigns from a temporary returned by a function, through pointers, and an empty name.

## Mistakes that cost marks

- No `return *this;`: `-Wall -Werror` turns "control reaches end of non-void function" into a compile error, so the mark is 0.
- Forgetting one member (often `price`): the program runs, but the printed price is wrong.
- Writing `Item::operator=(...)` with no return type, or leaving out `Item::`: a compile error.
