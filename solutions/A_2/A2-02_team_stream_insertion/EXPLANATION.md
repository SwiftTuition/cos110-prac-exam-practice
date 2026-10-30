# A2-02 Explanation: operator<< for Team

## What the function must do

The function prints a heading line for a `Team`, then one line for each employee. The heading shows how many slots hold an employee and how many slots the team has.

Some slots can be empty. An empty slot holds `NULL`. The function must not print or dereference these slots. If the team has no employees, the function prints one line with `(no members)`.

## How the solution works

```cpp
ostream& operator<<(ostream& out, const Team& t) {
    // t is const, so getMemberCount() and operator[] (not const) cannot be called. Use the members.
    int count = 0;
    for (int i = 0; i < t.size; i++) {
        if (t.members[i] != NULL) {
            count++;
        }
    }
    out << "Team (" << count << "/" << t.size << "):" << endl;
    if (count == 0) {
        out << "  (no members)" << endl;
    }
    for (int i = 0; i < t.size; i++) {
        if (t.members[i] != NULL) {
            out << "  " << *t.members[i] << endl;
        }
    }
    return out;
}
```

**Signature.** `ostream& operator<<(ostream& out, const Team& t)` is an overloaded operator. It defines what `cout << aTeam` does.

- `out` is a reference to the output stream. The function writes into the caller's stream and returns it.
- `t` is a `const` reference. The function may read the team but may not change it.
- The function is a `friend` in `Team.h`. Because of this, it may read the private members `t.members` and `t.size`. The word `friend` is not repeated in `A_2.cpp`.

**Why the function counts by itself.** The functions `getMemberCount()` and `operator[]` are not `const` member functions. A `const` object cannot call them. The function reads `t.members` and `t.size` directly instead.

**The data.** `t.members` is an array of pointers to `Employee`. A pointer holds the address of an object. `NULL` means the pointer holds no address. The `Team` constructor sets every slot to `NULL`. A slot becomes non-`NULL` only when `addMember` stores an employee there. The function `removeMember` deletes the employee and sets the slot back to `NULL`.

**First loop: count the employees.**

- `for (int i = 0; i < t.size; i++)` visits every slot from index 0 to `t.size - 1`. The loop stops before `t.size`, because index `t.size` is outside the array.
- `if (t.members[i] != NULL)` checks that the slot holds an employee. Only then does the function add 1 to `count`. The loop counts slots that are not empty, not the array length.
- If the team has size 0, the loop body never runs and `count` stays 0.

**Heading.** The statement `out << "Team (" << count << "/" << t.size << "):" << endl;` prints the heading. The counted number goes first, then the array length. The function prints the heading before the `if`, so every team gets a heading.

**The empty case.** `if (count == 0)` checks that no slot holds an employee. A team of size 0 and a team with only `NULL` slots both give `count` equal to 0. The function then prints the line `  (no members)`, with two spaces before the text. The second loop prints nothing for such a team.

**Second loop: print the employees.**

- The loop runs through the slots in the same order, from index 0 upward. This gives slot order in the output.
- `if (t.members[i] != NULL)` protects the dereference. The expression `*t.members[i]` follows the pointer to the `Employee`. If the slot is `NULL`, the dereference is undefined behaviour and the program can crash.
- `out << "  " << *t.members[i] << endl;` prints two spaces, then the employee, then a newline. The employee is printed by the given `operator<<` for `Employee`, which prints no newline. The function adds `endl` itself, so every line ends with a newline, including the last one.

**Return.** `return out;` returns the stream so the caller can chain more output after the team.

The function allocates no memory and frees no memory. The `Team` destructor frees the employees. The function only reads the data.

## Trace

The call is the second `cout << *team;` in `main.cpp`. Before this call, `main` put Thandi in slot 0 and Sipho in slot 1. Then `main` called `team->removeMember(0)`. The array has size 3 and now holds:

| Slot | 0 | 1 | 2 |
|---|---|---|---|
| Content | `NULL` | Sipho | `NULL` |

First loop (counting):

| `i` | `t.members[i] != NULL` | `count` after this step |
|---|---|---|
| 0 | false | 0 |
| 1 | true | 1 |
| 2 | false | 1 |

The heading prints `Team (1/3):`. The check `count == 0` is false, so the function skips the `(no members)` line.

Second loop (printing):

| `i` | `t.members[i] != NULL` | Output |
|---|---|---|
| 0 | false | nothing |
| 1 | true | `  Sipho Dlamini, 35, M, ID: none` and a newline |
| 2 | false | nothing |

The output of this call is the second block in the ExpectedOutput of `main.cpp`:

```text
Team (1/3):
  Sipho Dlamini, 35, M, ID: none
```

## Common mistakes

1. **Not skipping `NULL` slots.** If the second loop dereferences every slot, the function dereferences `NULL` after `removeMember`. This is undefined behaviour. In `main`, the first team prints correctly. The second print reaches the `NULL` in slot 0. Valgrind reports `Invalid read of size 8`, and the program stops with a segmentation fault (`SIGSEGV`). The rest of the expected output is missing.
2. **Printing the array length as the count.** The heading then shows `Team (3/3):` where `Team (1/3):` is expected. The output of `main` then differs from the expected output.
3. **Calling `t.getMemberCount()` or `t[i]`.** The reference `t` is `const`. These functions are not `const` member functions, so the code does not compile. A compile error gives the mark 0.
4. **Leaving out the `(no members)` line.** A team with only `NULL` slots then prints a heading with nothing below it. The expected output for `Team (0/2):` has a second line, so the output differs.
