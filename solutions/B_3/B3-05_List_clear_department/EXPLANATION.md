# B3-05 Explanation: List<Department*>::clear

## What the function must do

The general `List<T>::clear()` deletes every node. For `List<Department*>`, the list must also delete the `Department` objects, because `Company` has no destructor and nothing else frees them. After the call, `headNode` is `NULL` and `size` is `0`. The destructor `~List()` calls `clear()`, so the specialization also runs when a `Company` is destroyed.

## How the solution works

`List<T>` is a **class template**. The name `T` is a template parameter: a placeholder for a type. A **member specialization** replaces one member function of the template for one exact type. Here, `clear()` has its own version for `T = Department*`.

Each `Node<T>` holds `T* data`. For `List<Department*>`, `data` has the type `Department**`: a pointer to a `Department*`. `~Node()` deletes `data`. This frees only the pointer that the node allocated. It does not delete the `Department` that the pointer points to. The specialization must delete the `Department` itself.

```cpp
template <>
void List<Department*>::clear() {
```

The line `template <>` tells the compiler that this function is a specialization. The concrete type goes after the class name: `List<Department*>`. The text `template <class T>` does not appear here, because `T` is fixed to `Department*`. The definition must match the declaration at the bottom of `List.h`. The file also includes `Department.h`, because `delete` on a `Department*` needs the full class.

```cpp
    Node<Department*>* curr = headNode;
    while (curr != NULL) {
```

`curr` points at the node that the loop visits. It starts at the first node. The condition `curr != NULL` stops the loop after the last node. For an empty list, `headNode` is `NULL`, so the loop does not run, and the function does not use a `NULL` pointer. This makes `clear()` safe to call on an empty list and safe to call twice.

```cpp
        Node<Department*>* temp = curr;
        curr = curr->next();
```

`temp` saves the current node. `next()` returns the next node, and the assignment moves `curr` forward. The function must move `curr` before it deletes the node. After `delete temp`, the function cannot read `next()` from that node.

```cpp
        delete temp->getData();   // the Department (deleting NULL does nothing)
```

`getData()` returns the `Department*` that the node holds. The statement `delete` on this pointer runs the destructor `~Department()`, which is virtual. The destructor that runs belongs to the real type of the object, even through a `Department*`. The department deletes its teams, and each team deletes its employees. A `NULL` entry in the list is safe, because `delete` on a `NULL` pointer does nothing. The function needs no extra `if` for `NULL`.

This line must come before `delete temp;`. The function reads the data through the node. After the node is deleted, the function cannot call `getData()` on it.

```cpp
        delete temp;              // the node, which deletes its copy of the pointer
    }
```

This line deletes the node. `~Node()` deletes `data`, which is the node's own copy of the pointer. Each node and each department is deleted exactly once.

```cpp
    headNode = NULL;
    size = 0;
}
```

After the loop, `headNode` still holds the address of the first deleted node. The line `headNode = NULL;` removes this pointer to freed memory. The line `size = 0;` makes the size match the empty list. These two lines are necessary for two reasons. First, the list can be used again after `clear()`. Second, `~List()` calls `clear()` again when the list is destroyed. A `headNode` that still points at freed memory would make that second call delete the same nodes again.

## Trace

The call is `spare.clear();` from `main.cpp`. The list `spare` holds `Development(2)` and then `Marketing(1)`, because `prepend` adds at the front. Neither department has teams. `D` is the `Development` department and `M` is the `Marketing` department.

| Step | `curr` | `temp` | Action | Freed |
|---|---|---|---|---|
| Start | node 1 (holds `D`) | none | `curr != NULL` is true | nothing |
| Round 1 | node 2 (holds `M`) | node 1 | `curr = curr->next()` | nothing |
| | node 2 | node 1 | `delete temp->getData();` | `D` |
| | node 2 | node 1 | `delete temp;` | node 1 and its pointer copy |
| Round 2 | `NULL` | node 2 | `curr = curr->next()` | nothing |
| | `NULL` | node 2 | `delete temp->getData();` | `M` |
| | `NULL` | node 2 | `delete temp;` | node 2 and its pointer copy |
| End | `NULL` | node 2 | `curr != NULL` is false; the loop ends | nothing |
| After | none | none | `headNode = NULL; size = 0;` | nothing |

The same steps run for the `Company` object `yyra` when `main` ends. `~List()` calls `clear()`. The list holds `HR` and then `Sales`. Each `delete` on a department also frees its team and its employees.

The output of `main.cpp` is:

```text
1->2->3
Empty List (size 0)
Company with 2 departments
HR (cost R24000)
Team:
  Anna Botha, 41, F, ID: none
  Sipho Dlamini, 34, M, ID: none
Sales (cost R15000)
Team:
  Thandi Mokoena, 29, F, ID: none
Total cost: R39000
Spare departments: 2
Spare departments after clear: 0
```

## Common mistakes

- **Delete only the nodes.** If the function deletes `temp` but not `temp->getData()`, `~Node()` frees only the pointer copy. Every `Department`, `Team` and `Employee` stays in memory. The output is still correct, but valgrind reports `definitely lost` and `indirectly lost` blocks for the four departments and everything they own.
- **Read `next()` after `delete temp`.** The code `delete temp; curr = temp->next();` reads a deleted node. This is undefined behaviour. In `main.cpp`, valgrind reports `Invalid read of size 8`. The loop also stops after the first node, so valgrind reports leaks for the other nodes and departments.
- **Call `temp->getData()` after `delete temp`.** The node is gone, so the call reads freed memory. This is undefined behaviour. In `main.cpp`, valgrind reports `Invalid read of size 8`. Delete the department first, then the node.
- **Forget `headNode = NULL;` and `size = 0;`.** After `clear()`, `headNode` points at freed nodes. The call `clear()` in `~List()` then deletes the nodes and the departments a second time. Valgrind reports `Invalid read` and `Invalid free() / delete / delete[] / realloc()` errors. The size also stays wrong: the output shows `Spare departments after clear: 2` instead of `0`.
- **Write `template <class T>` or use `Node<T>*`.** With `template <class T>`, the compiler reports `error: no declaration matches 'void List<Department*>::clear()'`. With `Node<T>*` after `template <>`, it reports `error: 'T' was not declared in this scope`, because `T` is not defined in a full specialization. In both cases the code does not compile. The function must use `Node<Department*>*`.
