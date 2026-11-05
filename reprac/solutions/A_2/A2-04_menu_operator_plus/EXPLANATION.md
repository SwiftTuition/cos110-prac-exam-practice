# A2-04 Explanation: Menu::operator+(Item*)

## What the function must do

`menu + item` adds one item to the menu. The item goes into the first empty (`NULL`) slot. If there is no empty slot, the menu is full: the function deletes the item, and the menu stays as it was. In both cases the function returns the menu itself, so that `menu + a + b;` adds two items.

The menu owns every item that is passed to it. The caller writes `menu + new Item(...)` and never deletes that item. So every item must end up either in the array (and `~Menu()` deletes it later) or deleted by this function. Any other path leaks memory.

## How the solution works

```cpp
Menu& Menu::operator+(Item* item) {
    for (int i = 0; i < maxSize; i++) {
        if (items[i] == NULL) {
            items[i] = item;
            return *this;
        }
    }
    delete item;
    return *this;
}
```

**The signature.** `operator+` is a member function. In `menu + p`, the left operand `menu` is the object (`this`), and the right operand `p` is the parameter `item`. The return type `Menu&` is a reference to a menu. The function returns the same menu, not a new one.

**The loop.**

- `for (int i = 0; i < maxSize; i++)` visits the slots from the front. The first `NULL` slot it meets has the lowest index.
- `items[i] == NULL` is true for an empty slot.
- `items[i] = item;` stores the pointer. The item itself is not copied. The array now holds its address.
- `return *this;` ends the function at once. This is what makes the item go into one slot only. `this` is a pointer to the menu, and `*this` is the menu itself. Returning it as `Menu&` returns a reference to the menu.

**After the loop.** The loop ends without a `return` only when no slot was `NULL`. The menu is full. `delete item;` frees the item, because no slot will ever hold it and the caller will not delete it. Then the function returns the menu.

**How the chain works.** `menu + a + b` is read as `(menu + a) + b`. The first call returns `menu` by reference, so the second call is again `menu + b`. If the return type were `Menu` (a copy), the second item would go into a temporary copy of the menu.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

`main.cpp` makes `Menu menu(3);`. All three slots start as `NULL`.

**`menu + new Item('S', "Garlic bread", 45.5);`**

| `i` | `items[i] == NULL` | action |
|---|---|---|
| 0 | true | store Garlic bread in slot 0, return |

**`menu + new Item('M', "Beef burger", 120) + new Item('D', "Malva pudding", 60);`** The first call:

| `i` | `items[i] == NULL` | action |
|---|---|---|
| 0 | false | next slot |
| 1 | true | store Beef burger in slot 1, return |

It returns `menu`, and the second call runs on it:

| `i` | `items[i] == NULL` | action |
|---|---|---|
| 0 | false | next slot |
| 1 | false | next slot |
| 2 | true | store Malva pudding in slot 2, return |

**`menu + new Item('M', "Veg curry", 95.5);`**

| `i` | `items[i] == NULL` | action |
|---|---|---|
| 0 | false | next slot |
| 1 | false | next slot |
| 2 | false | next slot |

`i` becomes 3, and `3 < 3` is false. The loop ends. The function deletes Veg curry and returns. The third print of the menu is the same as the second.

At the end of `main`, `~Menu()` deletes the three items in the array. Veg curry was already deleted by `operator+`. Valgrind reports "All heap blocks were freed".

## Common mistakes

- **No `delete item;` when the menu is full.** Veg curry is then never freed. The output is right, but valgrind reports `definitely lost` memory for the `new Item('M', "Veg curry", 95.5)` in `main.cpp`. A leak costs the memory marks.
- **No `return` inside the loop.** The loop then stores the same pointer in every `NULL` slot. The first call puts Garlic bread in slots 0, 1 and 2. The menu prints Garlic bread three times, and `~Menu()` deletes the same item three times. Valgrind reports memory errors (an `Invalid read of size 8` of the item that was already deleted). With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Replacing the last item when the menu is full**, as in `delete items[maxSize - 1]; items[maxSize - 1] = item;`. The question says the menu does not change. The third print then shows Veg curry instead of Malva pudding. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Returning a copy (`Menu` instead of `Menu&`).** The header fixes the return type as `Menu&`, so a different return type in `A_2.cpp` does not compile.
- **Making a copy of the item (`new Item(*item)`).** The original item is then never deleted, and valgrind reports a leak for each call.
