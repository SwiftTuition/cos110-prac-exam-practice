Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A1-01. Exceptions: the constructors of the exception classes and `printException` (100)

For this question, implement the exception hierarchy in the file `A_1.cpp`: the constructor `Exception(string)`, the member function `printException()`, and the constructor of each of the eight subclasses. The destructor `~Exception()` and the stream insertion `operator<<` are given in `Exception.cpp`.

## UML (only the classes this question needs)

```text
Exception
- msg: string
+ Exception(string)   <- implement
+ ~Exception()   {virtual}
+ printException(): void   <- implement
+ operator<<(ostream&, const Exception&): ostream&   {friend}

InvalidType : Exception
+ InvalidType(string)   <- implement

NothingMatchingFilter : Exception
+ NothingMatchingFilter(string)   <- implement

NothingAboveMinimumValue : NothingMatchingFilter
+ NothingAboveMinimumValue()   <- implement

NothingBelowMaximumValue : NothingMatchingFilter
+ NothingBelowMaximumValue()   <- implement

NotFoundException : Exception
+ NotFoundException()   <- implement

StarterNotFound : NotFoundException
+ StarterNotFound()   <- implement

MainNotFound : NotFoundException
+ MainNotFound()   <- implement

DessertNotFound : NotFoundException
+ DessertNotFound()   <- implement
```

Differences from the partial UML in the exam paper:

- `~Exception()` is virtual, so that the classes are polymorphic.
- `operator<<` is not drawn, but the exam paper says every class has one.
- The exam paper does not give the messages. The messages below are the ones this bank uses. In the exam, the header files and the question text decide.

## Given code you will use

- `Exception::~Exception()` is given. It is `virtual` and does nothing.
- `operator<<(ostream& out, const Exception& e)` is given. It prints `Exception: <msg>` with no newline.

## What the functions must do

1. `Exception(string msg)` stores `msg` in the member `msg`.
2. `printException()` prints `Exception: ` and then `msg`, and ends the line with `endl`. It prints to `cout`.
3. Each subclass constructor stores this message:

| Class | Message stored in `msg` |
|---|---|
| `InvalidType(t)` | `Invalid type: ` followed by the value of `t`, for example `Invalid type: Drink` |
| `NothingMatchingFilter(f)` | `Nothing matching filter: ` followed by the value of `f`, for example `Nothing matching filter: Dessert` |
| `NothingAboveMinimumValue()` | `Nothing matching filter: above minimum value` |
| `NothingBelowMaximumValue()` | `Nothing matching filter: below maximum value` |
| `NotFoundException()`, `StarterNotFound()`, `MainNotFound()`, `DessertNotFound()` | `Item not found` |

More rules:

- `msg` is `private` in `Exception`. A subclass cannot assign to `msg`. It passes its message to the constructor of its direct base class, in the member initialiser list, for example `: Exception("...")`.
- `NothingAboveMinimumValue` and `NothingBelowMaximumValue` are derived from `NothingMatchingFilter`, not directly from `Exception`. Their constructors must call the `NothingMatchingFilter` constructor. The `NothingMatchingFilter` constructor adds `Nothing matching filter: ` in front of the text it gets.
- The three not-found classes are derived from `NotFoundException`. Their message comes from the `NotFoundException` constructor.
- `Exception` and `NothingMatchingFilter` have no default constructor. So the constructors of `InvalidType`, `NothingMatchingFilter`, `NotFoundException`, `NothingAboveMinimumValue` and `NothingBelowMaximumValue` must call their direct base constructor in the initialiser list. If they do not, the code does not compile.
- `NotFoundException()` takes no argument. For the three not-found classes, the call `: NotFoundException()` is optional. If it is left out, C++ calls `NotFoundException()` anyway.

The given `operator<<` functions and the `ExpectedOutput` block apply to this question only. Another question in this bank may print the same class in a different way.

## Build and upload

1. Open a terminal in the `A_1` folder.
2. Run `make A_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`. `-Wall -Werror` turns every warning into an error.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
