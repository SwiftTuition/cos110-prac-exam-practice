# A3-07 hints

Try the question first. Read one hint at a time. The hints go from gentle to specific. They do not give the full answer.

## Hint 1

Think about the state of the new object when the copy constructor starts. What values do `members` and `size` hold before your code gives them values?

## Hint 2

If you reuse `operator=`, look at what the given `operator=` does first: it deletes every employee in `members` and then the array. In a brand-new object, those pointers were never set.

## Hint 3

Give `members` and `size` safe values before you reuse `operator=`: `NULL` and `0`. Deleting `NULL` does nothing, and a loop up to a size of `0` runs zero times. You can set them in the member initialiser list of the constructor.
