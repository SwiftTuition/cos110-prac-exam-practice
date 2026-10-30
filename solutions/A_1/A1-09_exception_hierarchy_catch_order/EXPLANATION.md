# A1-09 Explanation: Team::setMemberID

## What the function must do

The function `setMemberID` sets the ID number of the member in slot `index`. Two kinds of exception can occur. The class `InvalidIDException` is derived from `Exception`, so an `InvalidIDException` is also an `Exception`. The function must catch both kinds. It prints one line for each case and returns `true` for success or `false` for any exception. No exception may leave the function.

## How the solution works

```cpp
bool Team::setMemberID(int index, string idNum) {
    try {
        Employee* employee = getMember(index);
        employee->setIDNum(idNum);
        cout << "Member " << index << ": ID set to " << idNum << endl;
        return true;
```

A `try` block holds code that can throw. If a statement throws, C++ skips the rest of the block and looks for a matching `catch`.

- The given function `getMember(index)` returns an `Employee*`, which is the address of the employee. It throws a plain `Exception("No member at this index")` for a bad index or an empty slot. A bad index or an empty slot is therefore handled by this function, and `setMemberID` does not test the slot itself.
- The arrow `employee->setIDNum(idNum)` calls the function on the employee that the pointer holds. This call can throw an `InvalidIDException` (wrong length or a non-digit) or a plain `Exception` (the gender does not match).
- The `cout` line and `return true;` come after the call. They run only if no exception occurred. If the line came before the call, a failed call would also print `ID set`.

```cpp
    } catch (InvalidIDException& e) {
        // The most derived type must come first.
        cout << "Member " << index << ": bad ID [" << e.getBadID() << "]: " << e.what() << endl;
```

A `catch (InvalidIDException& e)` clause catches an `InvalidIDException`. The `&` makes `e` a reference to the thrown object, so C++ does not copy it. The call `e.getBadID()` gives the rejected ID number. The call `e.what()` gives the message, because `InvalidIDException` passes its message to the constructor of `Exception`. The function `getBadID` exists only in `InvalidIDException`, so this handler can use it.

```cpp
    } catch (Exception& e) {
        cout << "Member " << index << ": " << e.what() << endl;
    }
```

This handler catches every other `Exception`: the gender mismatch from `setIDNum` and the error from `getMember`. It prints only the message.

```cpp
    return false;
}
```

After a handler runs, the function continues after the last `catch` block. The line `return false;` runs for both handlers. The function also needs this line to return a value on every path.

**The order of the handlers.** C++ tests the handlers from top to bottom and uses the first one that fits. An `InvalidIDException` fits both `catch (InvalidIDException&)` and `catch (Exception&)`, because the derived class is also its base class. If the base handler is first, it takes every `InvalidIDException`, and the derived handler never runs. The compiler reports that the derived exception "will be caught by earlier handler". With `-Wall -Werror`, this warning is an error. The derived handler must therefore come first.

The function allocates and frees nothing. The employee belongs to the team.

## Trace

The team has `size` 3. Slot 0 holds Thandi, slot 1 holds Sipho (`'M'`), and slot 2 is empty. The table shows four calls from `main.cpp`.

| Call | `getMember` | `setIDNum` | Exception type | Handler used | Printed | Return |
|---|---|---|---|---|---|---|
| `setMemberID(1, "91052258000")` | returns Sipho | length is 11, not 13, throws `InvalidIDException` | `InvalidIDException` | first | `Member 1: bad ID [91052258000]: ID number must have 13 digits` | `false` |
| `setMemberID(1, "9105220800087")` | returns Sipho | form is valid, digits `0800` give `'F'`, Sipho is `'M'`, throws `Exception` | `Exception` | second | `Member 1: ID number does not match gender` | `false` |
| `setMemberID(2, "8503300800089")` | throws `Exception("No member at this index")` | not called | `Exception` | second | `Member 2: No member at this index` | `false` |
| `setMemberID(1, "9105225800087")` | returns Sipho | digits `5800` give `'M'`, stored | none | none | `Member 1: ID set to 9105225800087` | `true` |

For the second call, an `Exception` is not an `InvalidIDException`, so the first handler does not fit. C++ moves on to the second handler. For the third call, `setIDNum` is never reached, because `getMember` throws first.

In `main.cpp`, the calls for index 0 and the last call for index 1 return `true`. The value of `count` is 2.

The output of `main.cpp` is:

```text
Member 0: ID set to 9702140123081
Member 1: bad ID [91052258000]: ID number must have 13 digits
Member 1: bad ID [9105225800O87]: ID number must contain only digits
Member 1: ID number does not match gender
Member 2: No member at this index
Member 1: ID set to 9105225800087
IDs set: 2
Team:
  Thandi Mokoena, 29, F, ID: 9702140123081
  Sipho Dlamini, 35, M, ID: 9105225800087
```

## Common mistakes

- **Put `catch (Exception& e)` before `catch (InvalidIDException& e)`.** The compiler reports "exception of type 'InvalidIDException' will be caught by earlier handler". Under `-Wall -Werror` the build fails, and the mark is 0. The main test rejected this change at build time.
- **Catch only `Exception&`.** The code compiles, but an `InvalidIDException` prints as `Member 1: ID number must have 13 digits`. The text `bad ID [...]` is missing, and the output differs. The main test rejected this change.
- **Print `ID set` before the call to `setIDNum`.** A failed call then prints two lines for one call.
- **Leave out the final `return false;`.** The function then has a path that ends without a return value. Under `-Wall -Werror`, the warning `control reaches end of non-void function` is an error.
- **Let a handler return `true`.** The variable `count` in `main.cpp` then counts failed calls, and `IDs set: 2` would show a larger number.
- **Catch nothing for the `getMember` call.** The exception for an empty slot leaves the function. The program stops abnormally, and the mark is 0.
