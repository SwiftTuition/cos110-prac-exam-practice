# A2-03 Explanation: operator<< for Exception

## What the function must do

The function prints an exception: `Exception: ` and then the message. It prints no newline. It is the text of `printException()` without the `endl`, written to the stream it is given.

```text
Exception: Invalid type: Drink
```

## How the solution works

```cpp
ostream& operator<<(ostream& out, const Exception& e) {
    out << "Exception: " << e.msg;
    return out;
}
```

**The signature.**

- `ostream& out` is the caller's stream. The function writes into it and returns it.
- `const Exception& e` is a reference to the exception. It is `const`, so the function may only read it.
- The function is a `friend` of `Exception` (see `Exception.h`). A friend may read the private member `e.msg`. The word `friend` is written only in the class.

**The body.** `out << "Exception: " << e.msg;` prints the fixed text and then the stored message. There is no `endl`.

**Why it works for every subclass.** The parameter type is `const Exception&`. A reference to a base class can refer to an object of any derived class. So `cout << InvalidType("Drink")`, `cout << DessertNotFound()` and `cout << e` inside `catch (NotFoundException& e)` all call this one function. A subclass does not need its own `operator<<`. Every subclass object contains the `msg` of `Exception`, and the subclass constructor already filled it.

**Why it does not call `printException()`.** `printException()` is not a `const` member function. `e` is a `const` reference, so `e.printException()` does not compile. `printException()` also prints to `cout` and ends the line, so it cannot write to `out`.

**`return out;`** returns the stream for chains such as `cout << bad << " (InvalidType)" << endl;`.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

| Statement in `main.cpp` | Object that `e` refers to | `e.msg` | Printed |
|---|---|---|---|
| `cout << plain << endl;` | `Exception("Kitchen closed")` | `Kitchen closed` | `Exception: Kitchen closed` |
| `cout << bad << " (InvalidType)" << endl;` | `InvalidType("Drink")` | `Invalid type: Drink` | `Exception: Invalid type: Drink (InvalidType)` |
| `catch (Exception& e) { cout << "Caught: " << e << endl; }` | a thrown `NothingBelowMaximumValue` | `Nothing matching filter: below maximum value` | `Caught: Exception: Nothing matching filter: below maximum value` |
| `catch (NotFoundException& e) { cout << "Caught: " << e << endl; }` | a thrown `DessertNotFound` | `Item not found` | `Caught: Exception: Item not found` |
| `cout << ref << "!" << endl;` | `bad`, through a `const Exception&` | `Invalid type: Drink` | `Exception: Invalid type: Drink!` |

In the second row, the function returns `cout`. Then `" (InvalidType)"` is printed on the same line, because the function printed no newline. The last row works the same way with `"!"`.

In the `catch` rows, `e` has the type `Exception&` or `NotFoundException&`. Both convert to `const Exception&` for the call.

## Common mistakes

- **Calling `e.printException()`.** `e` is `const` and `printException()` is not a `const` member function. The build stops with the error "passing 'const Exception' as 'this' argument discards qualifiers". The mark is 0.
- **Ending with `endl`.** In `main.cpp`, ` (InvalidType)` and `!` then start new lines, and every `endl` in `main` adds an empty line. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Writing to `cout` instead of `out`.** `main.cpp` prints only to `cout`, so its output looks right. `main.cpp` does not show this mistake. Code that writes two exceptions into an `ostringstream`, with ` / ` between them, does: with `cout`, the exceptions appear on the screen at once, and the string stream holds only ` / `.
- **Printing only the message.** Without `Exception: `, every line misses the prefix. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **Writing one `operator<<` per subclass.** It is not needed and not declared in the header. A definition without a declaration in the class is not a friend, so it cannot read the private `msg`.
