# A1-01 Explanation: the exception classes

## What the functions must do

The file `A_1.cpp` holds ten short functions: the constructor of `Exception`, the member function `printException()`, and one constructor for each of the eight subclasses. Each constructor only has to put the right text into `msg`. `printException()` prints that text after `Exception: `.

The one idea behind all ten functions: `msg` is `private` in `Exception`. Only the code of `Exception` itself may touch it. A subclass sets it by passing its text to the constructor of the class directly above it.

## How the solution works

**The base constructor.**

```cpp
Exception::Exception(string msg) : msg(msg) {
}
```

The part after the colon is the member initialiser list. `msg(msg)` means: initialise the member `msg` with the parameter `msg`. Inside the brackets, the name `msg` means the parameter. Outside, before the brackets, it means the member. The body is empty because there is nothing else to do.

**`printException()`.**

```cpp
void Exception::printException() {
    cout << "Exception: " << msg << endl;
}
```

It prints to `cout`, not to a stream parameter. It ends with `endl`. The given `operator<<` prints the same text without the newline. In `main.cpp`, the first two lines show the difference: both print `Exception: Kitchen closed`, and the second needs its own `endl`.

**The two direct subclasses that take a string.**

```cpp
InvalidType::InvalidType(string type) : Exception("Invalid type: " + type) {
}

NothingMatchingFilter::NothingMatchingFilter(string filter) : Exception("Nothing matching filter: " + filter) {
}
```

`"Invalid type: " + type` joins a text and a `string`. The result is a new `string`. This string goes to the `Exception` constructor, which stores it in `msg`. The subclass never names `msg`.

**The two classes below `NothingMatchingFilter`.**

```cpp
NothingAboveMinimumValue::NothingAboveMinimumValue() : NothingMatchingFilter("above minimum value") {
}
```

`NothingAboveMinimumValue` is derived from `NothingMatchingFilter`, not from `Exception`. So its initialiser list calls the `NothingMatchingFilter` constructor. That constructor adds `Nothing matching filter: ` in front. The stored message is `Nothing matching filter: above minimum value`. The class passes only the end of the message. `NothingBelowMaximumValue` works the same way with `below maximum value`.

**The not-found classes.**

```cpp
NotFoundException::NotFoundException() : Exception("Item not found") {
}

StarterNotFound::StarterNotFound() : NotFoundException() {
}
```

`NotFoundException` stores `Item not found`. `StarterNotFound`, `MainNotFound` and `DessertNotFound` call the `NotFoundException` constructor, which stores that same message. The three classes differ only in their type. A `catch` block can tell them apart; their text cannot.

Writing `: NotFoundException()` is optional. If you leave it out, C++ calls `NotFoundException()` for you. Writing it makes the chain visible.

**The chain of constructor calls.** When `main` runs `throw NothingAboveMinimumValue();`, these steps happen:

1. `NothingAboveMinimumValue()` calls `NothingMatchingFilter("above minimum value")`.
2. `NothingMatchingFilter` puts `Nothing matching filter: ` in front and calls `Exception("Nothing matching filter: above minimum value")`.
3. The `Exception` constructor stores the text in `msg`. Its body ends.
4. The body of `NothingMatchingFilter` runs. It is empty.
5. The body of `NothingAboveMinimumValue` runs. It is empty.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

`main.cpp` throws one object of each class in a loop. The helper `throwOne(which)` throws a different object for each value of `which`. The three `catch` blocks are ordered with each derived class before its base class.

| `which` | thrown object | first `catch` that fits | printed line |
|---|---|---|---|
| 0 | `InvalidType("Drink")` | `Exception&` (an `InvalidType` object is not a `NothingMatchingFilter` and not a `NotFoundException`) | `Other: Exception: Invalid type: Drink` |
| 1 | `NothingMatchingFilter("Dessert")` | `NothingMatchingFilter&` | `Filter: Exception: Nothing matching filter: Dessert` |
| 2 | `NothingAboveMinimumValue()` | `NothingMatchingFilter&` (its base class) | `Filter: Exception: Nothing matching filter: above minimum value` |
| 3 | `NothingBelowMaximumValue()` | `NothingMatchingFilter&` | `Filter: Exception: Nothing matching filter: below maximum value` |
| 4 | `StarterNotFound()` | `NotFoundException&` | `Not found: Exception: Item not found` |
| 5 | `MainNotFound()` | `NotFoundException&` | `Not found: Exception: Item not found` |
| 6 | `DessertNotFound()` | `NotFoundException&` | `Not found: Exception: Item not found` |

For `which` 6, none of the `if` conditions in `throwOne` is true, so the last line throws `DessertNotFound()`. After `which` 6, the loop condition `which <= 6` is false and the loop ends.

Each line has two parts. The `catch` block prints the prefix, for example `Filter: `. Then `e.printException()` prints `Exception: `, the message and the newline. The call works on a base-class reference: `e` has the type `NothingMatchingFilter&`, but the object is a `NothingAboveMinimumValue`. Its `msg` was set by the constructor chain, so the right text appears.

## Common mistakes

- **Assigning to `msg` in the body of a subclass constructor**, for example `InvalidType::InvalidType(string type) { msg = "Invalid type: " + type; }`. This fails twice. `msg` is private, so the subclass may not use it. Also, without an initialiser list C++ calls `Exception()`, and `Exception` has no default constructor. The build stops with an error, and the mark is 0.
- **Calling the `Exception` constructor from `NothingBelowMaximumValue`**, as in `: Exception("Nothing matching filter: below maximum value")`. A constructor may call only the constructor of its direct base class. `Exception` is not the direct base of `NothingBelowMaximumValue`. The build stops with the error "type 'Exception' is not a direct base of 'NothingBelowMaximumValue'".
- **Passing the whole message to `NothingMatchingFilter`**, as in `: NothingMatchingFilter("Nothing matching filter: above minimum value")`. The `NothingMatchingFilter` constructor adds its prefix again. The line becomes `Filter: Exception: Nothing matching filter: Nothing matching filter: above minimum value`. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Leaving out `endl` in `printException()`.** The next output then continues on the same line. In `main.cpp`, the first two lines join into `Exception: Kitchen closedException: Kitchen closed`, and every caught exception runs into the next line. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Spelling a message differently**, for example `Invalid Type:` or `Item not found.` with a full stop. The output must match the table in the question exactly.
