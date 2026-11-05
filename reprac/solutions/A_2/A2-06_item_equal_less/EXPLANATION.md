# A2-06 Explanation: Item::operator== and Item::operator<

## What the functions must do

- `a == b` is `true` when the two items have the same type, the same name and the same price.
- `a < b` is `true` when the price of `a` is less than the price of `b`. The type and the name play no part. Equal prices give `false`.

Both operators are `const` member functions. They are not in the exam paper.

## How the solution works

```cpp
bool Item::operator==(const Item& other) const {
    return type == other.type && name == other.name && price == other.price;
}

bool Item::operator<(const Item& other) const {
    return price < other.price;
}
```

**Member operators.** For `a == b`, C++ calls `a.operator==(b)`. Inside the function, `type`, `name` and `price` are the members of `a` (the object `this` points to). `other` is `b`. A member function may read the private members of any `Item`, so `other.type` is allowed.

**The parameter.** `const Item& other` avoids a copy, and it promises that `other` is not changed. It also accepts a temporary item, as in a call such as `compare(Item('S', "Soup", 50), Item('S', "Soup", 50))`.

**The `const` at the end.** `) const {` promises that the function does not change `this` object. It must be written in `A_2.cpp` as well, because it is part of the function's signature. It is also needed for the calls in `main.cpp`: there the items are `const Item&` parameters, and only `const` member functions can be called on them.

**`operator==`, condition by condition.**

- `type == other.type` compares two `char` values.
- `name == other.name` compares two `string` values character by character.
- `price == other.price` compares two `float` values exactly. The prices in this question have an exact `float` value, so this is safe here.
- `&&` makes the result `true` only when all three parts are `true`. It stops at the first `false` part.

**`operator<`.** `price < other.price` is already a `bool`, so the function returns it directly. For equal prices, `<` gives `false`, as the question requires.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

`main.cpp` makes five items: burger (M, Beef burger, 120), curry (M, Veg curry, 95.5), burgerCopy (a copy of burger), cheapBurger (M, Beef burger, 99.5) and soup (S, Soup, 95.5). `compare(a, b)` prints both items, then `a == b` and `a < b`.

| Call | type equal | name equal | price equal | `==` | `a.price < b.price` | `<` |
|---|---|---|---|---|---|---|
| `compare(burger, burgerCopy)` | true | true | true | true | 120 < 120: false | false |
| `compare(burger, cheapBurger)` | true | true | false | false | 120 < 99.5: false | false |
| `compare(cheapBurger, burger)` | true | true | false | false | 99.5 < 120: true | true |
| `compare(curry, soup)` | false | not evaluated | not evaluated | false | 95.5 < 95.5: false | false |
| `compare(soup, curry)` | false | not evaluated | not evaluated | false | 95.5 < 95.5: false | false |

The last part of `main.cpp` finds the cheapest item with `<`. `list` holds burger, curry, cheapBurger and soup, and `cheapest` starts at 0.

| `i` | test `*list[i] < *list[cheapest]` | result | `cheapest` after |
|---|---|---|---|
| 1 | curry 95.5 < burger 120 | true | 1 |
| 2 | cheapBurger 99.5 < curry 95.5 | false | 1 |
| 3 | soup 95.5 < curry 95.5 | false | 1 |

The output is `Cheapest: Veg curry (M) R95.5`. Soup has the same price, but `<` is false for equal prices, so the first cheapest item stays.

## Common mistakes

- **`operator==` compares only the names.** Burger (R120) and cheapBurger (R99.5) then count as equal. The line `compare(burger, cheapBurger)` shows `== true`. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **`operator==` leaves out the type.** `main.cpp` gives the right output, because no two items there share a name and a price. `main.cpp` does not show this mistake. A call such as `compare(Item('S', "Chocolate", 30), Item('D', "Chocolate", 30))` does: this answer says `== true` instead of `== false`.
- **`operator<` uses `<=`.** Equal prices then give `true`. `compare(burger, burgerCopy)` shows `< true`, and the cheapest item becomes Soup. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Leaving out `const` after the parameter list in `A_2.cpp`.** The definition then does not match the declaration in `Item.h`. g++ reports "no declaration matches", and the build stops. The mark is 0.
- **Comparing addresses**, as in `return this == &other;`. Two different objects with the same values (burger and burgerCopy) are then not equal. `compare(burger, burgerCopy)` then prints `== false` instead of `== true`.
- **Writing the operators as free functions** (`bool operator==(const Item& a, const Item& b)`). The header declares member functions, so the free functions are never used, and the members stay undefined. The build fails at link time.
