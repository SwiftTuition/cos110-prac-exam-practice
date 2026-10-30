# B3-01 Explanation: printItem<Department*>

## What the function must do

The general template `printItem` prints a value with `cout << item << endl;`. For a `Department*`, that statement prints an address. The specialization is a special version of the template for the type `Department*`. It prints the department that the pointer points to. If the pointer is `NULL`, it prints `No department`.

## How the solution works

A **function template** is a recipe for functions. In `template <class T> void printItem(const T& item)`, the name `T` is a template parameter: a placeholder for a type. When the program calls `printItem(42)`, the compiler sets `T` to `int` and builds a version for `int`.

A **specialization** is a version of the template for one exact type. When the program calls `printItem` with a `Department*`, the compiler uses the specialization. For all other types, it uses the general template.

```cpp
template <>
void printItem<Department*>(Department* const& item) {
```

The line `template <>` tells the compiler that the function is a specialization and that no type placeholder remains. The text `<Department*>` after the function name gives the concrete type for `T`.

The parameter type comes from `const T&` with `T` equal to `Department*`. A `const` that is written after the star applies to the pointer. The result is `Department* const&`: a reference to a pointer that cannot change. The type is not `const Department*&`. The definition must match the declaration in `Templates.h` exactly. A different parameter type does not match any template declaration, and the compiler reports an error.

The declaration in `Templates.h` comes after the general template and before any call. For this reason, `main.cpp` calls the specialization and not the general template. `B_3.cpp` holds the definition.

```cpp
    if (item == NULL) {
        cout << "No department" << endl;
        return;
    }
```

`item` is a pointer. The condition `item == NULL` checks whether the pointer points at no object. A `NULL` pointer has no department to print. The next line would use `*item`. Using `*item` on a `NULL` pointer is undefined behaviour: the C++ rules do not say what happens. In this program, it stops with a segmentation fault. This check must come before the print line. If the condition is true, the function prints `No department` with a newline and leaves the function with `return`. The `return` prevents the function from reaching the print line below.

```cpp
    cout << *item;    // Department's operator<< already ends its lines
}
```

`*item` is the department that the pointer points to. The operator `<<` is **overloaded** for `Department`: the class defines its own version of `<<`. This version prints `<name> (cost R<cost>)` and a newline, and then each team. The functions `getName()` and `costToCompany()` are virtual, so a `Sales` object prints `Sales`, even though the pointer type is `Department*`.

The function does not add `endl`. The `Department` operator already ends every line, so an extra `endl` would print a blank line.

The function allocates and frees no memory. The caller owns the department and deletes it.

## Trace

The calls come from `main.cpp`. The first three calls use the general template. The last two calls use the specialization.

| Call | Type `T` | Template used | Check `item == NULL` | Printed |
|---|---|---|---|---|
| `printItem(42)` | `int` | general | not applicable | `42` |
| `printItem(3.5)` | `double` | general | not applicable | `3.5` |
| `printItem(string("Yyra HRMS"))` | `string` | general | not applicable | `Yyra HRMS` |
| `printItem(sales)` | `Department*` | specialization | false, because `sales` points at a `Sales` object | the department, with its team |
| `printItem(none)` | `Department*` | specialization | true, because `none` is `NULL` | `No department` |

In the fourth call, `cout << *item;` calls the `Department` operator. `getName()` gives `Sales`, and `costToCompany()` gives 1 employee times 15000. Then the team operator prints `Team:` and one line for each employee.

The output of `main.cpp` is:

```text
42
3.5
Yyra HRMS
Sales (cost R15000)
Team:
  Thandi Mokoena, 29, F, ID: none
No department
```

## Common mistakes

- **Write `const Department*& item`.** The parameter type does not match the declaration in `Templates.h`. The compiler reports that the template-id does not match any template declaration, and the mark is 0.
- **Omit the `NULL` check.** The call `printItem(none)` then runs `*item` on a `NULL` pointer. This is undefined behaviour. In this program, valgrind reports `Invalid read of size 8`, and the program stops with a segmentation fault (signal 11) before it prints `No department`. The edge test also passes a `NULL` entry from an array.
- **Print the pointer, as in `cout << item << endl;`.** The program prints an address, and the output differs from the expected output.
- **Add `endl` after `cout << *item;`.** The `Department` operator already ends every line. The extra `endl` prints a blank line, and the output differs from the expected output.
- **Write the first line by hand with a fixed name.** For example, `cout << "Department (cost R" << item->costToCompany() << ")" << endl;`. In `main.cpp`, this prints `Department (cost R15000)` and not `Sales (cost R15000)`, and the team lines are missing, so the output differs from the expected output. Use `cout << *item;`. The `Department` operator calls the virtual functions, which choose the name and the cost, and it also prints the teams. The edge test prints `HR`, `Department` and `Development` objects through the same function.
