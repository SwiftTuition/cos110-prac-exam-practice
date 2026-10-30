# A2-01 Explanation: operator<< for Employee

## What the function must do

The function prints one `Employee` as a single line of text. It does not print a newline. The text has the first name, surname, age, gender and ID number.

If the employee has no ID number yet, the function prints `none` in place of the ID. The function writes to the stream it receives and returns that stream, so calls can be chained.

## How the solution works

The full solution is short.

```cpp
ostream& operator<<(ostream& out, const Employee& e) {
    // e is const and the getters are not const, so a friend reads the members directly.
    out << e.firstName << " " << e.surName << ", " << e.age << ", " << e.gender << ", ID: ";
    if (e.idNum == "") {
        out << "none";
    } else {
        out << e.idNum;
    }
    return out;
}
```

**Signature.** `ostream& operator<<(ostream& out, const Employee& e)` is an overloaded operator. It tells the compiler what `cout << someEmployee` means.

- `ostream& out` is a reference. A reference is another name for an existing object. The function writes into the real stream, not a copy. A copy of a stream is not allowed.
- `const Employee& e` is a reference to an `Employee` that the function must not change. No copy of the employee is made.
- The word `friend` appears only in `Employee.h`. A friend function may read private members such as `e.firstName`. The function in `A_2.cpp` must not repeat `friend`.

**Why the members are read directly.** The parameter `e` is `const`. The getters such as `getFirstName()` are not `const` member functions. The compiler refuses to call a non-`const` function on a `const` object. The friend function can read `e.firstName` directly, so it does not need the getters.

**The first `out <<` line.** The line `out << e.firstName << " " << e.surName << ", " << e.age << ", " << e.gender << ", ID: ";` prints everything before the ID.

- The function uses `out`, not `cout`. The marking program may pass a different stream, for example a string stream. Text sent to `cout` would never reach that stream.
- Each `<<` returns the stream, so the next `<<` can follow in the same statement.
- The text `", ID: "` ends with a space. The format needs one space after `ID:`.

**The `if` condition.** `if (e.idNum == "")` checks whether the ID number is still the empty string. The constructor sets `idNum` to `""`. Only `setIDNum` changes it.

- If the condition is true, the function prints `none`. This protects the case of an employee with no ID.
- If the condition is false, the `else` branch prints the stored ID number.
- Without this check, an employee without an ID would print `ID: ` followed by nothing.

**The return.** `return out;` gives the same stream back to the caller. This is the reason that `cout << *thandi << " | " << *sipho << endl;` works. The expression `cout << *thandi` returns `cout`, and the next `<<` continues on it. The function must not print `endl`, because `main` adds it.

The function allocates no memory. There is nothing to free, so valgrind reports no leak from this function.

## Trace

The call comes from the third print statement in `main.cpp`.

```cpp
cout << *thandi << " | " << *sipho << endl;
```

The program reads this from left to right. The `Employee` Thandi has the ID `9702140123081`. The `Employee` Sipho has no ID.

| Step | Call | Check `e.idNum == ""` | Text added to the stream | Value returned |
|---|---|---|---|---|
| 1 | `operator<<(cout, *thandi)` | false (the ID is set) | `Thandi Mokoena, 29, F, ID: ` then `9702140123081` | `cout` |
| 2 | `cout << " | "` | not applicable | ` | ` | `cout` |
| 3 | `operator<<(cout, *sipho)` | true (the ID is empty) | `Sipho Dlamini, 35, M, ID: ` then `none` | `cout` |
| 4 | `cout << endl` | not applicable | a newline | `cout` |

The program output for the three print statements in `main.cpp` is:

```text
Thandi Mokoena, 29, F, ID: 9702140123081
Sipho Dlamini, 35, M, ID: none
Thandi Mokoena, 29, F, ID: 9702140123081 | Sipho Dlamini, 35, M, ID: none
```

## Common mistakes

1. **Writing to `cout` instead of `out`.** The output looks correct in `main.cpp`, because `main` uses `cout`. The edge test sends the employee to an `ostringstream`. The text appears on the screen instead, and the string stream is empty. The output differs from the expected output.
2. **Printing `endl` inside the function.** Every employee line then ends with an extra newline. The expected output of `main.cpp` differs, because `main` already adds `endl`.
3. **Calling the getters on `e`.** An expression such as `e.getFirstName()` does not compile. The reference `e` is `const`, and the getter is not a `const` member function. A compile error gives the mark 0.
4. **Forgetting the empty ID case.** The function then prints `ID: ` with nothing after it. The expected line for Sipho is `ID: none`, so the output differs.
