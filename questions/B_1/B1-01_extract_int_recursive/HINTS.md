# B1-01 hints

Try the question first. Read one hint at a time. The hints go from gentle to specific. They do not give the full answer.

## Hint 1

Find the smallest valid range. An empty range (`start >= end`) is invalid, so the smallest valid range has one character, for example `(2, 3)`. For that range, return that one digit (or `-1` if it is not a digit). This is your base case, so the recursion must stop there and never call `(start, start)`.

## Hint 2

Now make the range one character shorter. The value of `"1234"` is the value of `"123"` times 10, plus 4. Which shorter range of `str` holds `"123"`?

## Hint 3

A `-1` from the shorter range means that range was not valid. The whole answer must then be `-1` too, so check the result of the recursive call before you multiply it by 10.
