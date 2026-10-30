# A2-09 Explanation: Team::operator+= grows the array by one

## What the function must do

The operator `team += employee;` adds a copy of an employee to the end of a `Team`. The array `members` grows by one slot each time, so the team never becomes full.

The team stores its own copy. The caller still owns the employee it passed in. If the pointer is `NULL`, the function changes nothing. In all cases, the function returns the team itself, so calls can be chained.

## How the solution works

```cpp
Team& Team::operator+=(Employee* employee) {
    if (employee == NULL) {
        return *this;
    }
    Employee** temp = new Employee*[size + 1];
    for (int i = 0; i < size; i++) {
        temp[i] = members[i];  // move the pointers; the employees stay where they are
    }
    temp[size] = new Employee(*employee);  // the team keeps its own copy
    delete[] members;                      // only the old array, not the employees
    members = temp;
    size++;
    return *this;
}
```

**The signature.** `Team& Team::operator+=(Employee* employee)` is an overloaded operator. It gives meaning to `team += pointer`. The return type `Team&` is a reference to a `Team`. The parameter `employee` is a pointer. A pointer holds the address of an object, and `NULL` means it holds no address.

**Data.** `members` is an array of pointers to `Employee`. `size` is the length of that array. An array made with `new` has a fixed length. The array cannot grow in place. The function therefore builds a larger array and replaces the old one.

**The `NULL` check.** `if (employee == NULL)` checks that the caller passed an employee.

- If the check is true, the function returns `*this` at once. The team stays unchanged.
- The check protects the later statement `new Employee(*employee)`. The `*` follows the pointer. Following a `NULL` pointer is undefined behaviour.
- The check comes first, before any allocation. The function therefore allocates nothing for a `NULL` input.
- `*this` is the current object. Inside a member function, `this` is a pointer to the current object, and `*this` is the object itself. Returning it by reference allows a chain such as `(team += a) += b;`.

**The new array.** `Employee** temp = new Employee*[size + 1];` allocates an array with one more slot than the old array. `Employee**` is a pointer to a pointer to an `Employee`, which is the type of an array of `Employee*` values. The name `temp` holds the new array until the function is ready to swap.

**The copy loop.** `for (int i = 0; i < size; i++)` visits every index of the old array. The statement `temp[i] = members[i];` copies the pointer into the same index of the new array.

- The loop copies pointers, not employees. The employees stay where they are in memory. The new array points to the same employees as the old array.
- A `NULL` slot is copied as `NULL`, so empty slots keep their places.
- The loop uses the old `size`. The function must not change `size` before the loop finishes. The old array has `size` slots only.

**The new employee.** `temp[size] = new Employee(*employee);` puts a copy in the last slot, index `size`. The index `size` is valid in the new array, because the new array has `size + 1` slots. The expression `new Employee(*employee)` calls the copy constructor `Employee(const Employee&)`. The copy is a separate object. A later change to the caller's employee does not change the team's copy. The team's destructor deletes this copy, and the caller deletes the original.

**Free the old array.** `delete[] members;` frees the old array only. Memory made with `new[]` must be freed with `delete[]`. The function must not delete the employees. The new array still points to them, and the team's destructor will delete them later.

- This statement comes before `members = temp;`. After the reassignment, the address of the old array would be lost, and the memory could never be freed. Valgrind would report a leak.

**Update the members.** `members = temp;` makes the team use the new array. Then `size++;` adds 1 to the length. The new `size` matches the new array. The statement comes after all uses of the old `size`.

**The return.** `return *this;` returns the team by reference.

## Trace

The first call in `main.cpp` is `*team += sipho;`. The team starts with `size` 1 and holds Thandi in slot 0. The employee `sipho` has no ID number yet.

| Step | Statement | State |
|---|---|---|
| 1 | `employee == NULL` | false, so the function continues |
| 2 | `temp = new Employee*[size + 1]` | `temp` has 2 slots (uninitialised) |
| 3 | loop `i = 0`: `temp[0] = members[0]` | `temp[0]` points to Thandi |
| 4 | loop test `i = 1`, `1 < 1` | false, the loop ends |
| 5 | `temp[1] = new Employee(*employee)` | `temp[1]` points to a new copy of Sipho |
| 6 | `delete[] members` | the old 1-slot array is freed. Thandi is not freed |
| 7 | `members = temp` | the team uses the 2-slot array |
| 8 | `size++` | `size` is 2 |
| 9 | `return *this` | the team is returned |

After this call, `main` sets the ID number on its own `sipho`. The team holds a copy made earlier, so the team's Sipho still shows `ID: none`. The line `(*team += anna) += lebo;` runs the same steps twice. The first call grows `size` from 2 to 3 and returns the team. The second call grows `size` from 3 to 4.

The ExpectedOutput of `main.cpp` is:

```text
Team (2/2):
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
Main's employee: Sipho Dlamini, 35, M, ID: 9105225800087
Team (4/4):
  Thandi Mokoena, 29, F, ID: none
  Sipho Dlamini, 35, M, ID: none
  Anna Botha, 41, F, ID: none
  Lebo Nkosi, 25, F, ID: none
```

## Common mistakes

1. **Storing the caller's pointer.** The statement `temp[size] = employee;` stores the caller's object in the team. The team's output then shows the ID number that `main` set later (`ID: 9105225800087` and not `ID: none`), so the output differs. `main` deletes `sipho`, and then the `Team` destructor deletes the same object again. Valgrind reports `Invalid read of size 8` and `Invalid free() / delete / delete[] / realloc()`, which is a double delete.
2. **Not deleting the old array.** The output is still correct, but the old array is never freed. Valgrind reports a memory leak: in `main`, `definitely lost: 48 bytes in 3 blocks`, one block for each call.
3. **Deleting the old employees.** A loop that deletes `members[i]` before the swap frees employees that the new array still points to. The team then has dangling pointers. The printed output can still look correct, because reading freed memory is undefined behaviour. Valgrind reports many `Invalid read` errors and `Invalid free() / delete / delete[] / realloc()` when the destructor deletes the same employees again.
4. **Missing the `NULL` check.** The edge test runs `*team += NULL;`. Without the check, the function evaluates `*employee` on a `NULL` pointer, which is undefined behaviour. Valgrind reports `Invalid read of size 4`, and the program stops with a segmentation fault (`SIGSEGV`).
