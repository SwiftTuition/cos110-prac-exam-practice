# A2-03 Explanation: operator<< for Department

## What the function must do

The function prints a heading line for a `Department`, then prints every team in the department. The heading holds the department name and the cost to the company.

The function must print the name and cost of the real department type, such as `Development` or `HR`. If the department holds no team, the function prints one line with `(no teams)`.

## How the solution works

```cpp
ostream& operator<<(ostream& out, Department& d) {
    // getName() and costToCompany() are virtual, so a Sales object prints as Sales.
    out << "Department: " << d.getName() << " (cost R" << d.costToCompany() << ")" << endl;
    bool anyTeam = false;
    for (int i = 0; i < d.size; i++) {
        if (d.teams[i] != NULL) {
            out << *d.teams[i];
            anyTeam = true;
        }
    }
    if (!anyTeam) {
        out << "  (no teams)" << endl;
    }
    return out;
}
```

**Signature.** `ostream& operator<<(ostream& out, Department& d)` is an overloaded operator for `cout << aDepartment`.

- `out` is a reference to the output stream. The function writes to it and returns it.
- `d` is a reference to a `Department`. It is not `const`, because `getName()` and `costToCompany()` are not `const` member functions.
- The function is a `friend` in `Department.h`, so it may read the private members `d.teams` and `d.size`.

**Virtual calls.** `Sales`, `Marketing`, `HR` and `Development` are subclasses of `Department`. A friend function is not inherited, so only this one operator exists. A `Development` object reaches the operator as a `Department&`.

- `getName()` and `costToCompany()` are `virtual`. A `virtual` function runs the version of the real object, even when the reference has the type `Department&`.
- The call `d.getName()` returns `"Development"` for a `Development` object. The call `d.costToCompany()` returns the cost that the `Development` class calculates.
- Without `virtual`, the base versions would run. The base `getName()` returns `"Department"` and the base `costToCompany()` returns 0.

**Heading.** The first `out <<` statement prints `Department: `, the name, ` (cost R`, the cost and `)`. The cost is a `float`. With the normal stream format, `50000.0f` prints as `50000` with no decimals. The question states that all costs stay below one million.

**The flag.** `bool anyTeam = false;` records whether the function has found a team. The function cannot decide this from `d.size` alone. A department of size 2 can have two `NULL` slots.

**The loop.**

- `for (int i = 0; i < d.size; i++)` visits slots 0 up to `d.size - 1`, in order. A department of size 0 never enters the loop body.
- `if (d.teams[i] != NULL)` checks that the slot holds a team. `d.teams` is an array of pointers to `Team`. An empty slot holds `NULL`. Dereferencing `NULL` is undefined behaviour, so the check comes before `*d.teams[i]`.
- `out << *d.teams[i];` follows the pointer and prints the team with the given `operator<<` for `Team`. That operator prints its own `endl`, so the function adds none here.
- `anyTeam = true;` runs only for a slot that holds a team. The flag changes after the team prints.

**The `(no teams)` check.** `if (!anyTeam)` is true when the loop found no team. This covers a department of size 0 and a department whose slots are all `NULL`. The function prints `  (no teams)` with two spaces and an `endl`.

A team with zero employees still counts as a team. The flag becomes true, and the team prints its own `(no members)` line. The edge test checks this case. A version that tests `d.size == 0` instead of the flag fails the edge test.

**Return.** `return out;` returns the stream for chaining.

The function allocates and frees nothing. The `Department` destructor deletes the teams.

## Trace

The call is `cout << *hr;` in `main.cpp`. The object `hr` is a pointer to `HR` stored as `Department*`. Its size is 3. Slot 0 holds the team `people` with one employee, Anna. Slots 1 and 2 are `NULL`.

| Step | Action | Result |
|---|---|---|
| 1 | `d.getName()` | virtual call runs `HR::getName`, gives `HR` |
| 2 | `d.costToCompany()` | virtual call runs `HR::costToCompany`, gives 1 employee times 12000, which is `12000` |
| 3 | Print heading | `Department: HR (cost R12000)` and a newline |
| 4 | `anyTeam = false` | `anyTeam` is false |

| `i` | `d.teams[i] != NULL` | Action | `anyTeam` after |
|---|---|---|---|
| 0 | true | print the team `people`: `Team (1/1):` then `  Anna Botha, 41, F, ID: none` | true |
| 1 | false | none | true |
| 2 | false | none | true |

After the loop, `!anyTeam` is false, so the function does not print `(no teams)`. The output of this call is the second block of the ExpectedOutput in `main.cpp`:

```text
Department: HR (cost R12000)
Team (1/1):
  Anna Botha, 41, F, ID: none
```

## Common mistakes

1. **Calling the base versions.** Code that avoids the `virtual` calls prints `Department` and `R0` for every department. The output of `main` then differs from the expected output. The correct code calls `d.getName()` and `d.costToCompany()` through the reference.
2. **Testing `size` for the `(no teams)` line.** A department of size 2 with only `NULL` slots then prints nothing under the heading. The output of the edge test then differs from the expected output.
3. **Not checking for `NULL` before `*d.teams[i]`.** Dereferencing a `NULL` slot is undefined behaviour. In `main`, the `Development` department has 2 slots and one team, so slot 1 is `NULL`. The first team prints, then valgrind reports `Invalid read of size 4` and the program stops with a segmentation fault (`SIGSEGV`). The edge test also has `NULL` slots, for example the gap in slot 1 of the `Marketing` department.
4. **Declaring the parameter as `const Department& d`.** The calls to `getName()` and `costToCompany()` do not compile, because these functions are not `const` member functions. The function is also no longer the friend that `Department.h` declares, so `d.size` and `d.teams` give "is private within this context" errors. A compile error gives the mark 0.
