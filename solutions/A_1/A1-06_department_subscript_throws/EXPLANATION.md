# A1-06 Explanation: Department::operator[]

## What the function must do

The operator `operator[]` of `Department` gives the caller access to slot `index` of the array `teams`. The return type `Team*&` is a reference to the pointer in the slot. The caller can read the pointer or store a new pointer in the slot. For a negative index, the function throws `Exception("Negative index")`. For an index that is `size` or larger, the function throws `Exception("Index too large")`. An empty slot is not an error.

## How the solution works

```cpp
Team*& Department::operator[](int index) {
```

The member `teams` has the type `Team**`. It points to an array of `Team*` pointers. The type `Team*` is a pointer to a `Team`. The type `Team*&` is a reference to such a pointer. A reference is another name for an existing variable. If the function returns a reference to `teams[index]`, the caller works on the slot itself and not on a copy.

This is why the statement `(*sales)[2] = new Team(1);` works. The call `(*sales)[2]` returns the slot. The assignment then stores the new address in the slot. If the function returned a plain `Team*`, the result would be a temporary copy. A copy cannot receive an assignment, so the compiler would report an error for this statement.

**Check 1: a negative index.**

```cpp
    if (index < 0) {
        throw Exception("Negative index");
    }
```

A negative index is not a valid position in the array. The function throws before it reads or returns any slot. A `throw` stops the function and sends the `Exception` to the nearest matching `catch` in the caller.

**Check 2: an index that is too large.**

```cpp
    if (index >= size) {
        throw Exception("Index too large");
    }
```

The valid indexes are 0 to `size - 1`. The test uses `>=` because the index `size` is already outside the array. For a department with `size` 0, every non-negative index fails this check. The two checks use two separate `if` statements because the two cases have two different messages.

**Return the slot.**

```cpp
    return teams[index];
```

The index is valid here, so the read is inside the array. The function does not check for `NULL`. The question says that an empty slot is not an error, and the caller may need to test it with `(*sales)[1] == NULL` or fill it.

The function allocates nothing and deletes nothing. The department still owns every team in its slots and deletes them in `~Department()`.

If an assignment such as `(*sales)[3] = extra;` throws, the assignment never happens. The department does not own `extra`. The caller must delete `extra`, and `main.cpp` does this in the `catch` block. Without that `delete`, valgrind reports a leak.

## Trace

The department is `new Sales(3)`. It has `size` 3, and all three slots start as `NULL`. The slot 0 gets `north` through `addTeam`.

| Step | Code in `main.cpp` | Check 1 | Check 2 | Effect |
|---|---|---|---|---|
| 1 | `(*sales)[2] = new Team(1);` | 2 < 0 false | 2 >= 3 false | returns slot 2, the assignment stores the new team |
| 2 | `(*sales)[2]->addMember(...)` | false | false | returns slot 2, which now holds a team, and adds Anna |
| 3 | `(*sales)[1] == NULL` | false | 1 >= 3 false | returns slot 1, which is `NULL`, so the output is `Slot 1 is empty` |
| 4 | `(*sales)[-1];` | -1 < 0 true | not reached | throw `Negative index` |
| 5 | `(*sales)[3] = extra;` | 3 < 0 false | 3 >= 3 true | throw `Index too large`, `extra` is not stored |

In step 5, the `catch` block prints the message and runs `delete extra;`. The final `delete sales;` frees the teams in slots 0 and 2. The cost line shows R45000, because the class `Sales` charges R15000 for each of the three employees.

The output of `main.cpp` is:

```text
Slot 1 is empty
Sales (cost R45000)
Team:
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
Team:
  Anna Botha, 41, F, ID: none
Caught: Negative index
Caught: Index too large
```

## Common mistakes

- **Use `index > size`.** The index `size` then passes the check, and the function returns `teams[size]`, which is outside the array. The statement `(*sales)[3] = extra;` then writes outside the array. Valgrind reports `Invalid write of size 8`. The program prints `Extra team added`, and the department never deletes `extra`, so valgrind also reports a leak (`definitely lost`). The main test rejected this change.
- **Throw for a `NULL` slot.** The call `(*sales)[2] = new Team(1);` needs the empty slot 2. If the function throws for `NULL`, nothing in `main` catches the exception at that statement. The program stops with `terminate called after throwing an instance of 'Exception'` before it prints anything, and the mark is 0. The main test rejected this change.
- **Return a local copy.** Code such as `Team* tmp = teams[index]; return tmp;` returns a reference to a variable that ends when the function ends. The compiler reports `reference to local variable returned`, and `-Werror` turns this warning into an error.
- **Return `*teams[index]` or print the team.** The return type is `Team*&`, so the function must return the pointer slot. The line `return *teams[index];` gives the compile error `invalid initialization of reference of type 'Team*&' from expression of type 'Team'`. The function must not print anything.
- **Use one message for both errors.** The question requires `Negative index` for a negative index and `Index too large` for a large index. With one message, one of the two lines `Caught: ...` in the output would be wrong.
