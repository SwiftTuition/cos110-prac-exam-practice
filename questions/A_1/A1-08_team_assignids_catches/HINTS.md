# A1-08 hints

Try the question first. Read one hint at a time. The hints go from gentle to specific. They do not give the full answer.

## Hint 1

Each ID number needs its own chance to fail. Think about where a `try` block must start and end so that, after a `catch`, the function still goes on with the next `i`.

## Hint 2

Put the `try` and the `catch` **inside** the loop body. A `try` around the whole loop stops the loop at the first bad ID number.

## Hint 3

The two cases that are not errors (`i >= size` and an empty slot) do not need a `try`. Check them first. Add 1 to the count only after `setIDNum` returns without throwing.
