# A2-10 Explanation: Team::operator+ returns a merged team

## What the function must do

The operator `a + b` makes a new `Team` that holds copies of the members of `a`, then copies of the members of `b`. Neither `a` nor `b` changes.

The new team has exactly as many slots as there are members in both teams. Empty slots in `a` and `b` are left out, so the new team has no gaps. The function returns the new team by value.

## How the solution works

```cpp
Team Team::operator+(const Team& other) const {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (members[i] != NULL) {
            count++;
        }
    }
    for (int i = 0; i < other.size; i++) {
        if (other.members[i] != NULL) {
            count++;
        }
    }

    Team result(count);
    int next = 0;
    for (int i = 0; i < size; i++) {
        if (members[i] != NULL) {
            result.members[next] = new Employee(*members[i]);
            next++;
        }
    }
    for (int i = 0; i < other.size; i++) {
        if (other.members[i] != NULL) {
            result.members[next] = new Employee(*other.members[i]);
            next++;
        }
    }
    return result;
}
```

**The signature.** `Team Team::operator+(const Team& other) const` is an overloaded operator for `a + b`.

- The return type is `Team`, not `Team&`. The function returns a new object by value.
- `const Team& other` is a reference to the right-hand team. The function reads it and does not change it. A reference is another name for an existing object, so no copy is made.
- The `const` after the parameter list means the function does not change the left-hand team.
- The functions `getMemberCount()` and `operator[]` are not `const` member functions. A `const` function cannot call them. The function therefore counts and reads `members` and `size` directly.

**Data.** `members` is an array of pointers to `Employee`. A pointer holds the address of an object. An empty slot holds `NULL`. Reading `other.members` is allowed because `other` has the same class as the current object.

**Step 1: count the members.** Two loops count the slots that are not `NULL`.

- `for (int i = 0; i < size; i++)` visits each slot of the current team. `for (int i = 0; i < other.size; i++)` does the same for `other`. Each loop stops before its own array length.
- `if (members[i] != NULL)` and `if (other.members[i] != NULL)` count only slots that hold an employee. The test also protects the later dereference. An empty slot is not counted and not copied.
- The count is needed first because a `Team` array has a fixed length. The function must know the final length before it creates the new team. Adding `size + other.size` would keep the empty slots and leave gaps.
- If both teams have no members, the loops leave `count` at 0, and the result has size 0.

**Step 2: create the result.** `Team result(count);` makes a local `Team` with `count` slots, all `NULL`. The variable `next` holds the index of the next free slot in `result`. It starts at 0.

**Step 3: copy the current team.** The loop visits the slots in order from index 0.

- `if (members[i] != NULL)` skips empty slots again. Following a `NULL` pointer with `*members[i]` is undefined behaviour.
- `result.members[next] = new Employee(*members[i]);` creates a copy of the employee with the copy constructor of `Employee`. The expression `*members[i]` follows the pointer to the employee. The result team now owns a separate object.
- `next++;` moves to the next free slot. The increment is inside the `if`, so empty slots do not use up a position in `result`.
- If the function stored the pointer `members[i]` instead, two teams would hold the same employee. Both destructors would delete it, which is a double delete.

**Step 4: copy `other`.** The last loop does the same for `other`. It starts with `next` at the position where the first loop ended, so the members of `other` come after the members of the current team. The order is current team first, then `other`. For `a + a`, the second loop makes a second set of copies from the same employees.

**The return.** `return result;` returns the local team by value. The `Team` class has a deep copy constructor, so the returned copy gets its own employees. The compiler may also skip the copy and build the object directly in the caller's variable. The result is correct in both cases. When `result` goes out of scope, its destructor deletes its employees, and the caller's team keeps its own.

## Trace

The call is `Team merged = *north + *south;` in `main.cpp`. The team `north` has size 3 and holds `[Thandi, Sipho, NULL]`. The team `south` has size 2 and holds `[Anna, NULL]`.

Counting:

| Loop | `i` | Slot | Not `NULL` | `count` after |
|---|---|---|---|---|
| north | 0 | Thandi | true | 1 |
| north | 1 | Sipho | true | 2 |
| north | 2 | `NULL` | false | 2 |
| south | 0 | Anna | true | 3 |
| south | 1 | `NULL` | false | 3 |

The function creates `result(3)`. Copying:

| Loop | `i` | Slot | Action | `next` after |
|---|---|---|---|---|
| north | 0 | Thandi | `result.members[0]` is a copy of Thandi | 1 |
| north | 1 | Sipho | `result.members[1]` is a copy of Sipho | 2 |
| north | 2 | `NULL` | skipped | 2 |
| south | 0 | Anna | `result.members[2]` is a copy of Anna | 3 |
| south | 1 | `NULL` | skipped | 3 |

The three `cout` lines in `main` print `merged`, then `north`, then `south`. The teams `north` and `south` are unchanged. The ExpectedOutput of `main.cpp` is:

```text
Team (3/3):
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
  Anna Botha, 41, F, ID: none
Team (2/3):
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
Team (1/2):
  Anna Botha, 41, F, ID: none
```

## Common mistakes

1. **Copying the pointers.** The statement `result.members[next] = members[i];` shares the employees between teams. Each destructor deletes them, which gives a double delete. In `main`, the printed output still looks correct. Valgrind reports `Invalid read of size 8` and `Invalid free() / delete / delete[] / realloc()` when `merged` is destroyed after `north` and `south` were deleted.
2. **Sizing the result with `size + other.size`.** The result then has empty slots. In `main.cpp` it prints `Team (3/5):` where `Team (3/3):` is expected. The output of `main` then differs from the expected output.
3. **Building the result on the heap.** Code such as `Team* result = new Team(count); return *result;` returns a copy and never deletes the original. The output is still correct, but valgrind reports a leak. In `main` it shows `definitely lost: 16 bytes in 1 blocks` (the team), with its array and employees lost through it.
4. **Calling `getMemberCount()`.** The current team and `other` are both `const` inside the function. The function `getMemberCount()` is not a `const` member function, so the code does not compile. A compile error gives the mark 0.
