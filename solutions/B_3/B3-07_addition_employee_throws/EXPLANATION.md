# B3-07 Explanation: addition<Employee, Employee>

## What the function must do

The general template `addition` returns `v1 + v2`. Two `Employee` objects cannot be added, because the class has no `+` operator. The specialization for two employees must not add anything. The function must throw an `Exception` with the message `Cannot add two employees`, and it must not print anything.

## How the solution works

A **function template** is a recipe for functions. In `template <class T, class U> T addition(T v1, U v2)`, the names `T` and `U` are template parameters: placeholders for two types. The function returns a value of type `T`. For `addition(3, 4.5)`, the compiler sets `T` to `int` and `U` to `double`, and builds a version for those types.

A **specialization** is a version of the template that you write for exact types. When the program calls `addition` with two `Employee` objects, the compiler uses the specialization and not the general template.

```cpp
template <>
Employee addition<Employee, Employee>(Employee v1, Employee v2) {
```

The line `template <>` tells the compiler that this function is a specialization. The text `<Employee, Employee>` after the function name gives the types for `T` and `U`. The parameters `v1` and `v2` are passed by value, so C++ makes a copy of each argument with the `Employee` copy constructor. The definition must match the declaration in `Templates.h` exactly: the same return type, the same name and the same parameter types. The declaration appears after the general template and before any call, so `main.cpp` calls this specialization.

```cpp
    throw Exception("Cannot add two employees");
}
```

The keyword `throw` stops the function and sends an exception to the calling code. The expression `Exception("Cannot add two employees")` creates an `Exception` object that holds the message. The function throws the object by value. It does not throw a pointer and does not throw a C-string.

The function has no `return` statement. The function ends with `throw`, so the code after it never runs, and the compiler does not report a missing return value. The return type `Employee` is still required, because the declaration says so.

The calling code uses a `try` block and a `catch` block. A `catch` block with the parameter `Exception& e` catches an `Exception` thrown by value. The `&` means that `e` is a reference to the thrown object and not a copy. The function `what()` returns the message. A catch of another type, such as `catch (char*)`, does not match an `Exception` object.

The function does not use `new`, so it allocates nothing and frees nothing. When the function leaves through `throw`, C++ destroys the copies `v1` and `v2` by itself, so no memory is lost. The caller's heap objects are not affected, and the caller can still delete them.

The function prints nothing. The `catch` block in the calling code prints the message.

## Trace

The calls come from `main.cpp`. The first three calls use the general template. The call with two employees uses the specialization.

| Call | Template used | Computation | Result |
|---|---|---|---|
| `addition(3, 4.5)` | general, `T` is `int`, `U` is `double` | `3 + 4.5` is `7.5`, and the function converts it to `int` | `7` |
| `addition(2.5, 3)` | general, `T` is `double`, `U` is `int` | `2.5 + 3` | `5.5` |
| `addition(string("Human "), string("Resources"))` | general, `T` and `U` are `string` | joins the two strings | `Human Resources` |
| `addition(thandi, sipho)` | specialization | throws | see the steps below |

The steps of the last call:

| Step | Event |
|---|---|
| 1 | `main` enters the `try` block. |
| 2 | The call `addition(thandi, sipho)` copies `thandi` and `sipho` into `v1` and `v2`. |
| 3 | The function runs `throw Exception("Cannot add two employees");`. |
| 4 | The function ends at once. C++ destroys `v1` and `v2`. No value is returned. |
| 5 | The statement `Employee both = ...` does not finish, so `both` is not created. The line `cout << both << endl;` does not run. |
| 6 | The `catch (Exception& e)` block matches the thrown type. `e.what()` gives `Cannot add two employees`. |
| 7 | The block prints `Caught: Cannot add two employees`. |
| 8 | The program continues after the `catch` block and prints `Program continues`. |

The output of `main.cpp` is:

```text
7
5.5
Human Resources
Caught: Cannot add two employees
Program continues
```

## Common mistakes

- **Throw a pointer, as in `throw new Exception("...")`.** The type of the thrown value is `Exception*`. The block `catch (Exception& e)` does not match it, so the exception is uncaught. The program prints `terminate called after throwing an instance of 'Exception*'` and stops with signal 6 (SIGABRT). The lines `Caught: ...` and `Program continues` are never printed, and the mark is 0.
- **Throw a C-string, as in `throw "Cannot add two employees";`.** The lecture example for `char` throws a C-string, but here `main.cpp` catches `Exception&`. The type does not match, so the exception is uncaught. The program prints `terminate called after throwing an instance of 'char const*'` and stops with signal 6 (SIGABRT). The mark is 0.
- **Print the message instead of throwing.** The function then reaches its end without a return value. With `-Wall -Werror`, the compiler reports `error: no return statement in function returning non-void [-Werror=return-type]`, and the program does not compile.
- **Return one of the employees, as in `return v1;`.** No exception is thrown. In `main.cpp`, the program prints `Thandi Mokoena, 29, F, ID: none` instead of `Caught: Cannot add two employees`, and the output differs. The edge test prints `No exception` and `Caught 0 times` for this case.
- **Use a different message.** The text must be exactly `Cannot add two employees`. A different text changes the line that `what()` gives, and the output differs.
