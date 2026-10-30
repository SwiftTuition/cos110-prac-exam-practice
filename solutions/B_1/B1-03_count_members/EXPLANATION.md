# B1-03 Explanation: recursive countMembers

## What the function must do

The function `Team::countMembers(index)` counts the employees in a team, starting at slot `index` and ending at the last slot. A slot holds an employee when it is not `NULL`. A `NULL` slot is empty and adds nothing to the count.

Empty slots can be anywhere in the array, because `removeMember` sets a slot to `NULL`. If `index` is negative or larger than `size`, the answer is `0`. If `index` equals `size`, no slots are left, so the answer is also `0`.

## How the solution works

The member `members` is an array of pointers (`Employee**`). A pointer holds the address of an object, and `NULL` means the pointer points to nothing. The function looks at one slot, then asks itself about the slots after it. The function does not allocate or free memory. The team still owns its employees and deletes them in its destructor.

```cpp
if (index < 0 || index >= size) {
    return 0;
}
```

This is the base case. `index < 0` protects against a negative index, because `members[-1]` is outside the array. `index >= size` covers two situations. The value `index == size` means the function has passed the last slot, so no slots are left. A larger value is invalid. Both give `0`. This `if` also handles a team of size 0, because `0 >= 0` is true. Without the base case, every call would make another call, so the recursion could never end. g++ 13 sees this and reports `infinite recursion detected`. Under `-Wall -Werror` the build fails.

```cpp
int here = 0;
if (members[index] != NULL) {
    here = 1;
}
```

The variable `here` holds the count for the current slot. The `if` checks that the slot holds an employee. A slot that is `NULL` keeps `here` at `0`. The check is needed because the function must count only employees, not slots.

```cpp
return here + countMembers(index + 1);
```

This is the recursive case. The call `countMembers(index + 1)` counts the slots after the current slot. Each call raises `index` by 1, so the calls move toward `index == size`, which is the base case. The addition runs after the recursive call returns. Each call adds its own `here` to the count from the later slots.

## Trace

In `main.cpp`, the team has size 5. The slots are `Thandi`, empty, `Anna`, `Ravi`, empty. The call is `countMembers(0)`.

| Call | index | Slot | Branch taken | `here` | Result |
|---|---|---|---|---|---|
| 1 | 0 | Thandi | recursive case | 1 | waits for call 2 |
| 2 | 1 | empty (`NULL`) | recursive case | 0 | waits for call 3 |
| 3 | 2 | Anna | recursive case | 1 | waits for call 4 |
| 4 | 3 | Ravi | recursive case | 1 | waits for call 5 |
| 5 | 4 | empty (`NULL`) | recursive case | 0 | waits for call 6 |
| 6 | 5 | none | base case, `5 >= 5` | not set | returns `0` |

The calls return in the order 6, 5, 4, 3, 2, 1:

- Call 5 returns `0 + 0 = 0`.
- Call 4 returns `1 + 0 = 1`.
- Call 3 returns `1 + 1 = 2`.
- Call 2 returns `0 + 2 = 2`.
- Call 1 returns `1 + 2 = 3`.

The output of `main.cpp` is:

```text
Team of size 5:
  0: Thandi Mokoena, 29, F, ID: none
  1: empty
  2: Anna Botha, 41, F, ID: none
  3: Ravi Naidoo, 38, M, ID: none
  4: empty
Members from index 0: 3
Members from index 2: 2
Members from index 4: 0
After removing member 0, from index 0: 2
```

## Common mistakes

- **Counting a slot without the `NULL` check.** If `here` is always `1`, the function counts slots, not employees. For the team above, the answer is `5` instead of `3`.
- **Using `index > size` in the base case.** When `index` equals `size`, the function then reads `members[size]`, which is outside the array. This is undefined behaviour, so the result cannot be trusted. In the test run the output was still correct, but valgrind reported `Invalid read of size 8` for every call that reached the end, so the valgrind check fails.
- **No check for a negative index.** The function reads `members[-1]`, which is outside the array. This is undefined behaviour. The edge test `countMembers(-1)` expects `0`. In the test run, the line `6. negative index:` showed `3` instead of `0`, and valgrind reported `Invalid read of size 8`.
- **Calling `countMembers(index)` instead of `countMembers(index + 1)`.** The argument never changes, so the recursion never ends. The program compiles, but at run time valgrind reports `Stack overflow` and the program stops with a segmentation fault (`SIGSEGV`). No `Members from index` line is printed.
- **A loop or a helper function.** QUESTION.md states that either one scores 0.
