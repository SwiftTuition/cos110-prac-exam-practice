# B2-10 Explanation: Company::removeDepartment

## What the function must do

The function `removeDepartment` finds the first department whose name equals `name`. The function then removes its node from the list `departments` and also deletes the `Department` object. If a department is removed, the function returns `true`. If the company has no departments, or no department has that name, the function changes nothing and returns `false`.

Two objects are involved. The list node holds a pointer. The `Department` object is a separate object on the heap. The function must free both.

## How the solution works

A pointer is a variable that holds the address of an object. The operator `->` uses a pointer to reach a member. `NULL` means the pointer points to nothing. `List<Department*>` is a list whose values are `Department*` pointers. For each node, `getData()` returns that pointer.

The question gives these ownership rules:

- `~Company()` deletes every `Department` that is still in the list.
- `List<Department*>` does not delete the `Department` objects. `~Node()` deletes only that stored pointer, not the object it points to.
- `List<T>::remove(T value)` is given. It unlinks and deletes the first node whose data equals `value`. For `Department*`, it compares the pointers.

The search loop starts here:

```cpp
    Node<Department*>* curr = departments.head();
    while (curr != NULL) {
```

- `departments.head()` returns the first node, or `NULL` for an empty list.
- `curr` is the node that the loop checks.
- The condition `curr != NULL` stops the loop after the last node. For a company with no departments, the loop body never runs and the function returns `false`.

The body of the loop:

```cpp
        Department* department = curr->getData();
        if (department->getName() == name) {
```

- `department` is a copy of the pointer in the node. It points to the `Department` object.
- `getName()` is a virtual function. It returns `"Sales"`, `"HR"`, `"Marketing"` or `"Development"` for the matching subclass.
- The test `department->getName() == name` compares two strings. The comparison is case sensitive, so `"hr"` does not match `"HR"`.
- The loop runs from the head, so the first match in list order is the department that the function removes.

The removal:

```cpp
            departments.remove(department);
            delete department;
            return true;
```

1. `departments.remove(department)` finds the node that holds this pointer, links the previous node around it and deletes the node. The call also lowers `size`. The `Department` object is still alive after this call.
2. `delete department` then frees the `Department` object. The destructor is virtual, so the destructor of the subclass runs. The department deletes its teams, and each team deletes its employees.
3. `return true` ends the function at once.

The order is intentional. The list is fixed first, so no node holds a pointer to a freed `Department`, not even for a moment.

The `return true` is needed for a second reason. The node `curr` was deleted by `remove`. After that call, the loop must not run `curr = curr->next()`, because that would read a freed node. The comment in the code says the same: "curr is not used after this".

The loop ends without a match when the next lines run:

```cpp
        curr = curr->next();
    }
    return false;
```

- `curr = curr->next()` moves to the following node. It runs only if the current department did not match.
- `return false` runs after the last node, or for an empty list. The function changed nothing.

Memory: a successful call frees the list node, the `Department`, its teams and its employees. When the company is deleted later, `~Company()` deletes only the departments that remain in the list. The removed department is no longer in the list, so `~Company()` does not delete it a second time.

## Trace

Call from `main.cpp`: `tryRemove(yyra, "HR");`, which runs `company.removeDepartment(name)`. Departments were added with `prepend`, so the list order is the reverse of the add order: `Development->HR->Sales`.

| Step | `curr` points to | `department->getName()` | Test `== "HR"` | Action |
|---|---|---|---|---|
| Setup | Development node | | | `curr = departments.head()`. |
| Iteration 1 | Development node | `Development` | false | `curr` moves to the HR node. |
| Iteration 2 | HR node | `HR` | true | `departments.remove(department)` links the Development node to the Sales node and deletes the HR node. |
| After `remove` | (deleted) | | | `delete department` frees the HR `Department`, its team and its two employees. |
| End | | | | The function returns `true`. |

The call `tryRemove(yyra, "Finance");` checks three nodes, finds no match, reaches `NULL` and returns `false`.

The part of the program output for the removal is:

```text
removeDepartment(HR): true
removeDepartment(Finance): false
Company with 2 departments
Development (cost R25000)
Team:
  Lebo Nkosi, 25, F, ID: none
Sales (cost R15000)
Team:
  Thandi Mokoena, 29, F, ID: none
Total cost: R40000
```

## Common mistakes

- Calling `delete department;` without `departments.remove(department)`. The list keeps a node that holds a pointer to freed memory. Printing the company then reads a freed object. `~Company()` later deletes the same pointer again, which is a double delete. In the main test, the output still says `Company with 3 departments` and prints the freed HR department. valgrind reports "Invalid read of size 8" and "Invalid free() / delete / delete[] / realloc()".
- Calling `departments.remove(department)` without `delete department`. The node is gone, but the `Department` object, its teams and its employees are never freed. The output is still correct, but valgrind reports "definitely lost". The question says `List<Department*>` does not delete the departments.
- Not returning after the removal, so that the loop runs `curr = curr->next()`. The node `curr` was deleted by `remove`. The program reads a freed node, and valgrind reports "Invalid read of size 8". The output is still correct, so only valgrind shows this mistake.
- Using `while (curr->next() != NULL)` as the loop condition. The last node is never checked, so `removeDepartment("Sales")` fails when `Sales` is the tail. For an empty company, `curr` is `NULL`, and the loop test reads `curr->next()` through `NULL`. The main test still passes. The edge test starts with an empty company: valgrind reports "Invalid read of size 8" and the program stops with a segmentation fault (SIGSEGV).
- Deleting the node with `delete curr;` and then fixing nothing else. The previous node still links to the freed node, and `size` is not lowered. The list is broken. In the main test, the company still prints 3 departments, valgrind reports "Invalid read of size 8" when the freed node is printed, and "Invalid free() / delete / delete[] / realloc()" when the list deletes the freed node again. The given `remove` already does the unlinking and the `size` change, so the function should call it.
