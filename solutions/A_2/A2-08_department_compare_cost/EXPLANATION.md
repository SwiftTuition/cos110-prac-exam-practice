# A2-08 Explanation: Department operator< and operator> by cost

## What the function must do

The two operators compare two `Department` objects by their monthly cost to the company. The operator `<` returns `true` when the left department costs less than the right department. The operator `>` returns `true` when the left department costs more.

If the two costs are equal, both operators return `false`. The functions compare costs, not the number of employees, because each department type has its own cost per employee.

## How the solution works

```cpp
// costToCompany() is virtual, so each department uses its own cost rule.
bool Department::operator<(Department& other) {
    return costToCompany() < other.costToCompany();
}

bool Department::operator>(Department& other) {
    return costToCompany() > other.costToCompany();
}
```

**Overloaded operators as members.** `operator<` and `operator>` are member functions of `Department`. They give meaning to `x < y` and `x > y`. In the expression `x < y`, the object `x` on the left is the current object. The object `y` on the right is the parameter `other`.

**The parameter.** `Department& other` is a reference. A reference is another name for an existing object, so the function makes no copy. The reference is not `const`, because `costToCompany()` is not a `const` member function. A `const` object cannot call it. The function declares `Department&` to match `Department.h`.

**The virtual call.** `Sales`, `Marketing`, `HR` and `Development` are subclasses of `Department`. The function `costToCompany()` is `virtual`.

- A `virtual` function runs the version that belongs to the real object, even when the code reaches the object through a `Department&`.
- In `main.cpp`, `x` and `y` have the type `Department&`, but they refer to a `Sales` object and a `Development` object. The call runs `Sales::costToCompany` and `Development::costToCompany`.
- The subclass versions multiply the number of employees by a rate. The rates are R15000 for Sales, R18000 for Marketing, R12000 for HR and R25000 for Development. The base `Department` returns 0.

**The two cost calls.** In `costToCompany() < other.costToCompany()`, the call without an object name runs on the current object, as if written `this->costToCompany()`. The pointer `this` points to the current object. The call `other.costToCompany()` runs on the right-hand object. Both calls use the virtual rule of each real object.

**The comparison.** The built-in `<` on two `float` values gives `true` or `false`. The built-in `>` works the same way. The function returns this `bool` at once. The function has no `if`.

- For equal costs, `<` and `>` are both `false`. The built-in operators use strict comparison, so equal values give `false` for both.
- The function `>` does its own comparison. It does not use `!(*this < other)`. That expression would give `true` for equal costs.
- A department compared with itself gives `false` for both operators, because the two costs are equal.

The functions allocate and free nothing, so valgrind reports no memory problem from them.

## Trace

The calls come from `compare` in `main.cpp`. The department `sales` has one team of 2 employees. The department `dev` has one team of 1 employee.

**`compare(*sales, *dev)`**

| Step | Expression | Value |
|---|---|---|
| 1 | `costToCompany()` on `sales` (current object) | 2 employees times 15000, which is `30000` |
| 2 | `other.costToCompany()` on `dev` | 1 employee times 25000, which is `25000` |
| 3 | `30000 < 25000` | `false` |
| 4 | `30000 > 25000` | `true` |

**`compare(*hr, *dev)`**. The department `hr` has one team with 0 employees.

| Step | Expression | Value |
|---|---|---|
| 1 | `costToCompany()` on `hr` | 0 employees times 12000, which is `0` |
| 2 | `other.costToCompany()` on `dev` | `25000` |
| 3 | `0 < 25000` | `true` |
| 4 | `0 > 25000` | `false` |

The ExpectedOutput of `main.cpp` is:

```text
Sales costs R30000
Development costs R25000
HR costs R0
Sales < Development: false
Sales > Development: true
Development < Sales: true
Development > Sales: false
HR < Development: true
HR > Development: false
```

## Common mistakes

1. **Using `<=` and `>=`.** Two departments with equal costs then return `true`. The edge test compares Marketing (5 employees, R90000) with Sales (6 employees, R90000), and both operators must return `false`. The output of the edge test then differs from the expected output.
2. **Comparing the number of employees.** A version that compares `countEmployees()` ignores the rate. In the edge test, Marketing has 5 employees and Sales has 6, but their costs are equal. The output of the edge test then differs from the expected output.
3. **Calling the base version with a scope name.** A call such as `Department::costToCompany()` turns off the virtual rule. The base version returns 0 for every department, so every comparison gives `false`.
4. **Writing `>` as `!(*this < other)`.** For equal costs, `<` gives `false`, and the `!` makes `>` give `true`. The question requires `false`.
