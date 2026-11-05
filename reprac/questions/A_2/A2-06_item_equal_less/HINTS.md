# A2-06 hints

## Hint 1

Both operators are member functions. The left operand is the object itself (`this`). The right operand is the parameter `other`. Inside a member function you may read the private members of `other` too.

## Hint 2

Both functions end in `const` in `Item.h`. Write `const` after the parameter list in `A_2.cpp` as well, or the definition does not match the declaration.

## Hint 3

`operator==` joins three comparisons with `&&`. `operator<` compares one member only. For two equal prices, `a < b` and `b < a` are both false.
