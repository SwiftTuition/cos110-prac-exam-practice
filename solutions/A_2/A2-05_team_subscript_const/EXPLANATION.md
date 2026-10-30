# A2-05 Explanation: Team::operator[] (const)

## What the function must do

The function lets code write `team[i]` to get the employee in slot `i`, like an array index. The function returns the employee by `const` reference, so the caller can read the employee but not change it.

If the index is outside the array, or the slot is empty, the function throws an `Exception`. A reference cannot be `NULL`, so a throw is the only way to report a bad index.

## How the solution works

```cpp
const Employee& Team::operator[](int index) const {
    if (index < 0 || index >= size || members[index] == NULL) {
        throw Exception("Index out of bounds");
    }
    return *members[index];
}
```

**The header line.** `const Employee& Team::operator[](int index) const` has three parts that need an explanation.

- `operator[]` is an overloaded operator. It gives meaning to `team[i]` for a `Team` object.
- The return type `const Employee&` is a reference to an `Employee` that the caller must not change. The function returns the real object, not a copy.
- The second `const`, after the parameter list, makes this a `const` member function. A `const` member function promises not to change the team. A `const Team&` may call only `const` member functions. In `main.cpp`, the function `printFirstAndLast` receives a `const Team&` and uses `team[0]`, so the word `const` is required. The definition in `A_2.cpp` must match the declaration in `Team.h`, including this `const`.

**The data.** `members` is an array of pointers to `Employee`. `size` is the length of the array. A pointer holds the address of an object. An empty slot holds `NULL`, which means no address.

**The `if` condition.** The condition has three tests joined with `||` (or). The tests run from left to right. C++ stops at the first test that is true. This is called short-circuit evaluation. The order protects the array.

1. `index < 0` catches a negative index. An array has no slot -1.
2. `index >= size` catches an index past the end. The last valid index is `size - 1`. A team of size 0 has no valid index, and this test catches index 0 for that team.
3. `members[index] == NULL` catches an empty slot. A slot can be empty because the team was never full, or because `removeMember` set it to `NULL`.

The range tests come before `members[index]`. If `index` is -1 or equal to `size`, the expression `members[index]` would read memory outside the array. Because of short-circuit evaluation, the function never reads `members[index]` for those values.

**The throw.** `throw Exception("Index out of bounds");` creates an `Exception` object with that message and stops the function. The program jumps to the nearest matching `catch`. The function does not print anything and does not catch the exception. The caller decides what to do. In `main.cpp`, the `catch (Exception& e)` block receives the object by reference, and `e.what()` gives the message.

If nothing catches the exception, the program ends abnormally and the mark is 0.

**The return.** `return *members[index];` runs only when the index is in range and the slot is not `NULL`. The `*` follows the pointer and gives the `Employee` object itself. The function returns a reference to that object. The returned reference stays valid, because the team still owns the employee.

The function allocates and frees nothing. The `Team` destructor frees the employees.

## Trace

The calls come from `main.cpp`. The team has size 3 and holds Thandi (slot 0), Sipho (slot 1) and Anna (slot 2).

| Call | `index < 0` | `index >= size` | `members[index] == NULL` | Result |
|---|---|---|---|---|
| `team[0]` | false | false (0 >= 3 is false) | false (Thandi) | returns Thandi |
| `team[2]` | false | false (2 >= 3 is false) | false (Anna) | returns Anna |
| `(*team)[1]` | false | false | false (Sipho) | returns Sipho |
| `(*team)[3]` | false | true (3 >= 3 is true) | not evaluated | throws `Exception("Index out of bounds")` |

For the last call, the `catch (Exception& e)` block in `main` prints the message. The ExpectedOutput of `main.cpp` is:

```text
First: Thandi Mokoena, 29, F, ID: none
Last: Anna Botha, 41, F, ID: none
Sipho Dlamini, 35, M, ID: none
Caught: Index out of bounds
```

## Common mistakes

1. **Leaving out the `NULL` test.** The edge test removes the employee in slot 1 and then asks for `team[1]`. Without the `NULL` test, the function returns a reference made from a `NULL` pointer, which is undefined behaviour. When the edge test prints that employee, valgrind reports `Invalid read of size 8` and the program stops with a segmentation fault (`SIGSEGV`).
2. **Reading `members[index]` before the range tests.** With an index such as 3 or -1, the function reads memory outside the array. Valgrind reports `Invalid read of size 8` (once in `main`, three times in the edge test). The printed output can still look correct, because the value that is read is undefined. Only valgrind shows the mistake. The range tests must come first.
3. **Using `index > size` instead of `index >= size`.** The index equal to `size` then passes the test. For a team of size 3, index 3 is outside the array, so `members[3]` reads memory past the end. Valgrind reports `Invalid read of size 8`. The printed output can still look correct, so only valgrind shows the mistake. The correct test is `>=`.
4. **Leaving out the last `const`.** A definition `const Employee& Team::operator[](int index)` does not match the declaration in `Team.h`. The compiler reports `no declaration matches 'const Employee& Team::operator[](int)'`. A compile error gives the mark 0.
