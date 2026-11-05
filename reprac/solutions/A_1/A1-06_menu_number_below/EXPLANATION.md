# A1-06 Explanation: Menu::numberBelow

## What the function must do

`numberBelow(type, value)` counts the items of one type whose price is less than `value`. It returns the count. It throws in two cases:

- the type name `type` is not `"Starter"`, `"Main"` or `"Dessert"`: `InvalidType(type)`;
- the count is 0: `NothingBelowMaximumValue()`.

"Less than" is strict. An item that costs exactly `value` does not count.

The function has the same shape as `numberAbove`, with two changes: the comparison (`<`) and the exception class (`NothingBelowMaximumValue`). If you copy `numberAbove` and miss one of these changes, the output is wrong.

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

The type name is compared exactly. Any other type name throws `InvalidType(type)` before the loop, so an invalid type name throws even on an empty menu.

**Step 2: count.**

```cpp
    int count = 0;
    for (int i = 0; i < maxSize; i++) {
        if (items[i] != NULL && items[i]->getType() == code && items[i]->getPrice() < value) {
            count++;
        }
    }
```

- The loop visits every slot from 0 to `maxSize - 1`.
- The three parts of the condition must all be true:
  1. `items[i] != NULL`: the slot holds an item. It is first, so C++ never calls a function through `NULL`.
  2. `items[i]->getType() == code`: the item has the right type.
  3. `items[i]->getPrice() < value`: the price is strictly less than `value`.
- `&&` stops at the first false part. For an item of another type, the price is not read.

**Step 3: throw or return.**

```cpp
    if (count == 0) {
        throw NothingBelowMaximumValue();
    }
    return count;
```

`NothingBelowMaximumValue()` takes no argument. Its message is `Nothing matching filter: below maximum value`. The class is derived from `NothingMatchingFilter`, so a caller may also catch it as a `NothingMatchingFilter&` or an `Exception&`.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

The menu in `main.cpp` has `maxSize` 6:

| Slot | 0 | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|---|
| Item | Garlic bread (S) R45.5 | Beef burger (M) R120 | Veg curry (M) R95.5 | Malva pudding (D) R60 | Soup (S) R50 | `NULL` |

**`show(menu, "Main", 100)`.** `code` is `'M'`, `value` is 100.

| `i` | not `NULL` | type `'M'` | price `< 100` | `count` after |
|---|---|---|---|---|
| 0 | true | false (`'S'`) | not evaluated | 0 |
| 1 | true | true | 120: false | 0 |
| 2 | true | true | 95.5: true | 1 |
| 3 | true | false (`'D'`) | not evaluated | 1 |
| 4 | true | false (`'S'`) | not evaluated | 1 |
| 5 | false | not evaluated | not evaluated | 1 |

The function returns 1. The line is `Main below R100: 1`.

**`show(menu, "Main", 200)`.** Both mains are below 200. The count is 2.

**`show(menu, "Main", 95.5)`.** Slot 1: `120 < 95.5` is false. Slot 2: `95.5 < 95.5` is false. The count stays 0, so the function throws `NothingBelowMaximumValue()`. `main` prints `NothingBelowMaximumValue caught: Exception: Nothing matching filter: below maximum value`.

**`show(menu, "Starter", 50)`.** Garlic bread: `45.5 < 50` is true. Soup: `50 < 50` is false. The count is 1.

**`show(menu, "Dessert", 60)`.** Malva pudding costs exactly 60, and `60 < 60` is false. The count is 0, so the function throws.

**`show(menu, "Desserts", 60)`.** `"Desserts"` is not `"Dessert"`. Step 1 throws `InvalidType("Desserts")`.

## Common mistakes

- **Writing `<=` instead of `<`.** Equal prices are counted. `show(menu, "Main", 95.5)` returns 1 instead of throwing, and `show(menu, "Starter", 50)` returns 2. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Throwing `NothingAboveMinimumValue()`**, for example after copying `numberAbove`. Both classes are derived from `NothingMatchingFilter`, but they are not related to each other. The caller's `catch (NothingAboveMinimumValue& e)` comes first in `main.cpp`, so the line reads `NothingAboveMinimumValue caught: Exception: Nothing matching filter: above minimum value`. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **No `NULL` check.** Slot 5 of the main menu is empty, so the first call reaches a `NULL` pointer. Valgrind reports an invalid read, and the program stops with a segmentation fault. The mark is 0.
- **Leaving out the type part of the condition.** If Step 1 still sets `code`, `code` is never read, and `-Werror` stops the build with "variable 'code' set but not used". If the type name is only validated, items of every type are counted, and the counts are wrong.
- **Returning 0 instead of throwing.** The question asks for an exception when nothing is below the value. A return of 0 prints `Main below R95.5: 0`, and no `catch` block runs.
