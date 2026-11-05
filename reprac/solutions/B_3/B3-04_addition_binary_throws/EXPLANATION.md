# B3-04 Explanation: addition<Binary, Binary> throws

## What the function must do

The general template `addition<T, U>(v1, v2)` returns `v1 + v2` as a `T`. Two binary strings must not be added. The specialisation for two `Binary` objects must throw the C-string `"Cannot add two binary strings"` and print nothing. This is the exact pattern of Lecture 19, where `addition<char, char>` throws `"Cannot add two chars"`.

## How the solution works

```cpp
template <>
Binary addition<Binary, Binary>(Binary v1, Binary v2) {
```

- `template <>` marks a specialisation.
- The general template has **two** type parameters, `T` and `U`. So the specialisation names both: `addition<Binary, Binary>`. That sets `T = Binary` and `U = Binary`.
- The general return type is `T`, so here it is `Binary`. The general parameters are `T v1, U v2` by value, so here they are `Binary v1, Binary v2`. The definition must match the declaration in `Templates.h` exactly.
- By value means the call copies both arguments with the `Binary` copy constructor.

```cpp
    throw "Cannot add two binary strings";
}
```

- `throw` stops the function at once and sends the value to the nearest matching `catch`.
- A string literal is thrown as a `const char*`. `main.cpp` catches it with `catch (const char* msg)`, which matches.
- The function has no `return`. It always throws, so the end of the function is never reached, and g++ does not report a missing return value.
- When the function leaves through `throw`, C++ destroys the parameters `v1` and `v2`, and their destructors free their arrays. So nothing leaks, even in a loop.
- The parameters are not used. `-Wall` does not warn about unused parameters (that warning is in `-Wextra`), so the build is clean.

## Where the code lives, and why

`Templates.h` holds the general template and, after it, the declaration `template <> Binary addition<Binary, Binary>(Binary v1, Binary v2);`. `B_3.cpp` holds the one definition. Lecture 19 says specialisations must be "placed after the general template function". The declaration also comes before any call, so `main.cpp` uses the specialisation. A full specialisation is an ordinary function, so it is defined once, in the `.cpp` file.

## Trace

| Call in `main.cpp` | Version | Result |
|---|---|---|
| `addition(3, 4.5)` | general, `T = int`, `U = double` | `3 + 4.5` is 7.5, converted to `int`: `7` |
| `addition(2.5, 3)` | general, `T = double`, `U = int` | `5.5` |
| `addition(string("10"), string("01"))` | general, `T = U = string` | joins the strings: `1001` |
| `addition(a, b)` with two `Binary` | specialisation | throws |

The steps of the last call:

| Step | Event |
|---|---|
| 1 | `main` enters the `try` block. |
| 2 | `addition(a, b)` copies `a` and `b` into `v1` and `v2`. |
| 3 | `throw "Cannot add two binary strings";` runs. |
| 4 | The function ends. C++ destroys `v1` and `v2`, which frees their arrays. |
| 5 | `Binary sum = ...` does not finish, so `sum` is never created. `cout << sum` does not run. |
| 6 | `catch (const char* msg)` matches. It prints `Caught: Cannot add two binary strings`. |
| 7 | The program continues after the `catch`. `a` and `b` were never changed. |

The output of `main.cpp` is:

```text
7
5.5
1001
Caught: Cannot add two binary strings
a and b are unchanged: 0101 0011
```

## Common mistakes

- **Throwing a `std::string`** (`throw string("...")`). `catch (const char* msg)` does not match a `std::string`. The exception is uncaught: the program prints `terminate called after throwing an instance of 'std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >'` and stops with `Aborted` (exit code 134). The mark is 0.
- **Returning a value instead of throwing**, such as `return v1;`. No exception happens. `main.cpp` prints `0101` instead of the `Caught:` line.
- **Printing the message instead of throwing.** The function then reaches its end without a return value. g++ reports `no return statement in function returning non-void [-Werror=return-type]`, and the build fails.
- **Naming one type only**, as in `addition<Binary>(Binary v1, Binary v2)`. This also compiles, because the compiler deduces `U` from the second parameter. Write both types, as in the given declaration, so that the definition matches the header line by line.
- **Throwing with `new`**, as in `throw new string(...)`. The type is a pointer, which `catch (const char*)` does not match, and the object leaks.
