# A2-07 Explanation: Menu::operator+= grows the array

## What the function must do

`menu += item` adds one item, like `operator+`. The difference is the full menu. `operator+` deletes the item. `operator+=` makes room: it replaces the array with one that is one slot longer and puts the item in the new last slot.

The function is not in the exam paper. A growing array always needs four steps: make a new array, copy the pointers, free the old array, update the size.

## How the solution works

**Part 1: use a free slot.**

```cpp
    for (int i = 0; i < maxSize; i++) {
        if (items[i] == NULL) {
            items[i] = item;
            return *this;
        }
    }
```

This is the loop of `operator+`. If a slot is `NULL`, the item goes there and the function ends. The array keeps its size.

**Part 2: the menu is full, so grow.**

```cpp
    Item** bigger = new Item*[maxSize + 1];
```

`new Item*[maxSize + 1]` makes an array of `maxSize + 1` pointers on the heap. `bigger` points to it. The pointers inside are not set yet.

```cpp
    for (int i = 0; i < maxSize; i++) {
        bigger[i] = items[i];
    }
    bigger[maxSize] = item;
```

- The loop copies the addresses from slots 0 to `maxSize - 1`. It does not copy the items. Both arrays now point to the same items.
- `bigger[maxSize]` is the new last slot. The old array had no slot with this index. The new item goes there. Every slot of `bigger` now has a value.

```cpp
    delete[] items;
    items = bigger;
    maxSize++;
    return *this;
```

- `delete[] items;` frees the old array of pointers. It uses `delete[]` because the array was made with `new[]`. It does not free the items, because `bigger` still points to them.
- `items = bigger;` makes the menu use the new array.
- `maxSize++` records the new length. `operator<<` and `~Menu()` both loop up to `maxSize`, so they now see the new slot.
- `return *this;` returns the menu as `Menu&`, so `(menu += a) += b;` works.

Do the steps in this order: copy, then `delete[] items`. The copy loop reads `items[i]`, so the old array must still exist.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

`main.cpp` makes `Menu menu(2);`.

**`menu += Garlic bread` and `menu += Beef burger`.** Part 1 finds slot 0, then slot 1. The array does not grow. The first print shows `Menu (max 2):` with two items.

**`menu += new Item('D', "Malva pudding", 60);`** Part 1 finds no `NULL` slot. Part 2 runs with `maxSize` 2:

| Step | `items` (old array) | `bigger` | `maxSize` |
|---|---|---|---|
| `new Item*[3]` | [Garlic, Beef] | [?, ?, ?] | 2 |
| copy, `i = 0` | [Garlic, Beef] | [Garlic, ?, ?] | 2 |
| copy, `i = 1` | [Garlic, Beef] | [Garlic, Beef, ?] | 2 |
| `bigger[2] = item` | [Garlic, Beef] | [Garlic, Beef, Malva] | 2 |
| `delete[] items` | freed | [Garlic, Beef, Malva] | 2 |
| `items = bigger; maxSize++` | (now the new array) | | 3 |

The second print shows `Menu (max 3):` with three items.

**`(menu += Veg curry) += Ice cream;`** The menu is full again. The first call grows the array from 3 to 4 slots and puts Veg curry in slot 3. It returns `menu`. The second call finds no `NULL` slot either, grows the array from 4 to 5 slots and puts Ice cream in slot 4. The third print shows `Menu (max 5):` with five items.

At the end, `~Menu()` deletes the five items and the last array. Each old array was freed during its own `operator+=` call.

## Common mistakes

- **No `delete[] items;`.** The old arrays of pointers are never freed. The output is right, but valgrind reports `definitely lost` memory: one block for each time the menu grew. Memory marks are lost.
- **Deleting the items as well**, with a loop of `delete items[i];` before `delete[] items;`. The new array then points to freed items. The next print reads them, and at the end `~Menu()` deletes them a second time. The freed memory can still hold the old values, so the printed output can look right. Valgrind still reports many errors, starting with `Invalid read`.
- **Forgetting `maxSize++`.** The new last slot is outside the loops of `operator<<` and `~Menu()`. The new item is not printed, and it is never deleted. The second print shows `Menu (max 2):` again, and valgrind reports a leak.
- **Growing every time, even when a slot is free.** Without Part 1, each of the first two `+=` calls adds a slot to the new menu of size 2. The first print then shows `Menu (max 4):`, with two empty slots in front and the two items in slots 2 and 3. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **`delete items;` instead of `delete[] items;`.** Memory made with `new[]` must be freed with `delete[]`. Valgrind reports `Mismatched free() / delete / delete []`.
- **Copying the items with `new Item(*items[i])`.** The old items are then never deleted, and valgrind reports a leak for each one.
