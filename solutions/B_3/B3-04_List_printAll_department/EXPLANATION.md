# B3-04 Explanation: List<Department*>::printAll

## What the function must do

The general `List<T>::printAll()` prints each value as `<index>: <value>`. For `List<Department*>`, the value is a pointer, and the general version would print an address. The specialization must print the department that each pointer points to. It must also handle an empty list and a `NULL` entry.

## How the solution works

`List<T>` is a **class template**. The name `T` is a template parameter: a placeholder for a type such as `int`, `string` or `Department*`. The compiler builds a separate class for each type that the program uses.

A **member specialization** replaces one member function of the template for one exact type. Here, `printAll()` has its own version for `T = Department*`. For all other types, the program uses the general `printAll()`.

```cpp
template <>
void List<Department*>::printAll() {
```

The line `template <>` tells the compiler that this function is a specialization. The concrete type goes after the class name: `List<Department*>`. The type does not go after the function name. The text `template <class T>` does not appear here, because `T` is already fixed to `Department*`. Inside this function, `headNode` has the type `Node<Department*>*`. The definition must match the declaration at the bottom of `List.h`.

The file starts with `#include "Department.h"` and `#include "List.h"`. `List.h` only names the class `Department`. The function uses `*department`, which needs the full class, so the file includes `Department.h`.

```cpp
    if (headNode == NULL) {
        cout << "Empty List" << endl;
        return;
    }
```

`headNode` is a pointer to the first node. It is `NULL` when the list is empty. If the condition is true, the function prints `Empty List` and leaves the function with `return`. Without this check, the loop below would run zero times and print nothing. The question requires the text `Empty List`, as in the general version.

```cpp
    Node<Department*>* curr = headNode;
    int index = 0;
```

`curr` points at the node that the loop visits. It starts at the first node. `index` counts the position of the node, from 0. Each node holds one `Department*`.

```cpp
    while (curr != NULL) {
```

The loop continues while `curr` points at a node. After the last node, `curr` becomes `NULL`, and the loop ends. The loop does not change the list and does not delete a node.

```cpp
        Department* department = curr->getData();
```

`getData()` returns the stored value, which is a `Department*`. The line copies the pointer into the local variable `department`. This copies the address only. It does not copy the department and does not take ownership. The list does not own the departments in this question. `main` deletes them.

```cpp
        if (department == NULL) {
            cout << index << ": No department" << endl;
        } else {
            cout << index << ": " << *department;   // operator<< ends its own lines
        }
```

The condition `department == NULL` checks for a `NULL` entry. The list can hold `NULL` pointers, because `prepend(NULL)` is allowed. For a `NULL` entry, the expression `*department` would follow a `NULL` pointer. This is undefined behaviour: the C++ rules do not say what happens. In this program, it stops with a segmentation fault. So the check must come before it. For a `NULL` entry, the function prints `<index>: No department` and a newline.

For a real department, `*department` is the department that the pointer points to. The operator `<<` is **overloaded** for `Department`: the class defines its own version of `<<`. This version prints `<name> (cost R<cost>)` and a newline, and then each team. The functions `getName()` and `costToCompany()` are virtual, so a `Sales` object prints `Sales`. The Department operator already ends every line, so the function does not add `endl`.

```cpp
        curr = curr->next();
        index++;
    }
}
```

`next()` returns the next node. The assignment moves `curr` forward. `index++` adds 1 to the position. If the function did not move `curr`, the loop would never end.

## Trace

The call is `departments.printAll();` from `main.cpp`. The list was built with `departments.prepend(sales)` and then `departments.prepend(hr)`. The function `prepend` adds at the front, so the list is `hr` then `sales`. HR has 2 employees (2 times 12000 is 24000). Sales has 1 employee (1 times 15000 is 15000).

| Step | `curr` | `index` | Check | Printed |
|---|---|---|---|---|
| Start | first node | 0 | `headNode == NULL` is false | nothing |
| Round 1 | node with `hr` | 0 | `department == NULL` is false | `0: ` and the HR department, with its team |
| Move | node with `sales` | 1 | none | nothing |
| Round 2 | node with `sales` | 1 | `department == NULL` is false | `1: ` and the Sales department, with its team |
| Move | `NULL` | 2 | the loop condition `curr != NULL` is false | nothing |

The call `numbers.printAll()` on `List<int>` uses the general version. It prints `0: 10`, `1: 20` and `2: 30`.

The output of `main.cpp` is:

```text
0: 10
1: 20
2: 30
0: HR (cost R24000)
Team:
  Anna Botha, 41, F, ID: none
  Sipho Dlamini, 34, M, ID: none
1: Sales (cost R15000)
Team:
  Thandi Mokoena, 29, F, ID: none
```

## Common mistakes

- **Write the type after the function name**, as in `List<Department*>::printAll<Department*>()`. The compiler rejects this form with `error: expected initializer before '<' token`. The program does not compile, and the mark is 0.
- **Write `template <class T>` instead of `template <>`.** The definition does not match any declaration. The compiler reports `error: no declaration matches 'void List<Department*>::printAll()'`.
- **Use `Node<T>*` inside the specialization.** The name `T` is not defined in a full specialization. The compiler reports `error: 'T' was not declared in this scope`, and the code does not compile. The function must use `Node<Department*>*`.
- **Omit the `NULL` check.** The edge test has a `NULL` entry. The code `*department` on a `NULL` pointer is undefined behaviour. In the edge test, valgrind reports `Invalid read of size 8` at the `NULL` entry, and the program stops with a segmentation fault (signal 11). The lines after `0: Development ...` are never printed.
- **Print the pointer, as in `cout << curr->getData()`.** The program prints an address, and the output differs from the expected output.
- **Delete the department inside the function.** `main` deletes each department, so each department is deleted twice. In `main.cpp`, valgrind reports `Invalid read` and `Invalid free() / delete / delete[] / realloc()` errors when `main` deletes the departments again. In the edge test, `dev` is printed a second time after it was deleted, and the output shows `0: Department (cost R0)` instead of `0: Development (cost R25000)`.
- **Add `endl` after `*department`.** The Department operator already ends every line, so the output gets an extra blank line.
