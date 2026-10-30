# A3-02 Explanation: Team::operator=

## What the function must do

The statement `*a = *b;` must make team `a` hold its own copy of every employee in team `b`. The two teams must have the same size, and each employee must stay in the same slot number. After the call, the teams share no `Employee` object. The function must also free the memory that team `a` owned before the call.

## How the solution works

A `Team` has two members. `members` has type `Employee**`: a pointer to an array, and each array slot holds an `Employee*` (a pointer to one employee) or `NULL`. `size` is the number of slots. The team owns its employees, so the team must delete them.

A **shallow copy** copies the pointers only. After a shallow copy, both teams point at the same `Employee` objects. Both destructors would then delete the same objects, and valgrind reports a double delete. A **deep copy** makes new `Employee` objects. The function must make a deep copy.

```cpp
Team& Team::operator=(const Team& other) {
```

`other` is a reference to the right-hand team. The word `const` means the function does not change `other`. The function returns `Team&`, a reference to the left-hand team.

```cpp
    if (this == &other) {
        return *this;
    }
```

`this` is a pointer to the current object (the left-hand team). `&other` is the address of the right-hand team. The condition is true when both are the same team, as in `a = a;`. The check must come first, because the next step deletes the memory that `other` would use. In `a = a`, `other` is the current team itself. Without the check, the function deletes the employees and the array. The line `members = new Employee*[size];` then changes `other.members` too, because `other` is the same object. The copy loop reads the slots of this new array, and these slots hold no set values. The employees are lost. If the condition is true, the function returns `*this` (the current object) and changes nothing.

```cpp
    for (int i = 0; i < size; i++) {
        delete members[i];
    }
    delete[] members;
```

This step frees the old memory of the current team. The loop runs from slot `0` to slot `size - 1` and deletes each employee. A slot that holds `NULL` is safe: `delete` on a `NULL` pointer does nothing. Without the loop, the old employees stay in memory and valgrind reports a leak. `delete[] members` frees the array of pointers. The function must delete the employees first. After `delete[] members`, the function cannot read `members[i]` any more.

The deletion loop needs the old `size`. For this reason, the line `size = other.size;` comes after the deletions.

```cpp
    size = other.size;
    members = new Employee*[size];
```

The function reads `other.size` and `other.members` directly. The getters `getSize()` and `getMemberCount()` are not `const` functions, so the function cannot call them on a `const Team&`. The first line copies the size. The second line allocates a new array of that many `Employee*` slots. The slots hold no valid values yet. The loop must set every slot.

```cpp
    for (int i = 0; i < size; i++) {
        if (other.members[i] == NULL) {
            members[i] = NULL;
        } else {
            members[i] = new Employee(*other.members[i]);
        }
    }
```

The loop visits every slot number `i`. The `if` checks whether the slot in `other` is empty. If the slot is `NULL`, the new slot becomes `NULL`. The function must not dereference `NULL`. The expression `*other.members[i]` on a `NULL` pointer would crash. If the slot holds an employee, `new Employee(*other.members[i])` creates a new employee. `*other.members[i]` is the employee object that the pointer points to. The `Employee` copy constructor copies all its attributes. The new slot then points at the new object, in the same slot number `i`.

When `size` is `0`, the loop does not run and `new Employee*[0]` gives an empty array. The destructor can delete it.

```cpp
    return *this;
}
```

The function returns the current team. For `a = b = c;`, C++ first runs `b = c`, and then `a = b`.

## Trace

The call is `*a = *b;` from `main.cpp`. Before the call, team `a` has size 2 and team `b` has size 3. Employee `Sipho` is the object `S`, `Ravi` is `R`, and `Thandi` is `T`. In `b`, slot 1 is `NULL` because of `removeMember(1)`.

| Step | Code | `size` | `members` of `a` |
|---|---|---|---|
| Before | none | 2 | `[ T, NULL ]` (one array of 2 slots) |
| 1 | `this == &other`: the two addresses differ, so the condition is false | 2 | `[ T, NULL ]` |
| 2 | loop `i = 0`: `delete members[0]` frees `T` | 2 | `[ freed, NULL ]` |
| 3 | loop `i = 1`: `delete members[1]` on `NULL` does nothing | 2 | `[ freed, NULL ]` |
| 4 | `delete[] members;` frees the old array | 2 | no array |
| 5 | `size = other.size;` | 3 | no array |
| 6 | `members = new Employee*[size];` | 3 | new array of 3 slots, values not set |
| 7 | `i = 0`: `other.members[0]` is not `NULL`, so the slot gets a new copy `S'` of `S` | 3 | `[ S', ?, ? ]` |
| 8 | `i = 1`: `other.members[1]` is `NULL`, so `members[1] = NULL` | 3 | `[ S', NULL, ? ]` |
| 9 | `i = 2`: `other.members[2]` is not `NULL`, so the slot gets a new copy `R'` of `R` | 3 | `[ S', NULL, R' ]` |
| 10 | `return *this;` | 3 | `[ S', NULL, R' ]` |

The objects `S'` and `R'` are new. Team `b` still points at `S` and `R`. After `b->removeMember(0)`, team `b` deletes `S`, but `a` still holds `S'`. The output shows that team `a` has not changed.

The output of `main.cpp` is:

```text
Team a before:
Team of size 2:
  0: Thandi Mokoena, 29, F, ID: none
  1: empty
Team b:
Team of size 3:
  0: Sipho Dlamini, 34, M, ID: none
  1: empty
  2: Ravi Naidoo, 38, M, ID: none
Team a after *a = *b:
Team of size 3:
  0: Sipho Dlamini, 34, M, ID: none
  1: empty
  2: Ravi Naidoo, 38, M, ID: none
Team b after removing member 0:
Team of size 3:
  0: empty
  1: empty
  2: Ravi Naidoo, 38, M, ID: none
Team a has not changed:
Team of size 3:
  0: Sipho Dlamini, 34, M, ID: none
  1: empty
  2: Ravi Naidoo, 38, M, ID: none
```

## Common mistakes

- **Shallow copy.** The code `members[i] = other.members[i];` copies the pointers. Both teams then own the same employees. The destructors delete each employee twice, and valgrind reports invalid frees. This happens in `main.cpp`.
- **No self-assignment check.** For `a = a;`, the function deletes the employees and the array of the team. Because `other` is the same team, the copy loop then reads the new array, and its slots hold no set values. In the edge test (test 1, `a = a`), valgrind reports "Conditional jump or move depends on uninitialised value(s)". The employee Lebo is lost, and the team prints `0: empty`.
- **Delete only the array.** If the function runs `delete[] members;` without the loop, the old employees have no pointer any more. Valgrind reports a leak.
- **Copy a `NULL` slot with `new Employee(*other.members[i])`.** The function dereferences a `NULL` pointer, and the program stops with a segmentation fault. The `if` for `NULL` slots prevents this.
- **Keep the old `size`.** If the function does not set `size = other.size;`, the new array has the wrong length. The copy has the wrong slot count. If the source team is smaller than the old size, the copy loop reads beyond the end of the source array.
