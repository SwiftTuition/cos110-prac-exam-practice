# A1-08 Explanation: Menu::printSummary (catch order)

## What the function must do

`printSummary(type, minPrice)` is the caller side of the exceptions. It calls two given functions that can throw, `findFirst` and `numberAbove`. If both calls work, it prints one summary line and returns `true`. If either call throws, it catches the exception, prints a line that depends on the exception's class, and returns `false`. No exception may leave the function.

The function is not in the exam paper. The exam's catching code needs the same skill: `catch` blocks by reference, in the right order.

## The classes that can arrive

| Call | Can throw |
|---|---|
| `findFirst(type)` | `InvalidType`, `StarterNotFound`, `MainNotFound`, `DessertNotFound` |
| `numberAbove(type, minPrice)` | `InvalidType`, `NothingAboveMinimumValue` |

The family tree of all nine exception classes is below. `NothingBelowMaximumValue` is drawn in grey: neither call throws it, so it cannot arrive in `printSummary`.

![Exception at the top. Its subclasses are InvalidType, NothingMatchingFilter and NotFoundException. NothingMatchingFilter has the subclasses NothingAboveMinimumValue and NothingBelowMaximumValue. NotFoundException has the subclasses StarterNotFound, MainNotFound and DessertNotFound.](exceptions_tree.svg)

An object of a derived class is also an object of every class above it. A `DessertNotFound` object is a `NotFoundException` and an `Exception` too.

## How the solution works

**The `try` block.**

```cpp
    try {
        Item first = findFirst(type);
        int count = numberAbove(type, minPrice);
        cout << type << ": first is " << first << ", " << count << " above R" << minPrice << endl;
        return true;
    }
```

- The two calls run in order. If `findFirst` throws, `numberAbove` never runs. If `numberAbove` throws, the `cout` line never runs.
- The `cout` line comes after both calls. So the summary line appears only when both calls worked. Nothing of it is printed for a failed call.
- `Item first = findFirst(type);` declares and fills `first` in one statement. `Item` has no default constructor, so `Item first;` on its own line does not compile.
- `return true;` is inside the `try` block. It runs only when nothing was thrown.

**The `catch` blocks.** When an exception is thrown, C++ looks at the `catch` blocks from top to bottom. It runs the first block whose class fits the object, and skips the rest.

```cpp
    } catch (DessertNotFound& e) {
        cout << "No desserts yet. ";
        e.printException();
    } catch (NotFoundException& e) {
        cout << "Not on the menu. ";
        e.printException();
    } catch (NothingAboveMinimumValue& e) {
        cout << "Nothing above R" << minPrice << ". ";
        e.printException();
    } catch (Exception& e) {
        cout << "Request failed. ";
        e.printException();
    }
    return false;
```

- `DessertNotFound&` comes before `NotFoundException&`. In the other order, the `NotFoundException&` block would catch every `DessertNotFound`, and the `DessertNotFound&` block could never run. g++ reports this as "exception of type 'DessertNotFound' will be caught by earlier handler", and `-Werror` turns it into a build error.
- `NotFoundException&` catches the other two not-found classes: `StarterNotFound` and `MainNotFound`.
- `NothingAboveMinimumValue&` is not related to the not-found classes, so its place among them does not matter. It must come before `Exception&`.
- A `catch (NothingMatchingFilter& e)` block would also catch it here, because no other filter exception can reach `printSummary`. The question asks for `NothingAboveMinimumValue&`.
- `Exception&` comes last. It catches everything that the blocks above did not catch. Here that is `InvalidType`.
- Each block catches by reference (`&`). The object is not copied. Here, `Exception` has a virtual destructor. So catching it by value gives the warning "catching polymorphic type 'class Exception' by value", and `-Werror` turns it into a build error.
- `e.printException()` prints `Exception: `, the message and the newline. The line starts with the block's own prefix, so the two parts form one line.
- When a `catch` block ends, the function continues after the last `catch` block. So `return false;` runs.

## Trace

The calls below are in `main.cpp`. Open it to see the full code.

The menu in `main.cpp` has `maxSize` 5: slot 0 Garlic bread (S) R45.5, slot 1 Beef burger (M) R120, slot 2 Veg curry (M) R95.5, slots 3 and 4 `NULL`. The helper `check` calls `printSummary` and then prints `  returned true` or `  returned false`.

| Call | What happens in the `try` block | First `catch` that fits | Line printed |
|---|---|---|---|
| `("Main", 100)` | `findFirst` returns Beef burger. `numberAbove` counts Beef burger (120 > 100); Veg curry fails (95.5 > 100 is false). The count is 1. | none | `Main: first is Beef burger (M) R120, 1 above R100` |
| `("Starter", 45.5)` | `findFirst` returns Garlic bread. `numberAbove`: 45.5 > 45.5 is false, the count is 0, it throws `NothingAboveMinimumValue`. | `NothingAboveMinimumValue&` | `Nothing above R45.5. Exception: Nothing matching filter: above minimum value` |
| `("Dessert", 10)` | `findFirst` finds no `'D'` and throws `DessertNotFound`. | `DessertNotFound&` | `No desserts yet. Exception: Item not found` |
| `("Drink", 10)` | `findFirst` throws `InvalidType("Drink")`. | `Exception&` (the three blocks above do not fit) | `Request failed. Exception: Invalid type: Drink` |
| `empty, ("Starter", 0)` | `findFirst` throws `StarterNotFound`. | `NotFoundException&` (`DessertNotFound&` does not fit) | `Not on the menu. Exception: Item not found` |
| `empty, ("Main", 0)` | `findFirst` throws `MainNotFound`. | `NotFoundException&` | `Not on the menu. Exception: Item not found` |

For the `"Drink"` call, C++ checks the blocks in order. An `InvalidType` object is not a `DessertNotFound`, not a `NotFoundException`, not a `NothingAboveMinimumValue`. It is an `Exception`, so the last block runs.

## Common mistakes

- **`catch (Exception& e)` first.** No later block can ever run. g++ reports "exception of type 'DessertNotFound' will be caught by earlier handler", with a note "for type 'Exception'". With `-Werror` the build stops, and the mark is 0.
- **`catch (NotFoundException& e)` before `catch (DessertNotFound& e)`.** Same problem, same build error: the `DessertNotFound` block can never run.
- **Catching by value**, as in `catch (Exception e)`. In this question, g++ reports "catching polymorphic type 'class Exception' by value" under `-Wall`, and with `-Werror` the build stops. The warning appears only because `Exception` has a virtual destructor here. If the exam's `Exception` has no virtual function, `catch (Exception e)` compiles without a warning. It still copies only the `Exception` part of the object. Always catch by reference.
- **No `catch (Exception& e)` block.** `InvalidType` then leaves `printSummary`. In `main.cpp`, the call `check(menu, "Drink", 10)` ends the program with "terminate called after throwing an instance of 'InvalidType'". The remaining lines are missing, and valgrind reports the abnormal end. The mark is 0.
- **Printing part of the summary before `numberAbove`.** For example, `cout << type << ": first is " << first << ", ";` placed between the two calls. When `numberAbove` throws, that text is already printed, and the `catch` line continues it: `Starter: first is Garlic bread (S) R45.5, Nothing above R45.5. Exception: ...`. With this mistake, the output of `main.cpp` does not match the `ExpectedOutput` block.
- **`catch (const Exception& e)`.** `printException()` is not a `const` member function, so `e.printException()` does not compile on a `const` reference. The error says "passing 'const DessertNotFound' as 'this' argument discards qualifiers".
- **Rethrowing or printing nothing.** The question requires a line for every case and no exception leaving the function.
