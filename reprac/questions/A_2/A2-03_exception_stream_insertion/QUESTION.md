Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A2-03. Operator overloading: `operator<<` for `Exception` (100)

For this question, implement the stream insertion operator `operator<<` for the `Exception` class in the file `A_2.cpp`. It is a `friend` function of `Exception`. Because every exception class is derived from `Exception`, the same function prints every exception type.

## UML (only the classes this question needs)

```text
Exception
- msg: string
+ Exception(string)
+ ~Exception()   {virtual}
+ printException(): void
+ operator<<(ostream&, const Exception&): ostream&   {friend}   <- implement

InvalidType : Exception
+ InvalidType(string)

NothingMatchingFilter : Exception
+ NothingMatchingFilter(string)

NothingAboveMinimumValue : NothingMatchingFilter
+ NothingAboveMinimumValue()

NothingBelowMaximumValue : NothingMatchingFilter
+ NothingBelowMaximumValue()

NotFoundException : Exception
+ NotFoundException()

StarterNotFound : NotFoundException
+ StarterNotFound()

MainNotFound : NotFoundException
+ MainNotFound()

DessertNotFound : NotFoundException
+ DessertNotFound()
```

Differences from the partial UML in the exam paper:

- `~Exception()` is virtual, so that the classes are polymorphic.
- `operator<<` is not drawn, but the exam paper says every class has one. The one for `Exception` is the target.

## Given code you will use

- The constructors and `printException()` are given. `printException()` prints `Exception: <msg>` and a newline. The messages are:

| Class | Message stored in `msg` |
|---|---|
| `InvalidType(t)` | `Invalid type: t` |
| `NothingMatchingFilter(f)` | `Nothing matching filter: f` |
| `NothingAboveMinimumValue()` | `Nothing matching filter: above minimum value` |
| `NothingBelowMaximumValue()` | `Nothing matching filter: below maximum value` |
| `NotFoundException()`, `StarterNotFound()`, `MainNotFound()`, `DessertNotFound()` | `Item not found` |

  In the table, `t` and `f` stand for the text that the constructor receives. The three not-found classes have the same message. Only the `catch` that catches them tells them apart.

## What `operator<<(ostream& out, const Exception& e)` must print

Print `Exception:`, one space, and then the message:

```text
Exception: <msg>
```

For example `Exception: Invalid type: Drink`. This is the text of `printException()`, without the newline.

More rules:

- Print no newline. The caller adds `endl` when it wants one.
- Write to `out`, not to `cout`, and return `out`.
- `e` is a `const` reference. `printException()` is not a `const` member function, so `e.printException()` does not compile here. Read `e.msg` directly; a friend may read a private member.
- Write the word `friend` only in the class. Do not write it again in `A_2.cpp`.

The given `operator<<` functions and the `ExpectedOutput` block apply to this question only. Another question in this bank may print the same class in a different way.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`. `-Wall -Werror` turns every warning into an error.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
