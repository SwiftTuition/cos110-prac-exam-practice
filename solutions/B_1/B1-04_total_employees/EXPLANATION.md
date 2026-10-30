# B1-04 Explanation: recursive totalEmployees

## What the function must do

The function `Department::totalEmployees(index)` adds up the employees in all teams from slot `index` to the last slot. Each slot of `teams` holds a `Team*` or `NULL`. A `NULL` slot has no team and adds `0`. A team with no employees also adds `0`.

If `index` equals `size`, no slots are left, so the answer is `0`. If `index` is negative or larger than `size`, the answer is also `0`. The class `Team` has a given function `getMemberCount()` that returns the number of employees in one team.

## How the solution works

The array `teams` is an array of pointers (`Team**`). The function handles one slot, then asks itself about the slots after it. The function does not allocate or free memory. The department keeps ownership of its teams.

```cpp
if (index < 0 || index >= size) {
    return 0;
}
```

This is the base case. `index < 0` protects against a negative index, because `teams[-1]` is outside the array. `index >= size` covers the value `size`, which means the function has passed the last slot, and any larger invalid value. Both give `0`. The same line handles a department of size 0. Without a base case, every call would make another call, so the recursion could never end. g++ 13 sees this and reports `infinite recursion detected`. Under `-Wall -Werror` the build fails.

```cpp
int here = 0;
if (teams[index] != NULL) {
    here = teams[index]->getMemberCount();
}
```

The variable `here` holds the employee count of the current slot. The `if` checks that the slot holds a team. The arrow `->` calls a function through a pointer, so `teams[index]->getMemberCount()` calls the function on the team that the pointer points to. If the slot is `NULL`, the pointer points to nothing, and a call through it is undefined behaviour. The check keeps `here` at `0` for an empty slot.

```cpp
return here + totalEmployees(index + 1);
```

This is the recursive case. The call `totalEmployees(index + 1)` returns the employee count for the slots after the current slot. Each call raises `index` by 1, so the calls move toward `index == size`, which is the base case. The addition runs after the recursive call returns. Each call adds its own `here` to the total from the later slots.

## Trace

In `main.cpp`, the department has size 4. Slot 0 holds a team with 2 employees. Slot 1 is `NULL`, because the program deletes that team and sets the slot to `NULL`. Slot 2 holds a team with 1 employee. Slot 3 was never filled, so it is `NULL`. The call is `totalEmployees(0)`.

| Call | index | Slot | Branch taken | `here` | Result |
|---|---|---|---|---|---|
| 1 | 0 | team with 2 employees | recursive case | 2 | waits for call 2 |
| 2 | 1 | `NULL` | recursive case | 0 | waits for call 3 |
| 3 | 2 | team with 1 employee | recursive case | 1 | waits for call 4 |
| 4 | 3 | `NULL` | recursive case | 0 | waits for call 5 |
| 5 | 4 | none | base case, `4 >= 4` | not set | returns `0` |

The calls return in the order 5, 4, 3, 2, 1:

- Call 4 returns `0 + 0 = 0`.
- Call 3 returns `1 + 0 = 1`.
- Call 2 returns `0 + 1 = 1`.
- Call 1 returns `2 + 1 = 3`.

The output of `main.cpp` is:

```text
Department of size 4:
Slot 0: Team of size 3:
  0: Thandi Mokoena, 29, F, ID: none
  1: Sipho Dlamini, 34, M, ID: none
  2: empty
Slot 1: empty
Slot 2: Team of size 2:
  0: Lebo Nkosi, 25, F, ID: none
  1: empty
Slot 3: empty
Employees from team 0: 3
Employees from team 2: 1
Employees from team 3: 0
After removing a member of team 0: 2
```

## Common mistakes

- **No `NULL` check before `->`.** The first `NULL` slot makes the program call `getMemberCount()` through a null pointer. This is undefined behaviour. In the test run, valgrind reported `Invalid read of size 4`, and the program stopped with a segmentation fault (`SIGSEGV`) at the first call of `totalEmployees`. The main test and the edge test with an empty department both contain `NULL` slots.
- **Using `getSize()` of the team instead of `getMemberCount()`.** The function `getSize()` returns the number of slots, not the number of employees. The team in slot 0 has 3 slots but 2 employees, so the total is wrong. In `main.cpp`, the line `Employees from team 0:` shows `5` instead of `3`.
- **Using `index > size` in the base case.** When `index` equals `size`, the function then reads `teams[size]`, which is outside the array. This is undefined behaviour, so the result cannot be trusted. In the test run the output was still correct, but valgrind reported `Invalid read of size 8`, so the valgrind check fails.
- **Calling `totalEmployees(index)` instead of `totalEmployees(index + 1)`.** The argument never changes, so the recursion never ends. The program compiles, but at run time valgrind reports `Stack overflow` and the program stops with a segmentation fault (`SIGSEGV`).
- **A loop or a helper function.** QUESTION.md states that either one scores 0. The call to the given `Team::getMemberCount()` is allowed.
