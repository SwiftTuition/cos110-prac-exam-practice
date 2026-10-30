# A2-11 Explanation: Employee prefix and postfix operator++

## What the function must do

Both increment operators give an `Employee` a birthday. Each one adds 1 to `age` and changes nothing else.

The two versions return different things. The prefix version `++e` returns the employee itself. The postfix version `e++` returns a copy of the employee as it was before the birthday.

## How the solution works

```cpp
// Prefix: ++e
Employee& Employee::operator++() {
    age++;
    return *this;
}

// Postfix: e++ (the int parameter only tells the two versions apart)
Employee Employee::operator++(int) {
    Employee old(*this);
    age++;
    return old;
}
```

**Two functions with one name.** C++ has two forms of `++`. Both are overloaded operators of `Employee`. The compiler tells them apart by the parameter list.

- `operator++()` has no parameter. The compiler uses it for `++e`.
- `operator++(int)` has one `int` parameter. The compiler uses it for `e++`. The parameter has no name, because the function never uses its value. It exists only to mark the postfix version.

**Prefix: `Employee& Employee::operator++()`.**

- The return type `Employee&` is a reference. A reference is another name for an existing object. The function returns the real employee, not a copy.
- `age++;` adds 1 to the member `age` of the current object. Nothing else changes: the names, gender and ID number stay as they are.
- `return *this;` returns the current object. Inside a member function, `this` is a pointer to the current object. A pointer holds the address of an object. The `*` follows the pointer and gives the object itself.
- The reference points to the same object that the caller holds. Because of this, `++(++e)` adds 2 to `e`. The inner call returns `e`, and the outer call increments `e` again. The edge test also checks this: it stores the result of `++lebo` in `Employee& ref`, and a change through `ref` changes `lebo`.
- The function adds 1 first and returns afterwards. The prefix operator returns the new value, so the add must come before the return.

**Postfix: `Employee Employee::operator++(int)`.**

- The return type `Employee` has no `&`. The function returns a new object by value.
- `Employee old(*this);` creates a local object `old` with the copy constructor `Employee(const Employee&)`. The expression `*this` is the current object. The copy holds the age before the birthday.
- `age++;` adds 1 to the age of the current object. The copy `old` is a separate object and keeps the old age.
- `return old;` returns the copy.
- The copy must come before `age++`. If `age++` came first, the copy would hold the new age, and the postfix version would behave like the prefix version.
- The function cannot return a reference. The local variable `old` ends when the function ends. A reference to it would not be valid. With `-Wall -Werror`, the compiler rejects code that returns a reference to a local variable.

**Why the postfix version returns by value.** The caller of `e++` receives the old state of the employee. The employee itself already holds the new state. The only way to give back the old state is a separate object.

The functions allocate nothing with `new`, so valgrind reports no memory problem from them.

## Trace

The calls come from `main.cpp`. The employee `thandi` starts with age 29.

| Step | Statement | Operator called | `age` of `thandi` after | Value returned |
|---|---|---|---|---|
| 1 | `++(*thandi);` | prefix | 30 | reference to `thandi` (unused) |
| 2 | `cout << *thandi << endl;` | none | 30 | not applicable |
| 3 | `(*thandi)++` inside `Employee before = ...` | postfix | 31 | copy `old` with age 30 |
| 4 | `before` is built from the returned copy | none | 31 | `before` has age 30 |

Inside the postfix call in step 3, the order is:

| Order | Statement | `old.age` | `age` of `thandi` |
|---|---|---|---|
| 1 | `Employee old(*this);` | 30 | 30 |
| 2 | `age++;` | 30 | 31 |
| 3 | `return old;` | 30 | 31 |

The output is:

```text
Thandi Mokoena, 30, F, ID: none
Before: Thandi Mokoena, 30, F, ID: none
After: Thandi Mokoena, 31, F, ID: none
```

## Common mistakes

1. **Returning the new value from the postfix version.** A postfix version that increments first and then copies returns the new age. The line `Before:` would show 31 where 30 is expected. The output of `main` then differs from the expected output.
2. **Returning a copy from the prefix version.** A prefix version such as `Employee* copy = new Employee(*this); age++; copy->age++; return *copy;` returns a reference to a separate object, not to the employee itself. In `main` the output still looks correct, but the copy is never deleted. Valgrind reports `definitely lost: 112 bytes in 1 blocks`. In the edge test, `++(++lebo)` then adds only 1 to `lebo`, and `ref.setIDNum(...)` changes the copy and not `lebo`, so the edge output differs.
3. **Returning a reference to the local variable `old`.** A return type of `Employee&` in the postfix version, with `return old;`, returns a reference to a variable that ends with the function. This definition does not match `Employee operator++(int);` in `Employee.h`, so the compiler reports `no declaration matches 'Employee& Employee::operator++(int)'`. A compile error gives the mark 0.
4. **Using the same signature for both versions.** Two functions named `operator++()` with no parameter cannot exist together. The postfix version needs the extra `int` parameter, as in `Employee.h`. A postfix definition written as `Employee Employee::operator++()` gives `no declaration matches 'Employee Employee::operator++()'`.
