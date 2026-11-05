# A3-05: Assignment operator: `Binary::operator=` (a `bool*` array) (tutor notes)

## The answer

```cpp
#include "Binary.h"

Binary& Binary::operator=(const Binary& other) {
    if (this == &other) {
        return *this;
    }

    delete[] array;

    size = other.size;
    array = new bool[size];
    for (int i = 0; i < size; i++) {
        array[i] = other.array[i];
    }

    return *this;
}
```

The same four steps as `Menu::operator=`, with one array instead of an array of pointers:

1. `if (this == &other) return *this;`
2. `delete[] array;` (one `delete[]`, because the array holds `bool`s, not pointers).
3. `size = other.size;`, `array = new bool[size];`, then copy each bit.
4. `return *this;`

## Mistakes that cost marks

- No `delete[] array;`: the old array leaks (valgrind "definitely lost").
- `array = other.array;`: both objects share one array, so `b[0] = false;` also changes `a`, and the array is freed twice at the end.
- No self-assignment check: after `delete[] array;`, `array = new bool[size]` is a new array with unset values, and the loop copies it onto itself. valgrind reports uninitialised values when the bits are printed.
