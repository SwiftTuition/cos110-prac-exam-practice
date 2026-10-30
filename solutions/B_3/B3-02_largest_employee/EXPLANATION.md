# B3-02 Explanation: largest<Employee>

## What the function must do

The general template `largest` returns the larger of two values, found with the `>` operator. The class `Employee` has no `>` operator, so the general template cannot compile for employees. The specialization for `Employee` must compare the ages of the two employees. It returns the older employee, and it returns `b` when the ages are equal.

## How the solution works

A **function template** is a recipe for functions. In `template <class T> T largest(T a, T b)`, the name `T` is a template parameter: a placeholder for a type. For `largest(3, 7)`, the compiler sets `T` to `int` and builds a version for `int`. In that version, the line `a > b` compares two integers.

For `Employee`, the line `a > b` has no meaning, because the class does not define `>`. A **specialization** is a version of the template that you write for one exact type. When the program calls `largest` with two `Employee` objects, the compiler uses the specialization and not the general template.

```cpp
template <>
Employee largest<Employee>(Employee a, Employee b) {
```

The line `template <>` tells the compiler that this function is a specialization. The text `<Employee>` after the function name gives the type for `T`. The definition must match the declaration in `Templates.h` exactly: the same return type, the same name and the same parameter types. The declaration appears in `Templates.h` after the general template and before any call, so `main.cpp` calls this specialization.

The parameters `a` and `b` are passed by value. C++ makes a copy of each argument with the `Employee` copy constructor. The function returns an `Employee` by value, which makes another copy. The copy keeps every attribute, including `idNum`. The function does not use `new`, so it allocates nothing and frees nothing.

```cpp
    if (a.getAge() > b.getAge()) {
        return a;
    }
    return b;
```

The condition `a.getAge() > b.getAge()` compares the two ages, which are `int` values. The function uses `getAge()` because the attribute `age` is private. The comparison `>` works on `int`, so it compiles.

If the age of `a` is greater, the function returns `a`. In every other case, the function reaches `return b;`. This includes the case where the ages are equal. The general template has the same rule: it returns `b` when the values are equal.

The comparison must use `>` and not `>=`. With `>=`, equal ages would return `a`, and the result would differ from the general template.

## Trace

The calls come from `main.cpp`. The first three calls use the general template. The last two calls use the specialization.

| Call | Template used | Comparison | Result |
|---|---|---|---|
| `largest(3, 7)` | general, `T` is `int` | `3 > 7` is false | `7` |
| `largest(2.5, 1.5)` | general, `T` is `double` | `2.5 > 1.5` is true | `2.5` |
| `largest(string("apple"), string("pear"))` | general, `T` is `string` | `"apple" > "pear"` is false | `pear` |
| `largest(thandi, sipho)` | specialization | `29 > 34` is false, so the function returns `b` | Sipho |
| `largest(sipho, thandi)` | specialization | `34 > 29` is true, so the function returns `a` | Sipho |

In both of the last two calls, the older employee is Sipho. The function returns a copy of Sipho.

The output of `main.cpp` is:

```text
7
2.5
pear
Sipho Dlamini, 34, M, ID: none
Sipho Dlamini, 34, M, ID: none
```

## Common mistakes

- **Write `a > b` for the employees.** The class `Employee` has no `operator>`. The compiler reports an error, and the mark is 0. The function must compare `a.getAge()` and `b.getAge()`.
- **Use `>=` instead of `>`.** When the ages are equal, the function returns `a`. The first edge test (`Anna` and `Piet`, both aged 41) expects `Piet` for `largest(anna, piet)`, so the output differs.
- **Return the younger employee.** If the function uses `<`, or swaps the two returns, it returns the younger employee whenever the ages differ. In `main.cpp`, both lines then show `Thandi Mokoena, 29, F, ID: none` and not Sipho. With swapped returns, equal ages also give `a`, so the first two edge lines are wrong too.
- **Change the header line.** If the definition does not match the declaration in `Templates.h` (for example, `Employee& a` instead of `Employee a`), the compiler reports that the specialization does not match any template declaration, and the mark is 0.
