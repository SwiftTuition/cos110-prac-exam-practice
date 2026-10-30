# A3-03 Explanation: Team::operator= with a compact copy

## What the function must do

The statement `*a = *b;` must give team `a` its own copy of every employee in team `b`. The copy is compact. The new `size` equals the number of employees in `b`, and the copies fill slots `0, 1, 2, ...` in the same order as in `b`. The new team has no `NULL` slots. A normal deep copy keeps the slot numbers and the empty slots. This question does not.

## How the solution works

A `Team` has `Employee** members` (an array of `Employee*` pointers) and `int size` (the number of slots). A slot holds a pointer to an employee or `NULL`. The team owns its employees and must delete them. A **deep copy** creates new `Employee` objects. A **shallow copy** copies only the pointers, so two teams would point at the same employees and delete them twice.

```cpp
Team& Team::operator=(const Team& other) {
```

`other` is a reference to the right-hand team. The word `const` means the function does not change `other`. The function returns `Team&`, a reference to the left-hand team.

```cpp
    if (this == &other) {
        return *this;
    }
```

`this` is a pointer to the current object (the left-hand team). `&other` is the address of the right-hand team. The condition is true for `a = a;`. The check must come first, because the next step deletes the old memory. In `a = a`, the function would delete the employees and then try to count and copy them. The function would read freed memory. If the condition is true, the function returns `*this` (the current object). The team keeps its empty slots, as test 1 requires.

```cpp
    for (int i = 0; i < size; i++) {
        delete members[i];
    }
    delete[] members;
```

The loop deletes every employee of the current team. A `NULL` slot is safe, because `delete` on a `NULL` pointer does nothing. Without the loop, valgrind reports a leak. `delete[] members` frees the array of pointers. The employees must be deleted first, because the function cannot read the array after `delete[]`.

```cpp
    int count = 0;
    for (int i = 0; i < other.size; i++) {
        if (other.members[i] != NULL) {
            count++;
        }
    }
    size = count;
    members = new Employee*[size];
```

The function reads `other.size` and `other.members` directly. The getters `getSize()` and `getMemberCount()` are not `const` functions, so the function cannot call them on a `const Team&`.

The loop runs over all slots of `other`. The condition `other.members[i] != NULL` checks that the slot holds an employee. Only those slots are counted. The loop uses `other.size`, not `size`, because the new size is not known yet and the old `size` belongs to the old array.

The function then sets `size = count;` and allocates an array of that length. If `other` has no employees, `count` is `0`, and the array has zero slots. The team then has size `0`. The destructor can still delete this array.

The count must come before `new`, because the array length must be known when the array is created.

```cpp
    int next = 0;
    for (int i = 0; i < other.size; i++) {
        if (other.members[i] != NULL) {
            members[next] = new Employee(*other.members[i]);
            next++;
        }
    }
```

Two counters are used. `i` is the slot number in `other`. `next` is the slot number in the new array. The condition `other.members[i] != NULL` skips empty slots, so the function does not dereference a `NULL` pointer. `*other.members[i]` is the employee that the pointer points to. `new Employee(*other.members[i])` calls the `Employee` copy constructor to create a new employee. The new pointer goes to `members[next]`. Then `next` increases by one.

`next` increases only when the function copies an employee. For this reason, the new array has no gaps. The number of copies equals `count`, so every slot of the new array gets a value.

```cpp
    return *this;
}
```

The function returns the current team. For `*d = *c = *b;`, C++ runs `*c = *b` first, and then `*d = *c`.

## Trace

The call is `*a = *b;` from `main.cpp`. Before the call, `a` has size 2 with `[ Thandi, NULL ]`. Team `b` has size 4 with `[ Sipho, NULL, Ravi, NULL ]`. The slot 1 of `b` is `NULL` because of `b->removeMember(1)`. `Sipho'` and `Ravi'` are new copies.

| Step | Code | `count` | `next` | `size` | `members` of `a` |
|---|---|---|---|---|---|
| Before | none | none | none | 2 | `[ Thandi, NULL ]` |
| 1 | `this == &other`: the addresses differ, so the condition is false | none | none | 2 | `[ Thandi, NULL ]` |
| 2 | the first loop deletes `Thandi`; `delete` on `NULL` does nothing; `delete[] members` | none | none | 2 | no array |
| 3 | count loop, `i = 0`: not `NULL` | 1 | none | 2 | no array |
| 4 | `i = 1`: `NULL` | 1 | none | 2 | no array |
| 5 | `i = 2`: not `NULL` | 2 | none | 2 | no array |
| 6 | `i = 3`: `NULL` | 2 | none | 2 | no array |
| 7 | `size = count;` and `new Employee*[size]` | 2 | none | 2 | new array of 2 slots, values not set |
| 8 | copy loop, `i = 0`: not `NULL`, so `members[0]` is a copy `Sipho'`; `next` becomes 1 | 2 | 1 | 2 | `[ Sipho', ? ]` |
| 9 | `i = 1`: `NULL`, nothing happens | 2 | 1 | 2 | `[ Sipho', ? ]` |
| 10 | `i = 2`: not `NULL`, so `members[1]` is a copy `Ravi'`; `next` becomes 2 | 2 | 2 | 2 | `[ Sipho', Ravi' ]` |
| 11 | `i = 3`: `NULL`, nothing happens; `return *this;` | 2 | 2 | 2 | `[ Sipho', Ravi' ]` |

Team `b` is unchanged: it still has size 4 and points at `Sipho` and `Ravi`. After `b->removeMember(0)`, team `b` deletes `Sipho`, but team `a` still holds `Sipho'`.

The output of `main.cpp` is:

```text
Team a before:
Team of size 2:
  0: Thandi Mokoena, 29, F, ID: none
  1: empty
Team b:
Team of size 4:
  0: Sipho Dlamini, 34, M, ID: none
  1: empty
  2: Ravi Naidoo, 38, M, ID: none
  3: empty
Team a after *a = *b:
Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Ravi Naidoo, 38, M, ID: none
a: size 2, members 2
Team c after *d = *c = *b:
Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Ravi Naidoo, 38, M, ID: none
Team d after *d = *c = *b:
Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Ravi Naidoo, 38, M, ID: none
Team b after removing member 0:
Team of size 4:
  0: empty
  1: empty
  2: Ravi Naidoo, 38, M, ID: none
  3: empty
Team a has not changed:
Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Ravi Naidoo, 38, M, ID: none
```

## Common mistakes

- **Normal deep copy.** If the function sets `size = other.size;` and keeps the empty slots, team `a` prints `Team of size 4` with `empty` lines. The expected output shows size 2. The output then differs from the expected output.
- **Use `i` for the new array.** If the function writes `members[i] = ...` in the copy loop, each copy keeps its old slot number. In `main.cpp`, the copy of Ravi goes to `members[2]`, but the new array has only 2 slots. This writes past the end of the array, and slot 1 is never set. This is undefined behaviour. In the test runs, valgrind reported "Invalid write of size 8", "Conditional jump or move depends on uninitialised value(s)" and a leak ("definitely lost"). The output showed `1: empty` where Ravi should be.
- **Allocate before counting.** If the function calls `new Employee*[size]` before it sets `size = count;`, the array has the length of the old team, not `count`. When the old team has fewer slots than `count`, the copy loop writes past the end of the array. This is undefined behaviour. In the test runs, the output still looked correct, but valgrind reported "Invalid write of size 8" and "Invalid read of size 8" on both tests.
- **Shallow copy.** The code `members[next] = other.members[i];` copies the pointer. Both teams then own the same employee, and the destructors delete the employee twice. Valgrind reports invalid frees.
- **No self-assignment check.** For `a = a;`, the count loop reads the array that the function deleted in the step before, and valgrind reports "Invalid read of size 8". The copy loop then reads the new array, whose slots hold no set values, and valgrind reports "Conditional jump or move depends on uninitialised value(s)". In test 1, the team prints `Team of size 1:` and `0: empty`. Lebo and the empty slots are lost.
