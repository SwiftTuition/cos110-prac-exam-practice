# B1-08 Explanation: recursive totalCost

## What the function must do

The function `Company::totalCost(curr)` adds up the cost of departments in a linked list. The list is `List<Department*>`, so each node stores a `Department*`. The function starts at the node `curr` and adds the value of `costToCompany()` for each department until the end of the list.

A node can store `NULL` instead of a department. That node adds `0`. If `curr` is `NULL`, there are no nodes, so the answer is `0`. This also covers an empty company. The given `Company::costToCompany()` calls `totalCost(departments.head())`.

## How the solution works

The function reads the list and the departments. The function allocates no memory and frees none. The `Company` destructor already deletes the departments, so `totalCost` must not delete them.

```cpp
if (curr == NULL) {
    return 0;
}
```

This is the base case. The value `NULL` appears after the last node, and it also appears as the head of an empty list. In both situations there are no departments left to add, so the answer is `0`. Without this `if`, every call would make another call, so the recursion could never end. g++ 13 sees this and reports `infinite recursion detected`. Under `-Wall -Werror` the build fails.

```cpp
float here = 0;
if (curr->getData() != NULL) {
    here = curr->getData()->costToCompany();
}
```

The variable `here` holds the cost of the department in the current node. The arrow `->` calls a function through a pointer. The call `curr->getData()` returns the stored `Department*`. The `if` checks that this pointer is not `NULL`. A node can store `NULL`, and calling `costToCompany()` through a null pointer is undefined behaviour. For a `NULL` department, `here` stays `0`.

The function `costToCompany()` is `virtual` in `Department`. When the pointer points to a `Sales`, `Marketing`, `HR` or `Development` object, the call runs the version of that class. Each version multiplies the number of employees by a rate. The call is legal here because `costToCompany()` is `public` in `Department`, and the pointer has the type `Department*`.

```cpp
return here + totalCost(curr->next());
```

This is the recursive case. The call `curr->next()` returns the pointer to the following node. The call `totalCost(curr->next())` adds the costs of all later departments. Each call moves one node forward, so the calls move toward `NULL`, which is the base case. The addition runs after the recursive call returns.

## Trace

In `main.cpp`, the program adds `dev`, then `sales`, then `hr` with `addDepartment`. The function `addDepartment` adds at the front of the list, so the list order is `HR`, `Sales`, `Development`.

- `HR` has 1 employee, so its cost is `1 * 12000 = 12000`.
- `Sales` has 2 employees (one in each of its two teams), so its cost is `2 * 15000 = 30000`.
- `Development` has 2 employees, so its cost is `2 * 25000 = 50000`.

The call is `yyra.costToCompany()`, which calls `totalCost(departments.head())`.

| Call | curr points to | Branch taken | `here` | Result |
|---|---|---|---|---|
| 1 | node with `HR` | recursive case | 12000 | waits for call 2 |
| 2 | node with `Sales` | recursive case | 30000 | waits for call 3 |
| 3 | node with `Development` | recursive case | 50000 | waits for call 4 |
| 4 | `NULL` | base case | not set | returns `0` |

The calls return in the order 4, 3, 2, 1:

- Call 3 returns `50000 + 0 = 50000`.
- Call 2 returns `30000 + 50000 = 80000`.
- Call 1 returns `12000 + 80000 = 92000`.

The call `totalCost(first->next())` starts at the `Sales` node and returns `80000`. The call `totalCost(first->next()->next())` starts at the `Development` node and returns `50000`.

The output of `main.cpp` is:

```text
Company with 3 departments
HR of size 1:
Slot 0: Team of size 1:
  0: Lebo Nkosi, 25, F, ID: none
Sales of size 2:
Slot 0: Team of size 3:
  0: Anna Botha, 41, F, ID: none
  1: empty
  2: empty
Slot 1: Team of size 1:
  0: Ravi Naidoo, 38, M, ID: none
Development of size 1:
Slot 0: Team of size 2:
  0: Thandi Mokoena, 29, F, ID: none
  1: Sipho Dlamini, 34, M, ID: none
Total cost: R92000
Cost from the second department: R80000
Cost from the third department: R50000
```

## Common mistakes

- **No check of `curr->getData()` for `NULL`.** The main test still passes, because it has no `NULL` department. The edge test adds `NULL` with `addDepartment(NULL)`. The call `costToCompany()` through a null pointer is undefined behaviour. In the test run, valgrind reported `Invalid read of size 8`, and the program stopped with a segmentation fault (`SIGSEGV`) before the line `2. total:`.
- **No check of `curr` for `NULL`.** Without the base case, every call makes another call, so the recursion can never end. g++ 13 reports `infinite recursion detected`, and under `-Wall -Werror` the build fails. The mark is 0.
- **Calling `countEmployees()` instead of `costToCompany()`.** The function `countEmployees()` is `protected` in `Department`, so `Company` cannot call it. This is a compile error: `'int Department::countEmployees()' is protected within this context`. This function would also leave out the rate of each department.
- **Deleting a department inside `totalCost`.** The `Company` destructor deletes the same department again. A second delete of one object is undefined behaviour. In the test run, the first `Total cost` line was still `R92000`, but the next two lines showed `R0`, and valgrind reported `Invalid read`, `Invalid write` and `Invalid free() / delete / delete[] / realloc()` errors.
- **A loop or a helper function.** QUESTION.md states that either one scores 0. The call to the given `costToCompany()` of a department is allowed.
