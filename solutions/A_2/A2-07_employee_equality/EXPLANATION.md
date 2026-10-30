# A2-07 Explanation: Employee::operator== and operator!=

## What the function must do

The two operators compare two `Employee` objects. The operator `==` returns `true` when the two ID number strings are equal. It ignores names, age and gender.

An employee with no ID number has the empty string `""` as the ID. Two such employees are therefore equal. The operator `!=` must always return the opposite of `==`.

## How the solution works

```cpp
bool Employee::operator==(const Employee& other) const {
    // Only the ID numbers are compared. Two IDs that are not set ("") are equal too.
    return idNum == other.idNum;
}

bool Employee::operator!=(const Employee& other) const {
    return !(*this == other);
}
```

**Overloaded operators as members.** `operator==` and `operator!=` are member functions. They give meaning to `x == y` and `x != y` for two `Employee` objects. In the call `x == y`, the object on the left is the current object, and `y` is the parameter `other`.

**The parameter.** `const Employee& other` is a reference to the other employee. A reference is another name for an existing object, so the function makes no copy. The word `const` in front means the function must not change `other`.

**The `const` after the parameter list.** The second `const` makes the function a `const` member function. It promises not to change the current object. Both operators need it for two reasons.

- The header `Employee.h` declares them with `const`. The definition in `A_2.cpp` must match the declaration.
- In `main.cpp`, the function `compare` receives `const Employee&` parameters. A `const` object can call only `const` member functions.

**The `==` operator.** The statement `return idNum == other.idNum;` compares two `string` values. The `string` class defines `==` as "same characters in the same order". The expression gives a `bool`, and the function returns it.

- The function reads `other.idNum` directly. This is allowed because `other` has the same class as the current object. Private members are open to code in the same class.
- The function has no `if` and no special case for the empty ID. The constructor sets `idNum` to `""`. Two employees with no ID both hold `""`, and `"" == ""` is `true`. This gives the required result for row 4 of the question, where both IDs are not set.
- The function does not compare the names, age or gender. The question says only the ID matters.
- When an employee compares with itself, the two strings are the same, so the result is `true`.

**The `!=` operator.** The statement `return !(*this == other);` calls the operator `==` and reverses the answer.

- Inside a member function, `this` is a pointer to the current object. `*this` follows the pointer and gives the object itself. So `*this == other` calls the `operator==` above.
- The `!` operator turns `true` into `false` and `false` into `true`.
- The function reuses `==` and does not compare the ID numbers a second time. If the rule for `==` changes, the function `!=` follows it. The two operators cannot disagree.
- The function `!=` calls `==`, and `==` does not call `!=`. The calls do not repeat forever.

The functions allocate and free nothing, so valgrind reports no memory problem from them.

## Trace

The calls come from `compare` in `main.cpp`. The line `bool same = (x == y);` calls `==`. The line `bool different = (x != y);` calls `!=`.

**Call 1: `a` and `b`, no IDs set.** Both `idNum` values are `""`.

| Step | Expression | Value |
|---|---|---|
| 1 | `idNum == other.idNum` | `"" == ""`, which is `true` |
| 2 | `*this == other` inside `!=` | `true` |
| 3 | `!(*this == other)` | `false` |

**Call 3: `a` and `c`, different IDs.** The ID of `a` is `9702140123081`. The ID of `c` is `9702140123082`. The names also differ, but the function ignores them.

| Step | Expression | Value |
|---|---|---|
| 1 | `idNum == other.idNum` | the strings differ in the last character, so `false` |
| 2 | `*this == other` inside `!=` | `false` |
| 3 | `!(*this == other)` | `true` |

For call 2, `a` and `b` both hold `9702140123081`, so `==` gives `true` and `!=` gives `false`. The ExpectedOutput of `main.cpp` is:

```text
a, b (no IDs): == gives true, != gives false
a, b (same ID): == gives true, != gives false
a, c (different IDs): == gives false, != gives true
```

## Common mistakes

1. **Treating an ID that is not set as never equal.** A version such as `idNum != "" && idNum == other.idNum` returns `false` for two employees without an ID. The question requires `true`. The output of `main` then differs from the expected output.
2. **Comparing the names as well.** The edge test compares two employees with the same ID and different names. The expected result is `true`. The output of the edge test then differs from the expected output.
3. **Making `!=` give the same result as `==`.** If the body of `!=` is `return idNum == other.idNum;`, the two operators always agree. The output of `main` then differs from the expected output.
4. **Calling `*this != other` inside `operator!=`.** The function then calls itself, and the calls never end. The compiler (g++ 13 with `-Wall`) detects this and gives `infinite recursion detected`. Under `-Werror` this warning is an error, so the program does not compile. A compile error gives the mark 0.
