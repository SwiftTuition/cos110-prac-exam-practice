# A1-02 Explanation: Menu::findFirst

## What the function must do

`findFirst(type)` returns a copy of the first item of one type. The type arrives as a type name: `"Starter"`, `"Main"` or `"Dessert"`. Each `Item` stores its type as one character: `'S'`, `'M'` or `'D'`. So the function first turns the type name into the type code, then searches the array.

There are two ways to fail, and each has its own exception:

- the type name is not valid: `InvalidType(type)`;
- the type name is valid, but no item of that type is on the menu: `StarterNotFound()`, `MainNotFound()` or `DessertNotFound()`.

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

- `type == "Starter"` compares the whole `string` with the text. The comparison is exact. `"starter"` and `"Starters"` are not equal to `"Starter"`.
- Only one branch of the `if` / `else if` chain runs. The first condition that is true sets `code`.
- The final `else` runs when none of the three words matched. `throw` leaves the function at once. Nothing after it in the function runs.
- This step comes before the loop. So `findFirst("Drink")` throws `InvalidType` even on an empty menu. The question requires this order.

**Step 2: search from the front.**

```cpp
    for (int i = 0; i < maxSize; i++) {
        if (items[i] != NULL && items[i]->getType() == code) {
            return *items[i];
        }
    }
```

- The loop visits the slots 0, 1, ..., `maxSize - 1`. It stops before `maxSize`, which is outside the array.
- `items[i] != NULL` checks that the slot holds an item. An empty slot holds `NULL`.
- `items[i]->getType() == code` checks the type. The arrow `->` calls a member function through a pointer.
- `&&` stops at the first false part. For a `NULL` slot the left part is false, so `items[i]->getType()` never runs.
- `return *items[i];` follows the pointer and returns the item. The return type is `Item`, not `Item&`, so the caller gets a copy made by the copy constructor. The item in the menu stays where it is.
- `return` ends the function inside the loop. So the function returns the first match and never looks at later slots.

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

The loop ends without a `return` only when no slot matched. The code still holds the type, so the function picks the matching not-found class. If `code` is neither `'S'` nor `'M'`, it must be `'D'`, so the last line needs no `if`.

Every path of the function ends in a `return` or a `throw`. So g++ gives no "control reaches end of non-void function" warning.

`throw StarterNotFound();` creates the object and throws it by value. The caller catches it by reference, `catch (StarterNotFound& e)`.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

The first menu in `main.cpp` has `maxSize` 5:

| Slot | 0 | 1 | 2 | 3 | 4 |
|---|---|---|---|---|---|
| Item | Garlic bread (S) | Beef burger (M) | Veg curry (M) | Malva pudding (D) | `NULL` |

**`showFirst(menu, "Main")`.** Step 1 sets `code` to `'M'`.

| `i` | `items[i] != NULL` | `getType() == 'M'` | action |
|---|---|---|---|
| 0 | true | `'S'`: false | next slot |
| 1 | true | `'M'`: true | return Beef burger |

Slots 2 to 4 are never visited. The line is `First Main: Beef burger (M) R120`.

**`showFirst(menu, "Dessert")`.** `code` is `'D'`. Slots 0, 1 and 2 hold other types. Slot 3 matches, and the function returns Malva pudding. Slot 4 (`NULL`) is never reached.

**`showFirst(menu, "Drink")`.** Step 1 finds no match and throws `InvalidType("Drink")`. The loop never runs. `showFirst` catches it in `catch (InvalidType& e)` and prints `InvalidType caught: Exception: Invalid type: Drink`.

**`showFirst(dessertsOnly, "Starter")`.** This menu has `maxSize` 3: slot 0 is Ice cream (D), slots 1 and 2 are `NULL`. `code` is `'S'`.

| `i` | `items[i] != NULL` | `getType() == 'S'` | action |
|---|---|---|---|
| 0 | true | `'D'`: false | next slot |
| 1 | false | not evaluated | next slot |
| 2 | false | not evaluated | next slot |

`i` becomes 3, `3 < 3` is false, and the loop ends. `code` is `'S'`, so the function throws `StarterNotFound()`. The output is `StarterNotFound caught: Exception: Item not found`.

**`showFirst(empty, "Dessert")`.** Every slot is `NULL`. The loop finds nothing, and the function throws `DessertNotFound()`.

## Common mistakes

- **Throwing the base class `NotFoundException()` for every type.** The message is the same, so it looks right. But the caller's `catch (StarterNotFound& e)` does not accept a `NotFoundException`. In `main.cpp` the object goes to `catch (Exception& e)`, because the `catch (StarterNotFound& e)` block does not fit. The line reads `Exception caught: Exception: Item not found` instead of `StarterNotFound caught: ...`. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **No `NULL` check**, as in `if (items[i]->getType() == code)`. The call goes through a `NULL` pointer as soon as the search reaches an empty slot. In `main.cpp` this happens for `showFirst(dessertsOnly, "Starter")`. Valgrind reports `Invalid read`, and the program stops with a segmentation fault. The mark is 0.
- **Using the first letter of the type name as the code**, as in `char code = type[0];`. Then `"Drink"` gives `'D'`, and the function returns Malva pudding instead of throwing `InvalidType`. `"main"` gives `'m'`, which matches nothing. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Letting an invalid type name reach the not-found code.** For example, after the loop: `if (type == "Starter") throw StarterNotFound(); else if (type == "Main") throw MainNotFound(); else throw DessertNotFound();`. Then `findFirst("Drink")` throws `DessertNotFound` instead of `InvalidType`. In `main.cpp`, the line for `"Drink"` reads `DessertNotFound caught: Exception: Item not found`. Checking the type name first, before the loop, rules this out.
- **Returning a pointer**, as in `return items[i];`. The return type is `Item`, so the build fails.
- **Catching the exception inside `findFirst`.** Then it never reaches the caller. Printing in `findFirst` also adds lines that are not in the expected output.
