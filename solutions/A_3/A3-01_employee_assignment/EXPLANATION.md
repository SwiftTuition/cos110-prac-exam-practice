# A3-01 Explanation: Employee::operator=

## What the function must do

The statement `a = b;` must make the employee `a` hold the same details as the employee `b`. The function copies the five attributes: `firstName`, `surName`, `age`, `gender` and `idNum`. The function does nothing when an object is assigned to itself. The function returns the left-hand object so that `a = b = c;` works.

## How the solution works

An **assignment operator** is a function with the name `operator=`. C++ calls this function when the program writes `a = b;`. The object `a` is the current object. The object `b` is the parameter named `other`.

The parameter type is `const Employee&`. The `&` means `other` is a reference: it names the real object `b` and does not make a copy. The word `const` means the function promises not to change `other`.

```cpp
Employee& Employee::operator=(const Employee& other) {
```

The return type is `Employee&`. The function returns a reference to the left-hand object. This reference is what makes chaining possible.

```cpp
    if (this == &other) {
        return *this;
    }
```

`this` is a pointer to the current object. `&other` is the address of the object that `other` names. The condition `this == &other` compares the two addresses. The condition is true only when both sides are the same object, as in `a = a;`.

The check handles self-assignment. In this class, a copy of an object onto itself would do no harm, because `Employee` has no pointers. The check is step 1 of the four-step pattern that the solution follows. In classes that own memory, the same check is necessary. If the condition is true, the function returns `*this` and does no copying. `*this` is the current object itself.

```cpp
    firstName = other.firstName;
    surName = other.surName;
    age = other.age;
    gender = other.gender;
    idNum = other.idNum;
```

The function copies each attribute with `=`. The `string` class and the built-in types already know how to copy themselves. Memory is not a problem here, because `Employee` holds `string`, `int` and `char` only. Nothing is allocated with `new`, so nothing needs `delete`. Step 2 of the pattern (free old memory) is empty for this class.

The function reads `other.firstName` directly. The getters such as `getFirstName()` are not `const` functions. The compiler would refuse to call them on a `const Employee&`. A member function of `Employee` is allowed to read the private attributes of another `Employee` object.

The function copies `idNum` even when it is empty (`""`). If the function skipped an empty `idNum`, the old ID of the left-hand object would stay. The output would then show the wrong ID.

The function does not call `setIDNum`. That function validates the ID against the gender and can throw. A plain copy of `idNum` copies a value that was already valid in `other`.

```cpp
    return *this;
}
```

The last line returns the current object. For `a = b = c;`, C++ runs `b = c` first. That call returns `b`. Then C++ runs `a = b` with that returned object.

## Trace

The call is `*thandi = *sipho;` from `main.cpp`. The left side `*thandi` is the current object. The right side `*sipho` is `other`.

| Step | Code | `firstName` | `surName` | `age` | `gender` | `idNum` |
|---|---|---|---|---|---|---|
| Before | none | Thandi | Mokoena | 29 | F | 9702140123081 |
| 1 | `this == &other`: the two addresses differ, so the condition is false | Thandi | Mokoena | 29 | F | 9702140123081 |
| 2 | `firstName = other.firstName;` | Sipho | Mokoena | 29 | F | 9702140123081 |
| 3 | `surName = other.surName;` | Sipho | Dlamini | 29 | F | 9702140123081 |
| 4 | `age = other.age;` | Sipho | Dlamini | 34 | F | 9702140123081 |
| 5 | `gender = other.gender;` | Sipho | Dlamini | 34 | M | 9702140123081 |
| 6 | `idNum = other.idNum;` | Sipho | Dlamini | 34 | M | 9105225800087 |
| 7 | `return *this;` | Sipho | Dlamini | 34 | M | 9105225800087 |

The object `*sipho` does not change in any step. The two objects are separate after the call. A later change to one object does not change the other.

The output of `main.cpp` is:

```text
Before:
Thandi Mokoena, 29, F, ID: 9702140123081
Sipho Dlamini, 34, M, ID: 9105225800087
After *thandi = *sipho:
Sipho Dlamini, 34, M, ID: 9105225800087
Sipho Dlamini, 34, M, ID: 9105225800087
```

## Common mistakes

- **Skip one attribute.** The test program checks each attribute separately. If the function omits `age`, `firstName`, `surName`, `gender` or `idNum`, the printed line differs from the expected output.
- **Skip an empty `idNum`.** If the function copies `idNum` only when it is not empty, test case 2 prints the old ID `[8807125800083]` (the ID that `a` received in case 1). The expected line shows `[]`.
- **Return `Employee` instead of `Employee&`.** This returns a copy. The statement `Employee& result = (c = b);` then does not compile, because a reference cannot bind to a temporary copy. This also breaks the rule that `operator=` returns the left-hand object.
- **Forget `return *this;`.** The compiler under `-Wall -Werror` reports a warning for a missing return in a function that must return a value. The warning becomes an error, and the program does not compile. The mark is 0.
- **Call the getters on `other`.** `other.getFirstName()` does not compile, because `other` is `const` and the getters are not `const` functions.
