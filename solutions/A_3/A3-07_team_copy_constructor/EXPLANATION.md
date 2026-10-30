# A3-07 Explanation: Team::Team(const Team&)

## What the function must do

A **copy constructor** builds a new `Team` from an existing `Team`. It runs for `Team b(a);`, for `Team b = a;`, for `new Team(*a)` and when a `Team` is passed to a function by value. The new team must have the same size as the old team and its own copy of every employee. The two teams must share no `Employee` object.

## How the solution works

A constructor starts with an object whose members hold no meaningful values. The members `members` (an `Employee**`, a pointer to an array of `Employee*` pointers) and `size` (an `int`) hold no set values until the constructor sets them. They are uninitialised.

The given `Team::operator=` already makes a deep copy. The solution reuses it.

```cpp
Team::Team(const Team& other) : members(NULL), size(0) {
```

The text after the colon is the **member initialiser list**. It sets `members` to `NULL` and `size` to `0` before the body runs. The parameter `other` is a reference to the existing team. The word `const` means the constructor does not change `other`.

The order in the list follows the order of declaration in `Team.h`: `members` first, then `size`. If the list names `size` first, g++ with `-Wall` reports a `-Wreorder` warning, and `-Werror` makes the warning an error.

The initial values matter because of what `operator=` does first. The given `operator=` deletes every employee in the old array and then deletes the array itself:

```cpp
    for (int i = 0; i < size; i++) {
        delete members[i];
    }
    delete[] members;
```

This code is in `Team.cpp`. In a new object, no array exists yet. If `members` and `size` are not set, the loop uses an uninitialised `size`, and `delete` uses uninitialised addresses. This is undefined behaviour: C++ does not say what happens. With `size` equal to `0`, the loop runs zero times. With `members` equal to `NULL`, `delete[] members` does nothing, because deleting a `NULL` pointer is safe. The old state looks like an empty team, so `operator=` has nothing to free.

```cpp
    *this = other;
}
```

`this` is a pointer to the new object. `*this` is the new object itself. The statement `*this = other;` calls `Team::operator=` for the new object, with `other` as the right-hand side. The `if (this == &other)` check inside `operator=` is false here, because the new object and `other` are different objects. The function then sets `size = other.size;`, creates a new array, and makes a new copy of each employee with the `Employee` copy constructor. A `NULL` slot in `other` stays `NULL` in the copy. Each employee stays in the same slot number.

The solution does not repeat this loop. It relies on the given `operator=`, and the question allows this.

The copy is deep. A **shallow copy** would copy the pointers only, and both teams would then delete the same employees. A deep copy makes new `Employee` objects, so each team deletes its own.

## Trace

The call is `new Team(*a)` from `main.cpp`. Before the call, team `a` has size 3. Its slots are `[ Thandi, NULL, Anna ]`, because `a->removeMember(1)` deleted `Sipho`. The new team is `*b`. `Thandi'` and `Anna'` are new copies.

| Step | Code | `size` of the new team | `members` of the new team |
|---|---|---|---|
| Start | the constructor is called; no array exists | not set | not set |
| 1 | initialiser list: `members(NULL), size(0)` | 0 | `NULL` |
| 2 | `*this = other;` calls `operator=`; `this == &other` is false | 0 | `NULL` |
| 3 | in `operator=`: the loop runs 0 times; `delete[] members` on `NULL` does nothing | 0 | `NULL` |
| 4 | in `operator=`: `size = other.size;` | 3 | `NULL` |
| 5 | in `operator=`: `members = new Employee*[size];` | 3 | new array of 3 slots, values not set |
| 6 | `i = 0`: `other.members[0]` is not `NULL`, so the slot gets `Thandi'` | 3 | `[ Thandi', ?, ? ]` |
| 7 | `i = 1`: `other.members[1]` is `NULL`, so the slot is `NULL` | 3 | `[ Thandi', NULL, ? ]` |
| 8 | `i = 2`: `other.members[2]` is not `NULL`, so the slot gets `Anna'` | 3 | `[ Thandi', NULL, Anna' ]` |
| 9 | `operator=` returns; the constructor ends | 3 | `[ Thandi', NULL, Anna' ]` |

Team `a` still points at `Thandi` and `Anna`. After `a->removeMember(0)`, team `a` deletes `Thandi`, but team `b` still holds `Thandi'`. The output shows that team `b` has not changed.

The output of `main.cpp` is:

```text
Team a:
Team of size 3:
  0: Thandi Mokoena, 29, F, ID: none
  1: empty
  2: Anna Botha, 41, F, ID: none
Team b, a copy of a:
Team of size 3:
  0: Thandi Mokoena, 29, F, ID: none
  1: empty
  2: Anna Botha, 41, F, ID: none
Team a after removing member 0:
Team of size 3:
  0: empty
  1: empty
  2: Anna Botha, 41, F, ID: none
Team b has not changed:
Team of size 3:
  0: Thandi Mokoena, 29, F, ID: none
  1: empty
  2: Anna Botha, 41, F, ID: none
```

## Common mistakes

- **No `NULL` and `0` before `*this = other;`.** The constructor has an empty initialiser list and only the line `*this = other;`. The members are uninitialised. The loop in `operator=` then uses an uninitialised `size`, and `delete[] members` uses an uninitialised address. This is undefined behaviour. In the test runs, the output still looked correct, but valgrind reported errors. On `main.cpp` it reported "Conditional jump or move depends on uninitialised value(s)". On the edge test it also reported "Invalid free() / delete / delete[]" and "Invalid read of size 8".
- **Shallow copy.** The code `members = other.members; size = other.size;` copies the pointers. Both teams own the same array and employees. The destructors free them twice, and valgrind reports invalid frees.
- **Initialiser list in the wrong order.** The list `size(0), members(NULL)` does not match the order in `Team.h`. With `-Wall -Werror`, the warning `-Wreorder` becomes an error, and the program does not compile. The mark is 0.
- **Write a hand-made copy loop that skips `NULL` slots.** If the loop sets a slot only when `other.members[i]` is not `NULL`, the empty slots of the new array hold no set value. Later code, such as `operator<<` and the destructor, reads these slots and compares them with `NULL`. This is undefined behaviour. In the test runs, the output still looked correct, and valgrind reported "Conditional jump or move depends on uninitialised value(s)" on both tests. Each slot needs a value: `NULL` or a new copy.
