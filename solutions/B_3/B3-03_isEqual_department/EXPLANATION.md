# B3-03 Explanation: isEqual<Department*>

## What the function must do

The general template `isEqual` compares two values with `==`. For two `Department*` pointers, `==` compares addresses, so two different objects are never equal. The specialization for `Department*` must treat two departments as equal when their `costToCompany()` values are equal. Two `NULL` pointers are equal. One `NULL` pointer and one department are not equal.

## How the solution works

A **function template** is a recipe for functions. In `template <class T> bool isEqual(T a, T b)`, the name `T` is a template parameter: a placeholder for a type. For `isEqual(5, 6)`, the compiler sets `T` to `int` and builds a version for `int`.

A **specialization** is a version of the template that you write for one exact type. When the program calls `isEqual` with two `Department*` values, the compiler uses the specialization and not the general template.

```cpp
template <>
bool isEqual<Department*>(Department* a, Department* b) {
```

The line `template <>` tells the compiler that the function is a specialization. The text `<Department*>` after the function name gives the type for `T`. The parameters `a` and `b` are pointers. A **pointer** holds the address of an object, or `NULL` when it points at no object. The definition must match the declaration in `Templates.h` exactly. That declaration comes after the general template and before any call, so `main.cpp` calls this specialization.

```cpp
    if (a == NULL && b == NULL) {
        return true;
    }
```

The operator `&&` means "and". The condition is true only when both pointers are `NULL`. The function returns `true` for this case, because two missing departments are equal by the rule of the question. This check must come first. The next check uses `||` ("or"), which is true when one pointer is `NULL`. If the order were reversed, two `NULL` pointers would reach the "or" check and return `false`.

```cpp
    if (a == NULL || b == NULL) {
        return false;
    }
```

At this line, the first check has already handled the case where both pointers are `NULL`. If the condition is true here, exactly one pointer is `NULL`. A missing department and a real department are not equal, so the function returns `false`. This check also protects the next line. The next line calls a function through both pointers. A call through a `NULL` pointer is undefined behaviour: the C++ rules do not say what happens. In this program, it stops with a segmentation fault.

```cpp
    return a->costToCompany() == b->costToCompany();
```

At this line, both pointers point at real departments. The operator `->` calls a member function through a pointer. The function `costToCompany()` is virtual. C++ therefore calls the version that belongs to the real type of the object, even though the pointer type is `Department*`. A `Sales` object uses the rate of 15000 per employee, an `HR` object uses 12000, a `Marketing` object uses 18000 and a `Development` object uses 25000. The base `Department` returns 0.

The operator `==` compares the two costs. The result of the comparison (`true` or `false`) is the result of the function. The type of department does not matter, only the cost. The function does not delete or change the departments, so it allocates and frees no memory.

## Trace

The calls come from `main.cpp`. The first three calls use the general template. The last two calls use the specialization.

| Call | Template used | Check `a == NULL && b == NULL` | Check `a == NULL \|\| b == NULL` | Costs compared | Result |
|---|---|---|---|---|---|
| `isEqual(5, 5)` | general | not applicable | not applicable | `5 == 5` | true |
| `isEqual(5, 6)` | general | not applicable | not applicable | `5 == 6` | false |
| `isEqual(string("HR"), string("HR"))` | general | not applicable | not applicable | `"HR" == "HR"` | true |
| `isEqual(marketing, hr)` | specialization | false | false | `2 * 18000 = 36000` and `3 * 12000 = 36000` | true |
| `isEqual(sales, hr)` | specialization | false | false | `1 * 15000 = 15000` and `36000` | false |

The function `compare` prints `equal` for `true` and `not equal` for `false`.

The output of `main.cpp` is:

```text
5 and 5: equal
5 and 6: not equal
HR and HR: equal
Marketing R36000, HR R36000, Sales R15000
Marketing and HR: equal
Sales and HR: not equal
```

## Common mistakes

- **Compare the pointers, as in `return a == b;`.** This compares addresses. `Marketing and HR` are two different objects, so the output shows `not equal`, and the expected output shows `equal`.
- **Omit the `NULL` checks.** The edge tests pass `NULL` pointers. A call such as `a->costToCompany()` on a `NULL` pointer is undefined behaviour. In the edge test, the first call `isEqual(none, none)` already fails: valgrind reports `Invalid read of size 8`, and the program stops with a segmentation fault (signal 11) before it prints any line.
- **Check for one `NULL` before both `NULL`.** The call `isEqual(none, none)` then returns `false`, and the expected output is `equal`.
- **Compare names or types.** The question compares costs only. A function that compares `getName()` returns `false` for `Marketing and HR`, and the expected output is `equal`.
