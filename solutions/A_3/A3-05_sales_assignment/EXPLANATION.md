# A3-05 Explanation: Sales::operator= in a derived class

## What the function must do

`Sales` inherits from `Department` and adds one attribute, `target`. The statement `*a = *b;` must copy the `Department` part (the teams and the size) and the `Sales` part (`target`). The `Department` part uses private members, so `Sales` cannot copy it directly. The function must ask the base class to copy its own part.

## How the solution works

A **derived class** such as `Sales` contains a base part (the `Department` members `teams` and `size`) and its own members (`target`). The members `teams` and `size` are `private` in `Department`. Code in `Sales` cannot read or write them.

The given `Department::operator=` already makes a deep copy of `teams` and sets `size`. It deletes the old teams, creates a new array, and copies each team with the `Team` copy constructor. `Sales::operator=` must call that function. The function must not repeat the work.

```cpp
Sales& Sales::operator=(const Sales& other) {
```

`other` is a reference to the right-hand `Sales` object. The word `const` means the function does not change `other`. The function returns `Sales&`, a reference to the left-hand object.

```cpp
    if (this == &other) {
        return *this;
    }
```

`this` is a pointer to the current object. `&other` is the address of the right-hand object. The condition is true for `a = a;`. In that case the function returns `*this` (the current object) and does nothing else. The given `Department::operator=` has its own check, so a self-assignment would not damage the data here. The question lists this check as step 1, and the same step protects classes that own memory directly.

```cpp
    Department::operator=(other);
```

This line calls the base class version of the assignment operator. The text `Department::` in front of the function name tells the compiler to call the `Department` version. Without it, the call `operator=(other)` would be the `Sales` version, which would call itself without end.

The argument `other` has type `const Sales&`. A `Sales` object is a `Department`, so C++ allows a `const Sales&` where a `const Department&` is expected. The base function receives only the `Department` part of `other`. The base function frees the old teams of the current object. It then copies `size` and makes new copies of the teams and the employees.

C++ does not call the base class assignment operator by itself when a derived class defines its own `operator=`. If the line is missing, the `Department` part of the current object keeps its old teams and old size.

The order of the base call and `target = other.target;` does not change the result, because the two parts are independent. The solution follows the order of the question.

```cpp
    target = other.target;
```

`target` is an `int`. A plain `=` copies it. `target` is a member of `Sales`, so the base function does not copy it. The function reads `other.target` directly, because a member function of `Sales` is allowed to read the private members of another `Sales` object.

```cpp
    return *this;
}
```

The function returns the current object. For `a = b = c;`, C++ runs `b = c` first, and then `a = b`.

## Trace

The call is `*a = *b;` from `main.cpp`. Before the call, `a` has size 1 and target 100, and holds the team `t1` (with `Thandi`). Object `b` has size 2 and target 250. Its slots are `t2` (with `Sipho` and `Anna`) and `NULL`. `t2'` is a new copy of `t2`.

| Step | Code | `size` | `teams` of `a` | `target` of `a` |
|---|---|---|---|---|
| Before | none | 1 | `[ t1 ]` | 100 |
| 1 | `this == &other`: the addresses differ, so the condition is false | 1 | `[ t1 ]` | 100 |
| 2 | `Department::operator=(other);` runs: it deletes `t1` and the old array | 1 | no array | 100 |
| 3 | in the base function: `size = other.size;` and a new array of 2 slots | 2 | new array of 2 slots | 100 |
| 4 | in the base function: slot 0 gets `t2'` (a copy of `t2` with new employees); slot 1 is `NULL` | 2 | `[ t2', NULL ]` | 100 |
| 5 | `target = other.target;` | 2 | `[ t2', NULL ]` | 250 |
| 6 | `return *this;` | 2 | `[ t2', NULL ]` | 250 |

Object `b` still holds `t2`. Later, `main.cpp` runs `(*b)[0]->removeMember(0)` and `b->setTarget(300)`. These calls change `t2` and the target of `b`. Object `a` holds `t2'` and its own target 250, so `a` does not change. The cost line uses the number of employees times 15000, so `a` shows `R30000` and `b` shows `R15000` after the change.

The output of `main.cpp` is:

```text
Sales a before:
Sales of size 1:
Slot 0: Team of size 1:
  0: Thandi Mokoena, 29, F, ID: none
Target: 100, cost: R15000
Sales b:
Sales of size 2:
Slot 0: Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Anna Botha, 41, F, ID: none
Slot 1: empty
Target: 250, cost: R30000
Sales a after *a = *b:
Sales of size 2:
Slot 0: Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Anna Botha, 41, F, ID: none
Slot 1: empty
Target: 250, cost: R30000
Sales b after the changes:
Sales of size 2:
Slot 0: Team of size 2:
  0: empty
  1: Anna Botha, 41, F, ID: none
Slot 1: empty
Target: 300, cost: R15000
Sales a has not changed:
Sales of size 2:
Slot 0: Team of size 2:
  0: Sipho Dlamini, 34, M, ID: none
  1: Anna Botha, 41, F, ID: none
Slot 1: empty
Target: 250, cost: R30000
```

## Common mistakes

- **Leave out the base call.** Without `Department::operator=(other);`, the teams and the size of the current object do not change. The output of `a` after the assignment shows the old size and the old team. The output then differs from the expected output.
- **Leave out `target = other.target;`.** The base part is copied, but `target` keeps the old value. The line `Target: 250` prints `Target: 100`. The output then differs from the expected output.
- **Try to copy `teams` and `size` in `Sales`.** The members are `private` in `Department`. The code does not compile, and the mark is 0.
- **Call `operator=(other)` without `Department::`.** The call finds `Sales::operator=` and calls it again with the same arguments. The function then calls itself without end, and the program stops with a stack overflow.
- **Return a value instead of a reference.** If the return type is `Sales` and not `Sales&`, the function returns a copy. The `Department` copy constructor is private, so the code does not compile.
