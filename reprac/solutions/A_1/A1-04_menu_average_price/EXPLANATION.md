# A1-04 Explanation: Menu::averagePrice

## What the function must do

`averagePrice(type)` returns the average price of the items of one type: the sum of their prices divided by the number of items. It throws in two cases:

- the type name `type` is not `"Starter"`, `"Main"` or `"Dessert"`: `InvalidType(type)`;
- the menu has no item of that type: `NothingMatchingFilter(type)`. Without this exception, the function would divide by 0.

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

The type name must match exactly. For any other type name, the function throws `InvalidType(type)` and stops. This runs before the loop, so an invalid type name throws `InvalidType` even on an empty menu.

**Step 2: add up and count.**

```cpp
    float total = 0;
    int count = 0;
    for (int i = 0; i < maxSize; i++) {
        if (items[i] != NULL && items[i]->getType() == code) {
            total += items[i]->getPrice();
            count++;
        }
    }
```

- `total` is a `float`, like the prices. An `int` total would drop the decimals of each price.
- `count` is an `int`. It counts the matching items.
- The loop visits every slot. It must not stop at the first match.
- `items[i] != NULL` comes first in the `&&`, so the function never calls `getType()` through `NULL`.
- For a matching item, the price is added to `total` and `count` grows by 1. Both statements are inside the same `if`.

**Step 3: throw or divide.**

```cpp
    if (count == 0) {
        throw NothingMatchingFilter(type);
    }
    return total / count;
```

- The check uses `count`, not `total`. An item can cost 0, and it still counts as an item.
- The check comes before the division. `throw` ends the function, so the division never runs with `count` equal to 0.
- `NothingMatchingFilter(type)` gets the type name. The message is, for example, `Nothing matching filter: Dessert`.
- `total / count` divides a `float` by an `int`. C++ converts `count` to `float`, so the result keeps its decimals.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

The first menu in `main.cpp` has `maxSize` 6:

| Slot | 0 | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|---|
| Item | Garlic bread (S) R45.5 | Beef burger (M) R120 | Veg curry (M) R95.5 | Malva pudding (D) R60 | Soup (S) R50 | `NULL` |

**`showAverage(menu, "Starter")`.** `code` is `'S'`.

| `i` | not `NULL` | type `'S'` | `total` after | `count` after |
|---|---|---|---|---|
| 0 | true | true | 45.5 | 1 |
| 1 | true | false (`'M'`) | 45.5 | 1 |
| 2 | true | false (`'M'`) | 45.5 | 1 |
| 3 | true | false (`'D'`) | 45.5 | 1 |
| 4 | true | true | 95.5 | 2 |
| 5 | false | not evaluated | 95.5 | 2 |

`count` is 2, so there is no throw. The result is 95.5 / 2 = 47.75. The line is `Average Starter price: R47.75`.

**`showAverage(menu, "Main")`.** Slots 1 and 2 match. `total` is 120 + 95.5 = 215.5 and `count` is 2. The result is 107.75.

**`showAverage(menu, "Dessert")`.** Only slot 3 matches. The result is 60 / 1 = 60, printed as `R60`.

**`showAverage(menu, "Drink")`.** Step 1 throws `InvalidType("Drink")`.

**`showAverage(small, "Dessert")`.** The menu `small` has `maxSize` 2. Slot 0 holds Beef burger (M), slot 1 is `NULL`. No item has the type `'D'`, so after the loop `count` is 0. The function throws `NothingMatchingFilter("Dessert")`, and `main` prints `NothingMatchingFilter caught: Exception: Nothing matching filter: Dessert`.

## Common mistakes

- **No `count == 0` check.** For a type with no items, the function computes 0 / 0. For `float` values this does not crash. The result is "not a number". `cout` prints `nan` or `-nan`, depending on the system. With g++ on Linux, the line becomes `Average Dessert price: R-nan` instead of the `NothingMatchingFilter` line. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Declaring `int total`.** Each price is cut to a whole number when it is added: 45.5 becomes 45. The starter average becomes 95 / 2 = 47 (whole-number division), printed as `R47` instead of `R47.75`. g++ gives no warning for this with `-Wall`. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Checking `total == 0` instead of `count == 0`.** The output of `main.cpp` looks right, because no item there costs 0. `main.cpp` does not show this mistake. A menu whose only starter costs R0 does: `averagePrice("Starter")` then throws `NothingMatchingFilter` instead of returning 0.
- **Dividing by `maxSize`.** The empty slots and the items of other types are counted as well. The starter average becomes 95.5 / 6, printed as `R15.9167`. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Checking the count before the type name.** If the `count == 0` test comes first, an invalid type name (count 0) throws `NothingMatchingFilter("Drink")` instead of `InvalidType("Drink")`. The caller's `catch (InvalidType& e)` is skipped, and the line reads `NothingMatchingFilter caught: Exception: Nothing matching filter: Drink`. Check the type name first.
