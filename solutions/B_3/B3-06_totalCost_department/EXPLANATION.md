# B3-06 Explanation: totalCost<Department*>

## What the function must do

The general template `totalCost` takes a list and returns 0. The specialization for `Department*` must walk through a `List<Department*>` and add up the `costToCompany()` of each department. The function skips `NULL` entries. An empty list gives 0. The function changes nothing and deletes nothing.

## How the solution works

A **function template** is a recipe for functions. In `template <class T> float totalCost(List<T>& list)`, the name `T` is a template parameter: a placeholder for a type. For a `List<int>`, the compiler sets `T` to `int` and builds a version that returns 0.

A **specialization** is a version of the template that you write for one exact type. When the program calls `totalCost` with a `List<Department*>`, the compiler uses the specialization. `Company::costToCompany()` calls `totalCost(departments)`, so it also uses the specialization.

```cpp
template <>
float totalCost<Department*>(List<Department*>& list) {
```

The line `template <>` tells the compiler that the function is a specialization. The text `<Department*>` after the function name gives the type for `T`. The parameter `list` is a reference to a list (`&` after the type). A reference names the real list and does not copy it. The copy constructor of `List` is private, so the function cannot take the list by value. The definition must match the declaration in `Templates.h` exactly.

```cpp
    float total = 0;
```

`total` holds the running sum. It starts at 0, so an empty list returns 0. Without this value, the sum would start from an undefined value.

```cpp
    Node<Department*>* curr = list.head();
```

`totalCost` is not a member of `List`, so the function cannot use the private member `headNode`. The member function `head()` returns the first node, or `NULL` for an empty list. `curr` points at the node that the loop visits.

```cpp
    while (curr != NULL) {
```

The loop continues while `curr` points at a node. After the last node, `curr` becomes `NULL`, and the loop ends. For an empty list, `head()` returns `NULL`, so the loop does not run, and the function returns 0.

```cpp
        Department* department = curr->getData();
```

`getData()` returns the stored `Department*`. The line copies the pointer into the local variable `department`. This copies the address only. The function does not take ownership of the department.

```cpp
        if (department != NULL) {
            total += department->costToCompany();   // virtual: the subclass rule is used
        }
```

The list can hold `NULL` pointers, because `prepend(NULL)` is allowed. The condition `department != NULL` skips these entries. A call through a `NULL` pointer is undefined behaviour: the C++ rules do not say what happens. In this program, it stops with a segmentation fault. So the check must come before the call. A `NULL` entry adds nothing to the total.

The operator `->` calls a member function through a pointer. The function `costToCompany()` is virtual. C++ therefore calls the version that belongs to the real type of the object, even though the pointer type is `Department*`. A `Sales` object uses 15000 per employee, an `HR` object uses 12000, a `Marketing` object uses 18000 and a `Development` object uses 25000. The base `Department` returns 0. The operator `+=` adds the cost to `total`.

```cpp
        curr = curr->next();
    }
    return total;
}
```

`next()` returns the next node. The assignment moves `curr` forward. The assignment must run for every node, also for a node with a `NULL` entry, so it is outside the `if`. If the assignment were inside the `if`, a `NULL` entry would stop `curr` from moving, and the loop would never end. After the loop, the function returns the sum.

## Trace

The call is `yyra.costToCompany();` from `main.cpp`, which calls `totalCost(departments)`. The company holds `Sales` with 1 employee, `Marketing` with 2 employees and `Development` with 1 employee. The function `addDepartment` uses `prepend`, so the list order is `Development`, `Marketing`, `Sales`.

| Step | `curr` holds | `department != NULL` | `costToCompany()` | `total` |
|---|---|---|---|---|
| Start | none | not applicable | not applicable | 0 |
| Round 1 | `Development` | true | 1 * 25000 = 25000 | 25000 |
| Round 2 | `Marketing` | true | 2 * 18000 = 36000 | 61000 |
| Round 3 | `Sales` | true | 1 * 15000 = 15000 | 76000 |
| End | `NULL` | the loop condition `curr != NULL` is false | not applicable | 76000 |

The function returns 76000.

The call `totalCost(numbers)` on a `List<int>` uses the general template and returns 0. The call `totalCost(empty)` on an empty `List<Department*>` uses the specialization, and the loop does not run.

The output of `main.cpp` is:

```text
totalCost(numbers): 0
Company cost: R76000
totalCost(empty): 0
```

## Common mistakes

- **Omit the `NULL` check.** The edge test has `NULL` entries. The call `department->costToCompany()` on a `NULL` pointer is undefined behaviour. In the edge test, valgrind reports `Invalid read of size 8` in the `Mixed` call, and the program stops with a segmentation fault (signal 11).
- **Do not set `total` to 0.** With `float total;`, the sum starts from an undefined value. The compiler gives no warning with the course flags, so the code builds. In `main.cpp`, the printed values happened to be correct, but valgrind reports `Conditional jump or move depends on uninitialised value(s)` and `Use of uninitialised value of size 8`. The result cannot be trusted, also for an empty list, and the valgrind errors cost marks.
- **Place `curr = curr->next();` inside the `if`.** A `NULL` entry then leaves `curr` unchanged, and the loop does not end. In the edge test, the program hangs at the `Mixed` call and prints nothing more.
- **Delete the departments in `totalCost`.** The company deletes them in `~Company()`, and `main` deletes the others. Each department is then deleted twice. In `main.cpp`, the output is still correct, but valgrind reports `Invalid read` and `Invalid free() / delete / delete[] / realloc()` errors when `~Company()` deletes the departments again. The function must not change the list.
- **Use `list.headNode`.** The member is private, and `totalCost` is not a member of `List`. The compiler reports that `headNode` is private within this context, and the code does not compile. The function must use `list.head()`.
- **Take the list by value**, as in `List<Department*> list`. The definition does not match the declaration in `Templates.h`. The compiler reports that the template-id `totalCost<Department*>` does not match any template declaration, and the code does not compile. The copy constructor of `List` is also private, so a list cannot be passed by value.
