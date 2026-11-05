# A1-08 hints

## Hint 1

Put both calls, `findFirst` and `numberAbove`, inside one `try` block. Print the summary line after both calls, still inside the `try` block. If a call throws, the rest of the `try` block is skipped.

## Hint 2

A `DessertNotFound` object is also a `NotFoundException` object, and both are `Exception` objects. A `catch (Exception& e)` block accepts every one of them. C++ tries the `catch` blocks from top to bottom and uses the first one that fits.

## Hint 3

Write the derived class first: `DessertNotFound`, then its base class `NotFoundException`. `NothingAboveMinimumValue` can go anywhere before `Exception`. `Exception` comes last. In the opposite order, g++ warns "exception of type 'DessertNotFound' will be caught by earlier handler", and `-Werror` turns the warning into a build error.
