# A1-10 hints

Try the question first. Read one hint at a time. The hints go from gentle to specific. They do not give the full answer.

## Hint 1

Only steps 2 and 3 can throw. When one of them throws, which variable still points to the new employee, and who owns it at that moment?

## Hint 2

Put steps 2 and 3 in one `try` block. When the `catch (Exception& e)` block runs, the team does not hold the new employee, so `hire` is its only owner.

## Hint 3

A `catch` block can pass the exception on: `throw;` throws the caught exception again, and `throw e;` throws a copy of it. Free the memory before that line, because nothing after a `throw` runs.
