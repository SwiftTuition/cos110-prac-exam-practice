# A2-08 Explanation: Menu::operator-(string) removes an item

## What the function must do

`menu - "Beef burger"` removes the first item with that name. The function deletes the item, then moves every later pointer one slot to the front, so that the filled slots stay together at the front of the array. The last slot becomes `NULL`. If no item has the name, nothing changes. The function returns the menu, so `menu - "a" - "b"` works.

The function is not in the exam paper. Removing from a pointer array needs three steps: free the object, close the gap, and leave no slot pointing to freed memory.

## How the solution works

**Find the item.**

```cpp
    for (int i = 0; i < maxSize; i++) {
        if (items[i] != NULL && items[i]->getName() == name) {
```

- The loop goes from the front, so the first match has the lowest index.
- `items[i] != NULL` comes first. For an empty slot, `&&` stops, and `getName()` is never called through `NULL`.
- `items[i]->getName() == name` compares two `string` values exactly.

**Delete it.**

```cpp
            delete items[i];
```

The menu owns the item, so the menu must free it. After this line, `items[i]` still holds the old address, but the memory there is freed. The next steps overwrite that slot before anything reads it.

**Close the gap.**

```cpp
            for (int j = i; j < maxSize - 1; j++) {
                items[j] = items[j + 1];
            }
```

- `j` starts at the slot of the removed item.
- Each step copies the pointer from the next slot into slot `j`. This moves the pointers, not the items.
- The condition `j < maxSize - 1` stops at the second-last slot. The last step reads `items[maxSize - 1]`, the last valid slot. With `j < maxSize`, the last step would read `items[maxSize]`, outside the array.
- If the removed item is in the last slot, `j` starts at `maxSize - 1`, the condition is false at once, and nothing moves.

**Clear the last slot.**

```cpp
            items[maxSize - 1] = NULL;
            return *this;
```

After the moves, the last two slots hold the same pointer, or both hold `NULL`. The last slot must become `NULL`. Otherwise one item would be in two slots, and `~Menu()` would delete it twice. The function then returns and removes no other item.

**No match.** If the loop ends without a match, the function reaches the last `return *this;` and the menu is unchanged.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

`main.cpp` makes `Menu menu(4);` and adds three items:

| Slot | 0 | 1 | 2 | 3 |
|---|---|---|---|---|
| Item | Garlic bread | Beef burger | Malva pudding | `NULL` |

**`menu - "Beef burger";`** The outer loop: slot 0 is Garlic bread, no match. Slot 1 matches, so `i` is 1. The function deletes Beef burger. The inner loop runs while `j < 3`:

| `j` | `items[j] = items[j + 1]` | slots 0 to 3 after the step |
|---|---|---|
| 1 | `items[1] = items[2]` (Malva pudding) | Garlic, Malva, Malva, `NULL` |
| 2 | `items[2] = items[3]` (`NULL`) | Garlic, Malva, `NULL`, `NULL` |

Then `items[3] = NULL;` (it is already `NULL`) and the function returns. The first print shows Garlic bread, Malva pudding and two empty slots.

**`menu - "Pizza";`** Slots 0 and 1 hold other names. Slots 2 and 3 are `NULL`, so the left part of `&&` is false. The loop ends without a match. The menu does not change.

**`menu - "Garlic bread";`** Slot 0 matches, so `i` is 0. After the delete:

| `j` | `items[j] = items[j + 1]` | slots 0 to 3 after the step |
|---|---|---|
| 0 | `items[0] = items[1]` (Malva pudding) | Malva, Malva, `NULL`, `NULL` |
| 1 | `items[1] = items[2]` (`NULL`) | Malva, `NULL`, `NULL`, `NULL` |
| 2 | `items[2] = items[3]` (`NULL`) | Malva, `NULL`, `NULL`, `NULL` |

Then `items[3] = NULL;`. The second print shows Malva pudding in slot 0.

**`menu + new Item('M', "Veg curry", 95.5);`** The given `operator+` finds the first `NULL` slot, slot 1. Because the gap was closed, the new item goes right after Malva pudding.

## Common mistakes

- **No `delete items[i];`.** The pointer to the item is overwritten by the shift, so the item can never be freed. The output is right, but valgrind reports `definitely lost` memory for Beef burger and Garlic bread. Memory marks are lost.
- **Not setting the last slot to `NULL`.** In `main.cpp` the last slot is already `NULL` every time, so the output is right. `main.cpp` does not show this mistake. Removing the first item from a full menu of size 3 does. The last two slots then hold the same pointer to Ice cream. The print shows Ice cream twice (`[2] Ice cream (D) R35` instead of `[2] empty`), and `~Menu()` deletes it twice. Valgrind reports memory errors (`Invalid read of size 8`).
- **Setting the slot to `NULL` without moving the later items.** The menu then has a gap. After `menu - "Beef burger"`, the print shows `[1] empty` and `[2] Malva pudding`, and the next `operator+` fills the gap. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Shift loop with `j < maxSize`.** The last step reads `items[maxSize]`, one slot past the array. Valgrind reports `Invalid read of size 8`.
- **Removing every item with the name.** The question asks for the first one only. `main.cpp` does not show this mistake. A menu with two items called `Soup` does: after `menu - "Soup"`, one `Soup` must stay.
- **Continuing the outer loop after the removal.** Without `return`, the loop goes on with the next index. The item that moved into slot `i` is then skipped, and a second item with the same name may also be removed.
