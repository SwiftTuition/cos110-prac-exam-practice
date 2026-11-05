# A1-03 Explanation: Menu::findLast

## What the function must do

`findLast(type)` returns a copy of the last item of one type: the matching item with the highest index. It throws `InvalidType(type)` for a type name that is not `"Starter"`, `"Main"` or `"Dessert"`. It throws `StarterNotFound()`, `MainNotFound()` or `DessertNotFound()` when no item of that type is on the menu.

The function is `findFirst` with one change: the loop runs from the back of the array to the front. The first match it meets is then the last item of that type.

## How the solution works

**Step 1: turn the type name into a type code.**

```cpp
    char code;
    if (type == "Starter") {
        code = 'S';
    } else if (type == "Main") {
        code = 'M';
    } else if (type == "Dessert") {
        code = 'D';
    } else {
        throw InvalidType(type);
    }
```

The comparison `type == "Main"` is exact and case-sensitive. If none of the three words matches, the `else` branch throws `InvalidType(type)` and the function ends. This step runs before the loop, so an invalid type name throws `InvalidType` even when the menu is empty.

**Step 2: search from the back.**

```cpp
    for (int i = maxSize - 1; i >= 0; i--) {
        if (items[i] != NULL && items[i]->getType() == code) {
            return *items[i];
        }
    }
```

- `int i = maxSize - 1` starts at the last valid index. The index `maxSize` is outside the array.
- `i >= 0` keeps slot 0 in the search. With `i > 0`, slot 0 would never be checked.
- `i--` moves one slot to the front each time.
- `items[i] != NULL` comes first in the `&&`. The empty slots are at the back of the array, so a backward loop meets them first. For a `NULL` slot the left part is false, and C++ does not run `items[i]->getType()`.
- `return *items[i];` returns a copy of the item and ends the function. Because the loop runs backward, this is the match with the highest index.
- For a menu of size 0, `i` starts at -1. The condition `-1 >= 0` is false, and the loop body never runs.

**Step 3: nothing matched.**

```cpp
    if (code == 'S') {
        throw StarterNotFound();
    }
    if (code == 'M') {
        throw MainNotFound();
    }
    throw DessertNotFound();
```

The function picks the not-found class that belongs to the type. Every path ends in a `return` or a `throw`, so g++ gives no warning about a missing return value.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

The first menu in `main.cpp` has `maxSize` 6:

| Slot | 0 | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|---|
| Item | Garlic bread (S) | Beef burger (M) | Veg curry (M) | Malva pudding (D) | Soup (S) | `NULL` |

**`showLast(menu, "Main")`.** `code` is `'M'`. The loop starts at `i = 5`.

| `i` | `items[i] != NULL` | `getType() == 'M'` | action |
|---|---|---|---|
| 5 | false | not evaluated | next slot |
| 4 | true | `'S'`: false | next slot |
| 3 | true | `'D'`: false | next slot |
| 2 | true | `'M'`: true | return Veg curry |

The output is `Last Main: Veg curry (M) R95.5`. Beef burger in slot 1 is also a main, but the loop never reaches it.

**`showLast(menu, "Starter")`.** `code` is `'S'`. The loop starts at `i = 5`.

| `i` | `items[i] != NULL` | `getType() == 'S'` | action |
|---|---|---|---|
| 5 | false | not evaluated | next slot |
| 4 | true | `'S'`: true | return Soup |

The function returns Soup, not Garlic bread.

**`showLast(menu, "Drinks")`.** Step 1 throws `InvalidType("Drinks")` before the loop.

**`showLast(mainsOnly, "Main")`.** This menu has `maxSize` 3 and one item, Beef burger, in slot 0.

| `i` | `items[i] != NULL` | `getType() == 'M'` | action |
|---|---|---|---|
| 2 | false | not evaluated | next slot |
| 1 | false | not evaluated | next slot |
| 0 | true | `'M'`: true | return Beef burger |

This call needs `i >= 0`: the only match is in slot 0.

**`showLast(mainsOnly, "Starter")`.** The loop visits slots 2, 1 and 0 and finds no starter. Then `i` becomes -1, `-1 >= 0` is false, and the loop ends. The function throws `StarterNotFound()`.

## Common mistakes

- **Starting at `i = maxSize`.** The first step reads `items[maxSize]`, one slot past the end of the array. Valgrind reports `Invalid read of size 8` on every call that reaches the loop (7 of the 8 calls in `main.cpp`; the `"Drinks"` call throws before the loop). The value read there can be 0, so the printed output can look right. Valgrind still reports the errors, and memory errors cost marks.
- **Writing `i > 0`.** Slot 0 is never checked. In `main.cpp`, `showLast(mainsOnly, "Main")` then throws `MainNotFound` instead of returning Beef burger. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **A forward loop that returns at the first match.** It gives the first match: `Last Starter: Garlic bread` instead of `Last Starter: Soup`. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.

A forward loop that remembers the last match (a variable `Item* last = NULL;` set in the loop) is also correct, but it must then return `*last` after the loop and throw when `last` is still `NULL`.
- **No `NULL` check.** The backward loop meets an empty slot first on any menu that is not full, so the program stops with a segmentation fault on the first call.
- **Throwing `NotFoundException()`** for every type. The caller's `catch (StarterNotFound& e)` does not catch a plain `NotFoundException`, so the wrong `catch` block prints the line.
