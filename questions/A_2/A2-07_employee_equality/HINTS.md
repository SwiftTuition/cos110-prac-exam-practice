# A2-07 hints

Try the question first. Read one hint at a time. The hints go from gentle to specific. They do not give the full answer.

## Hint 1

`a != b` must always be the opposite of `a == b`. You do not need to compare the ID numbers a second time.

## Hint 2

Inside a member function, `*this` is the current object. So `*this == other` calls your own `operator==`.

## Hint 3

`operator!=` can return the opposite (`!`) of that call. Then the two operators can never disagree.
