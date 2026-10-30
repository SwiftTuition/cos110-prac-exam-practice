# A2-12 Explanation: Team::operator() finds a surname

## What the function must do

The function call operator lets code write `team("Dlamini")` as if the team were a function. The function searches the team for a member with the given surname. It returns the index of the first member that matches.

If no member has that surname, the function returns `-1`. The match is exact. Capital letters and spaces matter. Empty slots are skipped.

## How the solution works

```cpp
int Team::operator()(string surName) const {
    for (int i = 0; i < size; i++) {
        if (members[i] != NULL && members[i]->getSurName() == surName) {
            return i;
        }
    }
    return -1;
}
```

**The signature.** `int Team::operator()(string surName) const` has these parts.

- `operator()` is an overloaded operator. It gives meaning to a call such as `(*team)("Dlamini")`. In `main.cpp`, `team` is a pointer, so the code writes `(*team)`. The `*` turns the pointer into the object, and then `("Dlamini")` calls the operator.
- The parameter `string surName` is a copy of the surname to find.
- The return type `int` is the index of the match, or `-1`. The value `-1` is never a valid index, so it signals "not found".
- The `const` after the parameter list makes this a `const` member function. It promises not to change the team. The edge test calls the operator on a `const Team&`, which is possible only for a `const` member function. The definition must match the declaration in `Team.h`.

**Data.** `members` is an array of pointers to `Employee`. `size` is the length of the array. A pointer holds the address of an object. An empty slot holds `NULL`, which means no address.

**The loop.** `for (int i = 0; i < size; i++)` visits the slots in order, from index 0 to `size - 1`. The loop stops before `size`, because index `size` is outside the array.

- The order of the loop gives the "first match" rule. The function returns at the first match, so a later match with the same surname is never reached. In the edge test, the surname `Mokoena` appears in slot 0 and slot 1, and the function returns 0.
- If `size` is 0, the loop body never runs, and the function returns `-1`.

**The `if` condition.** The condition has two tests joined with `&&` (and). C++ checks the left test first. If the left test is false, C++ does not check the right test. This is called short-circuit evaluation. The order of the two tests matters.

1. `members[i] != NULL` checks that the slot holds an employee. An employee may have been removed with `removeMember`, and a team may not be full.
2. `members[i]->getSurName() == surName` compares the surname of that employee with the parameter. The arrow `->` follows the pointer and calls the function on the employee. The `string` class defines `==` as an exact comparison, character by character. The text `nkosi` does not equal `Nkosi`, and `"Nkosi "` with a space does not equal `Nkosi`.

The `NULL` test comes first. If the slot is `NULL`, the arrow `->` would follow a pointer that points to nothing. This is undefined behaviour. Because of short-circuit evaluation, the right side never runs for an empty slot.

**The `const` and `getSurName()`.** The function `getSurName()` is not a `const` member function. A `const` function usually cannot call non-`const` functions on its own object. Here the call is on the employee that `members[i]` points to, not on the team. In a `const` member function, the pointer `members` cannot change, but the `Employee` objects it points to can be used normally. The call compiles.

**The return.** `return i;` leaves the function at once with the index of the first match. `return -1;` comes after the loop. It runs only when the loop finishes without a match.

The function allocates and frees nothing.

## Trace

The team in `main.cpp` has size 4. The array holds `[Mokoena, Dlamini, Botha, NULL]`, where each name is the surname of the employee in that slot.

**Call `(*team)("Nkosi")`:** no member has this surname, so the loop runs to the end.

| `i` | `members[i] != NULL` | `getSurName()` | equals `"Nkosi"` | Action |
|---|---|---|---|---|
| 0 | true | `Mokoena` | false | next `i` |
| 1 | true | `Dlamini` | false | next `i` |
| 2 | true | `Botha` | false | next `i` |
| 3 | false | not called | not checked | next `i` |

After `i` is 3, the test `4 < 4` is false and the loop ends. The function returns `-1`.

**Call `(*team)("Botha")`:** the loop stops at the match.

| `i` | `members[i] != NULL` | `getSurName()` | equals `"Botha"` | Action |
|---|---|---|---|---|
| 0 | true | `Mokoena` | false | next `i` |
| 1 | true | `Dlamini` | false | next `i` |
| 2 | true | `Botha` | true | `return 2` |

The call `(*team)("Dlamini")` stops at `i` equal to 1 in the same way. The ExpectedOutput of `main.cpp` is:

```text
Dlamini: 1
Botha: 2
Nkosi: -1
```

## Common mistakes

1. **Leaving out the `NULL` test.** The team in `main.cpp` has an empty slot 3. Without the test, the search for `Nkosi` calls `getSurName()` through a `NULL` pointer, which is undefined behaviour. Valgrind reports `Invalid read of size 8`, and the program stops with a segmentation fault (`SIGSEGV`). The line `Nkosi: -1` is never printed.
2. **Returning the last match.** A loop that does not stop at the first match, and remembers the last index, returns 1 instead of 0 for `Mokoena` in the edge test. The output of the edge test then differs from the expected output.
3. **Returning `-1` inside the loop.** An `else { return -1; }` after the `if` ends the function on the first slot that does not match. The searches for `Dlamini` and `Botha` in `main.cpp` would return `-1` instead of 1 and 2. The `return -1;` belongs after the loop.
4. **Looping to `i <= size`.** The last pass reads `members[size]`, which is outside the array. Valgrind reports `Invalid read of size 8`. The printed output can still look correct, because the value that is read is undefined. Only valgrind shows the mistake.
