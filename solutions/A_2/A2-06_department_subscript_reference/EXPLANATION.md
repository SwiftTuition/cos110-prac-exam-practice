# A2-06 Explanation: Department::operator[] returning Team*&

## What the function must do

The function lets code write `(*dev)[i]` to reach slot `i` of the `teams` array in a `Department`. The function returns the slot itself, not a copy. The caller can then read the pointer in the slot, call a function through it, or store a new pointer in the slot.

If the index is outside the array, the function throws an `Exception`. An empty slot is not an error. The function returns the `NULL` pointer in that slot.

## How the solution works

```cpp
Team*& Department::operator[](int index) {
    if (index < 0 || index >= size) {
        throw Exception("Index out of bounds");
    }
    // Return the slot itself (not a copy), so the caller can change what it points to.
    return teams[index];
}
```

**The return type.** `Team*&` reads from right to left as "a reference to a pointer to a `Team`".

- A pointer holds the address of an object. `Team*` is a pointer to a `Team`.
- A reference is another name for an existing variable. A reference to a pointer is another name for the pointer variable itself.
- `teams` is an array of `Team*` values. The element `teams[index]` is one pointer variable. The function returns a reference to that variable.

Because the caller receives the variable itself, an assignment such as `(*dev)[0] = new Team(2);` changes the real slot in the array. If the function returned a copy of the pointer, the assignment would change only the copy. The array would stay unchanged.

**The operator.** `operator[]` is an overloaded operator. It gives meaning to `dev[i]` for a `Department`. In `main.cpp`, `dev` is a pointer, so the code writes `(*dev)[0]`. The `*` turns the pointer into the object, and then `[0]` calls the operator.

**The `if` condition.** `if (index < 0 || index >= size)` checks that the index is a valid slot number.

- `index < 0` catches a negative index. An array has no slot -1.
- `index >= size` catches an index past the end. The last valid index is `size - 1`. A department of size 0 has no valid index, and this test catches index 0 for that department.
- The check comes before `teams[index]`. The expression `teams[index]` with a bad index would refer to memory outside the array.

The condition has no test for `NULL`. An empty slot is a valid slot. The caller must be able to read it, test it or fill it. The code in `main.cpp` first fills each empty slot through this operator. A `NULL` test would throw before the slot ever gets a team.

**The throw.** `throw Exception("Index out of bounds");` creates an `Exception` object with that message. The function stops at this point. The program jumps to the nearest matching `catch`. The function does not print and does not catch. In `main.cpp`, the block `catch (Exception& e)` receives the object by reference and prints `e.what()`. If no `catch` handles the throw, the program ends abnormally and the mark is 0.

**The return.** `return teams[index];` returns the array element itself. The function must not copy the pointer into a local variable first. A local variable ends when the function ends, so a reference to it would not be valid. The compiler reports this under `-Wall -Werror`.

**Ownership.** The department owns its teams and deletes every slot in its destructor. If the caller stores a new pointer into a slot that already holds a team, the old team is lost unless the caller deletes it first. The operator does not delete anything. In `main.cpp`, the swap moves pointers between slots and creates no new team, so each team is still deleted once.

## Trace

The department `dev` has size 3. After the first lines of `main`, slot 0 holds the team of Thandi and Sipho (call it team A). Slot 1 is `NULL`. Slot 2 holds the team of Anna (call it team B).

The swap in `main.cpp` has three statements.

| Statement | Index checks | What the operator returns | Slots after the statement (0, 1, 2) |
|---|---|---|---|
| `Team* temp = (*dev)[0];` | 0 is in range | the slot 0 variable, read as a value | A, `NULL`, B (`temp` holds A) |
| `(*dev)[0] = (*dev)[2];` | 0 and 2 are in range | the slot 2 variable is read (B), the slot 0 variable is assigned | B, `NULL`, B |
| `(*dev)[2] = temp;` | 2 is in range | the slot 2 variable is assigned | B, `NULL`, A |

Then `(*dev)[3] = NULL;` runs inside a `try` block. The test `index >= size` is `3 >= 3`, which is true. The function throws before any assignment. The `catch` block prints the message.

The second `cout << *dev;` prints team B first and team A second. The ExpectedOutput of `main.cpp` ends with:

```text
Development (cost R75000)
Team:
  Anna Botha, 41, F, ID: none
Team:
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
Caught: Index out of bounds
```

## Common mistakes

1. **Allowing `index == size`.** Code with `index > size` accepts index 3 for a department of size 3. The assignment `(*dev)[3] = NULL;` in `main` then writes outside the array. Valgrind reports `Invalid write of size 8`. No exception is thrown, so the line `Caught: Index out of bounds` is missing from the output.
2. **Throwing for an empty slot.** The first statement `(*dev)[0] = new Team(2);` in `main.cpp` uses a `NULL` slot. If the function throws for `NULL`, this statement throws outside any `try` block. The exception is not caught. The program prints `terminate called after throwing an instance of 'Exception'` and stops with `SIGABRT` before it prints anything.
3. **Returning a copy or a local variable.** A version such as `Team* t = teams[index]; return t;` returns a reference to a local variable. The compiler gives `reference to local variable 't' returned`, and `-Werror` turns this warning into an error. A return type of `Team*` also does not match the declaration in `Department.h`. The compiler reports `no declaration matches 'Team* Department::operator[](int)'`.
4. **Reading `teams[index]` before the range check.** A bad index then reads memory outside the array. Valgrind reports `Invalid read of size 8` for each bad index. The printed output can still look correct, so only valgrind shows the mistake. The range check must come first.
