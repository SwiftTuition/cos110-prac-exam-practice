# A1-10 Explanation: Team::hire

## What the function must do

The function `hire` makes a new `Employee` with `new`, sets its ID number and adds it to the team. Two calls can throw an `Exception`: `setIDNum` and `addMember`. If one of them throws, the team does not keep the new employee, so `hire` must free it with `delete`. Then `hire` must throw the same error again, so the caller gets the same message.

## How the solution works

```cpp
void Team::hire(string firstName, string surName, int age, char gender, string idNum) {
    Employee* newEmployee = new Employee(firstName, surName, age, gender);
```

The operator `new` allocates an `Employee` on the heap and returns its address. The pointer `newEmployee` holds the address. Memory from `new` stays allocated until the program runs `delete` on it. At this line, `hire` is the only owner of the new employee.

The pointer is declared before the `try` block. A name declared inside a `try` block is not visible in the `catch` block. The `catch` block needs `newEmployee` to free the memory.

```cpp
    try {
        newEmployee->setIDNum(idNum);
        addMember(newEmployee);
```

The order of the two calls is fixed by the question. The ID number is checked first. If the ID number is bad and the team is full, the caller must receive the ID number message. If the first call throws, C++ skips the second call, so `addMember` does not run. If the first call works, `addMember` runs. It stores the pointer in the first empty slot, or it throws `Exception("Team is full")` and the team keeps nothing.

If both calls return normally, the team owns the new employee, and `~Team()` deletes it later. The function `hire` must not delete the employee on this path. A second `delete` would be a double delete.

```cpp
    } catch (Exception& e) {
```

This clause catches an `Exception` thrown by either call. The `&` makes `e` a reference to the thrown object. At this point the team does not hold the new employee, so `hire` is still its only owner.

```cpp
        delete newEmployee;
```

This line frees the employee. Without it, the memory is never freed, and valgrind reports a leak. The `delete` comes before the `throw`. A `throw` leaves the function at once, and no statement after it runs.

```cpp
        throw e;  // "throw;" also works: it throws the same exception again
    }
}
```

This line sends the error on to the caller. The caller of `hire` has its own `try` and `catch` and prints the message.

- The statement `throw e;` throws a copy of `e`. The copy has the type `Exception` and the same message.
- The statement `throw;` without an object throws the exception that is currently being handled, with no copy. It also keeps the real type of the object, which matters if a class derived from `Exception` is thrown. In this question, the given functions throw plain `Exception` objects, so both statements give the same result.
- The function must not print the message or return normally here. If it returned normally, the caller would think the hire worked.

## Trace

The call is the fourth `tryHire` in `main.cpp`: `hire("Lebo", "Nkosi", 25, 'F', "0101014999081")`. The team has `size` 2 and already holds Thandi and Sipho.

| Step | Code | Values | Result |
|---|---|---|---|
| 1 | `new Employee(...)` | Lebo, `'F'`, no ID number | `newEmployee` points to a new object |
| 2 | `setIDNum("0101014999081")` | length 13, digits `4999` give `'F'`, match | the ID number is stored in the new employee |
| 3 | `addMember(newEmployee)` | slot 0 and slot 1 are not `NULL` | throws `Exception("Team is full")` |
| 4 | `catch (Exception& e)` | `e.what()` is `Team is full` | the handler runs |
| 5 | `delete newEmployee;` | | the new employee is freed |
| 6 | `throw e;` | | the exception leaves `hire` |
| 7 | `catch` in `tryHire` | | prints `Caught: Team is full` |

The second `tryHire` call fails earlier. For Sipho with `"9105220800087"`, step 2 throws `ID number does not match gender`, and `addMember` never runs. The handler still frees the new employee. The third call, for Sipho with `"9105225800087"`, passes both steps. The team stores Sipho, and `hire` frees nothing.

The output of `main.cpp` is:

```text
Hired Thandi Mokoena
Caught: ID number does not match gender
Hired Sipho Dlamini
Caught: Team is full
Team:
  Thandi Mokoena, 29, F, ID: 9702140123081
  Sipho Dlamini, 35, M, ID: 9105225800087
```

## Common mistakes

- **Leave out the `delete`.** Each failed hire loses one `Employee`. Valgrind reports a leak. The main test rejected this change through valgrind.
- **Free the employee but do not throw again.** The function then returns normally after a failure. The caller prints `Hired Sipho Dlamini` and `Hired Lebo Nkosi` for hires that failed, and the output differs. The main test rejected this change.
- **Put `delete` after the `throw`.** The `throw` ends the function, so the `delete` never runs. This has the same result as no `delete`: a leak.
- **Call `addMember` before `setIDNum`.** For a full team and a bad ID number, the caller then gets `Team is full`. The question requires the ID number message. The edge test uses a team of size 0 and the ID number `"123"`. It rejected this change. There is a second problem. When `addMember` works and `setIDNum` then throws, the `catch` block deletes an employee that the team still holds. Valgrind reports `Invalid read` and `Invalid free()`.
- **Delete the employee on the success path.** The team still holds the pointer to the freed memory. Printing the team reads the freed employee, and `~Team()` deletes it again. Valgrind reports `Invalid read` and `Invalid free()`, even though the printed output can still look correct.
- **Declare `newEmployee` inside the `try` block.** The `catch` block cannot see the name, and the compiler reports an error.
