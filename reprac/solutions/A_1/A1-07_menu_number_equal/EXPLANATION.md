# A1-07 Explanation: Menu::numberEqual

## What the function must do

`numberEqual(type, value)` counts the items of one type whose price is exactly `value`. It returns the count. It throws in two cases:

- the type name `type` is not `"Starter"`, `"Main"` or `"Dessert"`: `InvalidType(type)`;
- the count is 0: `NothingMatchingFilter(type)`.

The second exception is the base class `NothingMatchingFilter`, not one of its two subclasses. It takes the type name, so the message names the type, for example `Nothing matching filter: Main`.

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

Any type name other than the three names throws `InvalidType(type)` before the loop. An invalid type name therefore throws `InvalidType` even on an empty menu.

**Step 2: count.**

```cpp
    int count = 0;
    for (int i = 0; i < maxSize; i++) {
        if (items[i] != NULL && items[i]->getType() == code && items[i]->getPrice() == value) {
            count++;
        }
    }
```

- The loop visits every slot.
- `items[i] != NULL` is checked first, so C++ never calls `getType()` or `getPrice()` through `NULL`.
- `items[i]->getType() == code` keeps only items of the requested type.
- `items[i]->getPrice() == value` compares two `float` values exactly. In general, `==` on `float` values is risky, because many decimals (such as 0.1) cannot be stored exactly. The prices in this question (45.5, 95.5, 120, 35, 0) can be stored exactly, so `==` gives the expected result here.

**Step 3: throw or return.**

```cpp
    if (count == 0) {
        throw NothingMatchingFilter(type);
    }
    return count;
```

The type name `type` goes into the exception. The caller in `main.cpp` catches it with `catch (NothingMatchingFilter& e)`.

**Why the catch order in `main.cpp` matters here.** The helper `show` has these `catch` blocks, in this order: `InvalidType&`, `NothingAboveMinimumValue&`, `NothingBelowMaximumValue&`, `NothingMatchingFilter&`, `Exception&`.

A `NothingMatchingFilter` object is not an `InvalidType`, not a `NothingAboveMinimumValue` and not a `NothingBelowMaximumValue`. So the first three blocks are skipped, and the `NothingMatchingFilter&` block catches it. A subclass object would stop at its own block first. So the output shows exactly which class the function threw.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

The menu in `main.cpp` has `maxSize` 7:

| Slot | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|---|---|
| Item | Garlic bread (S) R45.5 | Beef burger (M) R120 | Veg curry (M) R95.5 | Malva pudding (D) R60 | Soup (S) R50 | Pap and wors (M) R95.5 | `NULL` |

**`show(menu, "Main", 95.5)`.** `code` is `'M'`, `value` is 95.5.

| `i` | not `NULL` | type `'M'` | price `== 95.5` | `count` after |
|---|---|---|---|---|
| 0 | true | false (`'S'`) | not evaluated | 0 |
| 1 | true | true | 120: false | 0 |
| 2 | true | true | 95.5: true | 1 |
| 3 | true | false (`'D'`) | not evaluated | 1 |
| 4 | true | false (`'S'`) | not evaluated | 1 |
| 5 | true | true | 95.5: true | 2 |
| 6 | false | not evaluated | not evaluated | 2 |

The function returns 2. The line is `Main equal to R95.5: 2`.

**`show(menu, "Main", 100)`.** No main costs 100. The count is 0, and the function throws `NothingMatchingFilter("Main")`. The line is `NothingMatchingFilter caught: Exception: Nothing matching filter: Main`.

**`show(menu, "Dessert", 45.5)`.** Garlic bread costs 45.5, but it is a starter. The type part of the condition is false for it. Malva pudding is the only dessert, and it costs 60. The count is 0, and the message is `Nothing matching filter: Dessert`.

**`show(menu, "Starter", 45.5)`.** Garlic bread matches. Soup costs 50. The count is 1.

**`show(menu, "Snack", 45.5)`.** Step 1 throws `InvalidType("Snack")`.

## Common mistakes

- **Throwing `NothingBelowMaximumValue()`**, for example after copying `numberBelow`. In `main.cpp`, the block `catch (NothingBelowMaximumValue& e)` comes before `catch (NothingMatchingFilter& e)`, so it catches the object. The line reads `NothingBelowMaximumValue caught: Exception: Nothing matching filter: below maximum value`. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Throwing `NothingMatchingFilter` with a fixed text**, for example `NothingMatchingFilter("equal value")`. The right `catch` block runs, but the message is `Nothing matching filter: equal value` instead of naming the type. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Counting items of every type.** If the type name is only validated and the loop has no type check, `show(menu, "Dessert", 45.5)` counts Garlic bread and returns 1 instead of throwing. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block. If Step 1 still sets `code` but the loop never reads it, `-Werror` stops the build with "variable 'code' set but not used".
- **No `NULL` check.** Slot 6 is empty. The first call reaches it and calls a function through `NULL`. The program stops with a segmentation fault, and the mark is 0.

A tolerance such as `fabs(price - value) < 0.01` gives the same result here. But it needs `<cmath>`, and the question asks for equal prices. Use `==`.
