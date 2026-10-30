# A1-07 Explanation: Team::addMember

## What the function must do

The function `addMember` puts an `Employee*` into the first empty slot of the array `members`. After a successful call, the team owns the employee and deletes it in `~Team()`. The function throws an `Exception` in three cases: the pointer is `NULL`, the same pointer is already in the team, or no slot is empty. After a throw, the array is unchanged and the caller still owns the employee.

## How the solution works

The member `members` has the type `Employee**`. It points to an array of `Employee*` pointers. A pointer holds the address of an object. An empty slot holds `NULL`. The member `size` is the number of slots.

**Check 1: a NULL pointer.**

```cpp
    if (employee == NULL) {
        throw Exception("Employee is NULL");
    }
```

A `NULL` pointer points to no employee, so the question requires an exception for it. This check comes first, as the question requires. When the team is full and the pointer is `NULL`, the message must be `Employee is NULL` and not `Team is full`.

**Check 2: the same pointer in any slot.**

```cpp
    for (int i = 0; i < size; i++) {
        if (members[i] == employee) {
            throw Exception("Employee is already in the team");
        }
    }
```

The loop visits every slot from 0 to `size - 1`. The condition `members[i] == employee` compares two addresses. It is true when the slot holds the same employee object. The question defines "already in the team" as the same address, not the same name or ID number.

The loop must visit every slot and must not stop at an empty slot. An empty slot can appear before the employee, because `removeMember` sets a slot to `NULL`. If the same pointer were stored twice, `~Team()` would run `delete` on the same address twice. This is a double delete, and valgrind reports it.

The duplicate check runs before the search for a free slot. The function must not store the pointer and then find out that it is a duplicate.

**Check 3 and the store.**

```cpp
    for (int i = 0; i < size; i++) {
        if (members[i] == NULL) {
            members[i] = employee;
            return;
        }
    }
    throw Exception("Team is full");
```

The second loop looks for the lowest index with a `NULL` slot. The condition `members[i] == NULL` is true for an empty slot. The statement `members[i] = employee;` stores the pointer. The team now owns the employee. The `return` ends the function at once, so the function does not continue to the `throw`.

If the loop ends without a store, no slot was empty. The last line throws `Team is full`. For a team of size 0, the loop does not run, and the function throws `Team is full`.

Memory: the function allocates nothing and deletes nothing. It stores a pointer that the caller created with `new`. After a throw, `members` has not changed. The caller must delete the employee, as `main.cpp` does for `lebo`. Without that `delete`, valgrind reports a leak.

## Trace

The call sequence is from `main.cpp`. The team has `size` 2. The arrays show the slots 0 and 1.

| Call | Check 1 | Check 2 | Free slot search | Slots after the call |
|---|---|---|---|---|
| `addMember(thandi)` | not `NULL` | slots are `NULL`, no match | slot 0 is `NULL`, store | `[thandi, NULL]` |
| `addMember(thandi)` | not `NULL` | slot 0 matches | not reached | `[thandi, NULL]`, throw `Employee is already in the team` |
| `addMember(sipho)` | not `NULL` | no match | slot 0 is used, slot 1 is `NULL`, store | `[thandi, sipho]` |
| `addMember(lebo)` | not `NULL` | no match | no `NULL` slot, loop ends | `[thandi, sipho]`, throw `Team is full` |
| `addMember(NULL)` | `NULL`, throw | not reached | not reached | `[thandi, sipho]`, throw `Employee is NULL` |

After the call with `lebo` throws, `main` runs `delete lebo;` in the `catch` block. The program prints `Members: 2` and the team. Then `delete team;` runs `~Team()`, which deletes `thandi` and `sipho`.

The output of `main.cpp` is:

```text
Caught: Employee is already in the team
Caught: Team is full
Caught: Employee is NULL
Members: 2
Team:
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
```

## Common mistakes

- **Stop the duplicate search at the first empty slot.** The edge test removes the employee at slot 1 and then adds `lebo`, which sits in slot 2. The search stops at slot 1 and misses `lebo`. The function stores `lebo` a second time in slot 1, so the team prints Lebo twice, and `~Team()` deletes it twice. Valgrind reports `Invalid read of size 8` and `Invalid free()`. The edge test rejected this change.
- **Check for a full team before the `NULL` check.** For a full team and a `NULL` argument, the output would say `Team is full`. The main test expects `Employee is NULL`. The main test rejected this change.
- **Store the pointer in a slot other than the first empty slot.** The question requires the first empty slot, the lowest index that is `NULL`. The program prints the slots in index order, so a different slot gives a different order.
- **Compare the names instead of the pointers.** The question defines a duplicate by address. A second employee with the same name would be refused wrongly. Also, if the loop calls `members[i]->getFirstName()` on an empty slot, it follows a `NULL` pointer. Valgrind reports `Invalid read of size 8`, and the program stops with a segmentation fault (SIGSEGV).
- **Catch the exception inside `addMember` or print a message.** The caller then never sees the error, and the output lines `Caught: ...` are missing. The `catch` block in `main` that runs `delete lebo;` also never runs, so valgrind reports a leak (`definitely lost`).
- **Delete the employee inside `addMember` before the throw.** The question says that the caller still owns the employee after a throw. A second `delete` in `main` is then a double delete. The main output still looks correct, but valgrind reports `Invalid read of size 8` and `Invalid free()`.
