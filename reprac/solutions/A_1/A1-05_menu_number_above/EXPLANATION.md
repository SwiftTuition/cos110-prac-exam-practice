# A1-05 Explanation: Menu::numberAbove

## What the function must do

`numberAbove(type, value)` counts the items of one type whose price is greater than `value`. It returns the count. It throws in two cases:

- the type name `type` is not `"Starter"`, `"Main"` or `"Dessert"`: `InvalidType(type)`;
- the count is 0: `NothingAboveMinimumValue()`.

"Greater than" is strict. An item that costs exactly `value` does not count.

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

The type name is compared exactly. If it is none of the three names, the function throws `InvalidType(type)` and stops. This happens before the loop, so an invalid type name throws even when the menu is empty.

**Step 2: count.**

```cpp
    int count = 0;
    for (int i = 0; i < maxSize; i++) {
        if (items[i] != NULL && items[i]->getType() == code && items[i]->getPrice() > value) {
            count++;
        }
    }
```

- `count` starts at 0 before the loop.
- The loop visits every slot from 0 to `maxSize - 1`. It does not stop early: every matching item must be counted.
- The condition has three parts joined by `&&`. All three must be true to count the item:
  1. `items[i] != NULL`: the slot holds an item. This part is first, so for an empty slot C++ stops here and never calls a function through `NULL`.
  2. `items[i]->getType() == code`: the item has the right type. Without this part, items of other types would be counted.
  3. `items[i]->getPrice() > value`: the price is strictly greater. An equal price gives false.

**Step 3: throw or return.**

```cpp
    if (count == 0) {
        throw NothingAboveMinimumValue();
    }
    return count;
```

A count of 0 throws `NothingAboveMinimumValue()`. This class takes no argument. Its message is always `Nothing matching filter: above minimum value`. Otherwise the function returns the count.

The check `count == 0` covers two different situations: no item of that type at all, and items of that type that are all too cheap. Both throw the same exception.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

The menu in `main.cpp` has `maxSize` 6:

| Slot | 0 | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|---|
| Item | Garlic bread (S) R45.5 | Beef burger (M) R120 | Veg curry (M) R95.5 | Malva pudding (D) R60 | Soup (S) R50 | `NULL` |

**`show(menu, "Main", 100)`.** `code` is `'M'`, `value` is 100.

| `i` | not `NULL` | type `'M'` | price `> 100` | `count` after |
|---|---|---|---|---|
| 0 | true | false (`'S'`) | not evaluated | 0 |
| 1 | true | true | 120: true | 1 |
| 2 | true | true | 95.5: false | 1 |
| 3 | true | false (`'D'`) | not evaluated | 1 |
| 4 | true | false (`'S'`) | not evaluated | 1 |
| 5 | false | not evaluated | not evaluated | 1 |

The count is 1, so the function returns 1. The line is `Main above R100: 1`.

**`show(menu, "Main", 120)`.** Slot 1: `120 > 120` is false. Slot 2: `95.5 > 120` is false. The count stays 0, and the function throws `NothingAboveMinimumValue()`. The caller's `catch (NothingAboveMinimumValue& e)` prints `NothingAboveMinimumValue caught: Exception: Nothing matching filter: above minimum value`.

**`show(menu, "Starter", 45.5)`.** Slot 0: Garlic bread costs 45.5, and `45.5 > 45.5` is false. Slot 4: Soup costs 50, and `50 > 45.5` is true. The count is 1.

**`show(menu, "Dessert", 100)`.** Only slot 3 is a dessert, and `60 > 100` is false. The count is 0, so the function throws.

**`show(menu, "Drink", 10)`.** Step 1 throws `InvalidType("Drink")`. The loop never runs.

## Common mistakes

- **Writing `>=` instead of `>`.** Equal prices are then counted. `show(menu, "Main", 120)` returns 1 instead of throwing, and `show(menu, "Starter", 45.5)` returns 2. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Leaving out the type check in the condition.** There are two versions of this mistake.
  - The solution's Step 1 is kept, but `items[i]->getType() == code` is removed from the condition. Then `code` is set and never read. g++ reports "variable 'code' set but not used", and `-Werror` makes this a build error. The mark is 0.
  - The type name is only checked (`if (type != "Starter" && type != "Main" && type != "Dessert") throw InvalidType(type);`), and the loop counts every item. Then every item above the value counts, of any type. `show(menu, "Starter", 45.5)` counts Beef burger, Veg curry, Malva pudding and Soup and returns 4. `show(menu, "Dessert", 100)` counts Beef burger and returns 1. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Throwing `NothingMatchingFilter(type)`.** It is the base class of `NothingAboveMinimumValue`. The caller's `catch (NothingAboveMinimumValue& e)` does not accept a base-class object. A later `catch` block prints `NothingMatchingFilter caught: Exception: Nothing matching filter: Main`. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **No `NULL` check.** Slot 5 of the main menu is empty. The first call already reaches it and calls `getType()` through `NULL`. Valgrind reports an invalid read, and the program stops with a segmentation fault before it prints anything. The mark is 0.
- **Checking the type name only when the count is 0.** For an invalid type name the count is always 0, so the output can be the same. But the loop then reads every slot first, and one `if` does two jobs. Checking the type name before the loop is clearer and is what the question asks.
