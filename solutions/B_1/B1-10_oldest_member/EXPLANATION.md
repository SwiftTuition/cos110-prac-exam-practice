# B1-10 Explanation: recursive oldest

## What the function must do

The function `Team::oldest(index)` returns the greatest age among the employees in the slots from `index` to the last slot. Each slot of `members` holds an `Employee*` or `NULL`. The function skips `NULL` slots.

If no employee is in those slots, the answer is `0`. This is safe because all ages are more than `0`. If `index` equals `size`, no slots are left, so the answer is `0`. If `index` is negative or larger than `size`, the answer is also `0`. If two employees have the same age, the answer is that age.

## How the solution works

The array `members` is an array of pointers (`Employee**`). A pointer holds the address of an object, and `NULL` means it points to nothing. The function first asks about the later slots, then compares the current slot with that answer. The function allocates no memory and frees none.

```cpp
if (index < 0 || index >= size) {
    return 0;
}
```

This is the base case. `index < 0` protects against a negative index, because `members[-1]` is outside the array. `index >= size` covers the value `size`, which means the function has passed the last slot, and any larger invalid value. Both give `0`, the "no employee" answer. The same line handles a team of size 0. Without a base case, every call would make another call, so the recursion could never end. g++ 13 sees this and reports `infinite recursion detected`. Under `-Wall -Werror` the build fails.

```cpp
int restOldest = oldest(index + 1);
```

This is the recursive call. The variable `restOldest` holds the greatest age in the slots after the current slot. Each call raises `index` by 1, so the calls move toward `index == size`, which is the base case. The call comes before the comparison. The function needs `restOldest` to compare with the current slot.

```cpp
if (members[index] != NULL && members[index]->getAge() > restOldest) {
    return members[index]->getAge();
}
return restOldest;
```

This `if` has two conditions joined by `&&`. The operator `&&` checks the left condition first. If it is false, the right condition is not evaluated. The left condition `members[index] != NULL` checks that the slot holds an employee. The right condition uses the arrow `->`, which calls `getAge()` on the employee that the pointer points to. The `NULL` test must come first. Otherwise, the function would call `getAge()` through a null pointer, which is undefined behaviour.

The right condition `members[index]->getAge() > restOldest` checks that the current employee is older than every employee after this slot. If both conditions are true, the function returns the age of the current employee. In every other case, the function returns `restOldest`. This covers an empty slot, a younger employee and an employee of the same age. For the same age, the two values are equal, so the answer is correct.

## Trace

In `main.cpp`, the team has size 5. The slots are `Thandi` (29), empty, `Anna` (41), `Ravi` (38), empty. The call is `oldest(0)`.

| Call | index | Slot | Branch taken | `restOldest` | Result |
|---|---|---|---|---|---|
| 1 | 0 | Thandi, 29 | recursive case | set when call 2 returns | waits for call 2 |
| 2 | 1 | empty (`NULL`) | recursive case | set when call 3 returns | waits for call 3 |
| 3 | 2 | Anna, 41 | recursive case | set when call 4 returns | waits for call 4 |
| 4 | 3 | Ravi, 38 | recursive case | set when call 5 returns | waits for call 5 |
| 5 | 4 | empty (`NULL`) | recursive case | set when call 6 returns | waits for call 6 |
| 6 | 5 | none | base case, `5 >= 5` | not set | returns `0` |

The calls return in the order 6, 5, 4, 3, 2, 1:

- Call 5: `restOldest` is `0`. The slot is `NULL`, so the function returns `0`.
- Call 4: `restOldest` is `0`. Since `38 > 0`, the function returns `38`.
- Call 3: `restOldest` is `38`. Since `41 > 38`, the function returns `41`.
- Call 2: `restOldest` is `41`. The slot is `NULL`, so the function returns `41`.
- Call 1: `restOldest` is `41`. Since `29 > 41` is false, the function returns `41`.

The output of `main.cpp` is:

```text
Team of size 5:
  0: Thandi Mokoena, 29, F, ID: none
  1: empty
  2: Anna Botha, 41, F, ID: none
  3: Ravi Naidoo, 38, M, ID: none
  4: empty
Oldest from index 0: 41
Oldest from index 3: 38
Oldest from index 4: 0
After removing member 2, from index 0: 38
```

## Common mistakes

- **Returning the first age found.** A version that returns the age of the first employee that it meets gives a wrong answer. For the team above, `oldest(0)` returns `29` instead of `41`. The output of the main test then differs from the expected output.
- **Testing the age before `NULL`.** If the condition is `members[index]->getAge() > restOldest && members[index] != NULL`, the first part runs on a `NULL` slot. The call goes through a null pointer. This is undefined behaviour. In the test run, valgrind reported `Invalid read of size 4`, and the program stopped with a segmentation fault (`SIGSEGV`) in the first call `oldest(0)`.
- **No `NULL` check at all.** The same thing happens: `Invalid read of size 4`, then `SIGSEGV`. The main test has empty slots at index 1 and index 4, and the edge test starts with a team where every slot is empty.
- **Using `index > size` in the base case.** When `index` equals `size`, the function then reads `members[size]`, which is outside the array. This is undefined behaviour, so the result cannot be trusted. In the test run the output was still correct, but valgrind reported `Invalid read of size 8`, so the valgrind check fails.
- **Calling `oldest(index)` instead of `oldest(index + 1)`.** The argument never changes, so the recursion never ends. The program compiles, but at run time valgrind reports `Stack overflow` and the program stops with a segmentation fault (`SIGSEGV`).
- **A loop or a helper function.** QUESTION.md states that either one scores 0. The call to the given `Employee::getAge()` is allowed.
