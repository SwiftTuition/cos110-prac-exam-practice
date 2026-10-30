# A1-09 hints

Try the question first. Read one hint at a time. The hints go from gentle to specific. They do not give the full answer.

## Hint 1

An `InvalidIDException` object is also an `Exception` object. So a `catch (Exception& e)` block accepts both types.

## Hint 2

When an exception is thrown, C++ tries the `catch` blocks from top to bottom and uses the first one that fits. Ask yourself which of your two blocks would take an `InvalidIDException`.

## Hint 3

The `catch` block for the derived class must come before the `catch` block for its base class. In the opposite order, `-Wall -Werror` stops the build with "exception of type 'InvalidIDException' will be caught by earlier handler".
