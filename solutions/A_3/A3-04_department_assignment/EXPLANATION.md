# A3-04 Explanation: Department::operator=

## What the function must do

The statement `*a = *b;` must make department `a` hold its own copy of every team in department `b`. The sizes become equal, and each team stays in the same slot number. The copy goes two levels deep: every `Team` is new, and every `Employee` inside each team is new. The function must free the teams that department `a` owned before the call.

## How the solution works

A `Department` has `Team** teams` (an array of `Team*` pointers) and `int size` (the number of slots). A slot holds a pointer to a team or `NULL`. The department owns its teams. `~Department()` deletes each team, and each `~Team()` deletes its own employees.

A **shallow copy** copies only the pointers, so two departments would point at the same `Team` objects and delete them twice. A **deep copy** creates new objects. The function does not copy employees itself. The given `Team(const Team&)` constructor makes a deep copy of one team, including a new copy of every employee. The function calls this constructor.

```cpp
Department& Department::operator=(const Department& other) {
```

`other` is a reference to the right-hand department. The word `const` means the function does not change `other`. The function returns `Department&`, a reference to the left-hand department.

```cpp
    if (this == &other) {
        return *this;
    }
```

`this` is a pointer to the current object (the left-hand department). `&other` is the address of the right-hand department. The condition is true for `a = a;`. The check must come first, because the next step deletes the teams that `other` would supply. In `a = a`, `other` is the current department itself. Without the check, the function deletes every team and the array. The line `teams = new Team*[size];` then changes `other.teams` too, because `other` is the same object. The copy loop reads the slots of this new array, and these slots hold no set values. The teams are lost. If the condition is true, the function returns `*this` (the current object) and changes nothing.

```cpp
    for (int i = 0; i < size; i++) {
        delete teams[i];
    }
    delete[] teams;
```

The loop deletes every team of the current department. Each `delete` runs `~Team()`, and that destructor deletes the employees of the team. A slot that holds `NULL` is safe, because `delete` on a `NULL` pointer does nothing. Without the loop, valgrind reports a leak for every old team and employee. `delete[] teams` frees the array of pointers. The teams must be deleted first, because the function cannot read the array after `delete[]`.

```cpp
    size = other.size;
    teams = new Team*[size];
```

The loop above needs the old `size`, so the new size is set after the loop. The function reads `other.size` and `other.teams` directly. A member function of `Department` is allowed to read the private members of another `Department`. The first line copies the size. The second line allocates a new array of that many `Team*` slots. The slots hold no valid values yet, so the next loop must set every slot.

```cpp
    for (int i = 0; i < size; i++) {
        if (other.teams[i] == NULL) {
            teams[i] = NULL;
        } else {
            teams[i] = new Team(*other.teams[i]);
        }
    }
```

The loop visits every slot number `i`. The `if` checks whether the slot in `other` is empty. If the slot is `NULL`, the new slot becomes `NULL`. The function must not dereference `NULL`, because `*other.teams[i]` on a `NULL` pointer crashes. If the slot holds a team, `*other.teams[i]` is the team object that the pointer points to. `new Team(*other.teams[i])` calls the `Team` copy constructor, which creates a new team with new employees. The new slot points at the new team, in the same slot number `i`.

The condition tests for `NULL` only. A team with no employees is not `NULL`, so the function copies it too (test 6 checks this). When `size` is `0`, the loop does not run, and the department has an array with zero slots.

```cpp
    return *this;
}
```

The function returns the current department. For `x = y = z;`, C++ runs `y = z` first, and then `x = y`.

## Trace

The call is `*a = *b;` from `main.cpp`. Before the call, `a` has size 1 and holds one team `t1`, which holds `Thandi`. Department `b` has size 3. The slots are `t2` (with `Sipho` and `Anna`), `NULL`, and `t4` (with `Lebo`). The slot 1 of `b` is `NULL` because `main.cpp` deleted that team and set the slot to `NULL`. `t2'` and `t4'` are new copies.

| Step | Code | `size` | `teams` of `a` |
|---|---|---|---|
| Before | none | 1 | `[ t1 ]` |
| 1 | `this == &other`: the addresses differ, so the condition is false | 1 | `[ t1 ]` |
| 2 | loop `i = 0`: `delete teams[0]` frees `t1` and `Thandi` | 1 | `[ freed ]` |
| 3 | `delete[] teams;` frees the old array | 1 | no array |
| 4 | `size = other.size;` | 3 | no array |
| 5 | `teams = new Team*[size];` | 3 | new array of 3 slots, values not set |
| 6 | `i = 0`: `other.teams[0]` is not `NULL`, so the slot gets `t2'`, a copy of `t2` with new copies of `Sipho` and `Anna` | 3 | `[ t2', ?, ? ]` |
| 7 | `i = 1`: `other.teams[1]` is `NULL`, so `teams[1] = NULL` | 3 | `[ t2', NULL, ? ]` |
| 8 | `i = 2`: `other.teams[2]` is not `NULL`, so the slot gets `t4'`, a copy of `t4` with a new copy of `Lebo` | 3 | `[ t2', NULL, t4' ]` |
| 9 | `return *this;` | 3 | `[ t2', NULL, t4' ]` |

Department `b` still points at `t2` and `t4`. Later, `main.cpp` runs `(*b)[0]->removeMember(1)`, which deletes `Anna` from `t2`. Then it deletes `t4` and sets slot 2 of `b` to `NULL`. These changes affect `b`, `t2` and `t4` only. Department `a` holds `t2'` and `t4'`, so the output shows that `a` has not changed.

The output of `main.cpp` is:

```text
Department a before:
Department of size 1:
Slot 0: Team of size 2:
  0: Thandi Mokoena, 29, F, ID: none
  1: empty
Department b:
Department of size 3:
Slot 0: Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Anna Botha, 41, F, ID: none
Slot 1: empty
Slot 2: Team of size 1:
  0: Lebo Nkosi, 25, F, ID: none
Department a after *a = *b:
Department of size 3:
Slot 0: Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Anna Botha, 41, F, ID: none
Slot 1: empty
Slot 2: Team of size 1:
  0: Lebo Nkosi, 25, F, ID: none
Department b after the changes:
Department of size 3:
Slot 0: Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: empty
Slot 1: empty
Slot 2: empty
Department a has not changed:
Department of size 3:
Slot 0: Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Anna Botha, 41, F, ID: none
Slot 1: empty
Slot 2: Team of size 1:
  0: Lebo Nkosi, 25, F, ID: none
```

## Common mistakes

- **Shallow copy.** The code `teams[i] = other.teams[i];` copies the pointers. After `main.cpp` deletes `t4` from `b`, department `a` holds a pointer to freed memory. Printing `a` reads freed memory, and the destructors delete the same teams twice. Valgrind reports invalid reads and invalid frees.
- **No self-assignment check.** For `a = a;`, the function deletes the teams and the array. Because `other` is the same department, the copy loop then reads the new array, and its slots hold no set values. In the edge test (test 1, `a = a`), valgrind reports "Conditional jump or move depends on uninitialised value(s)". The team of Lebo is lost, and the department prints `Slot 0: empty`.
- **Delete only the array.** If the function runs `delete[] teams;` without the loop, the old teams and employees have no pointer any more. Valgrind reports a leak.
- **Copy a `NULL` slot with `new Team(*other.teams[i])`.** The function dereferences a `NULL` pointer, and the program stops with a segmentation fault. The `if` for `NULL` slots prevents this.
- **Skip a team that has no employees.** The condition must test the team pointer, not the number of employees. A function that skips empty teams leaves a `NULL` slot where the original has a team. Test 6 (`d = e`) then prints `Slot 0: empty` instead of a team of size 2.
