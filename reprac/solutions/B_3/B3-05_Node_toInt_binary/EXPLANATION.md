# B3-05 Explanation: Node<Binary>::toInt() (member specialisation)

## What the function must do

`Node<T>` has a member function `int toInt()`. The general version in `Node.cpp` returns `(int)data`, which works for `int`, `double`, `bool` and `char`. A `Binary` cannot be cast to `int`, so the general version cannot be built for `Node<Binary>`. The specialisation must return the decimal value of the stored binary string, with `data[0]` as the most significant bit.

## What is different about this question

B3-01 to B3-04 specialise a **function template**. This question specialises **one member function of a class template**. Only `toInt()` changes. The constructor, `getData()` and `next()` still come from the general template.

The name of the function shows the difference:

| Kind | General | Specialisation |
|---|---|---|
| function template | `void printValue(const T& value)` | `void printValue<Binary>(const Binary& value)` |
| member of a class template | `int Node<T>::toInt()` | `int Node<Binary>::toInt()` |

In a member specialisation the type goes after the **class** name, `Node<Binary>`, because `toInt()` itself is not a template. Only the class has a type parameter.

## How the solution works

```cpp
#include "Node.h"

template <>
int Node<Binary>::toInt() {
```

- `#include "Node.h"` brings in the class, the general `toInt()` (through `Node.cpp`) and the declaration of the specialisation.
- `template <>` marks a specialisation, with no type left open.
- `int Node<Binary>::toInt()` says: this is the `toInt()` member of the class `Node<Binary>`. It must match the declaration at the bottom of `Node.h` exactly.

```cpp
    int value = 0;
    for (int i = 0; i < data.getSize(); i++) {
        value = value * 2;
        if (data[i]) {
            value = value + 1;
        }
    }
    return value;
}
```

- Inside a member function, `data` is the node's own member. In `Node<Binary>` it is a `Binary` object (not a pointer), so `data.getSize()` and `data[i]` use a dot and square brackets directly.
- The loop reads from index 0, the most significant bit. Each bit doubles the value so far and adds 1 if the bit is 1.
- For an empty string the loop does not run, and the result is 0.
- The function allocates nothing, so there is nothing to free.

## Where the code lives, and why

| File | Holds | Why |
|---|---|---|
| `Node.h` | `#include "Binary.h"` at the top | `data` is a `T`, not a `T*`. To declare anything about `Node<Binary>`, the compiler must know the full `Binary` class. |
| `Node.h` | the class, then `#include "Node.cpp"`, then the declaration `template <> int Node<Binary>::toInt();` | The declaration must come after the general member function and before any use. Placing it at the bottom of `Node.h` puts it after `Node.cpp` and in front of every file that includes `Node.h`. |
| `Node.cpp` | the general `toInt()` (`return (int)data;`) | It is a template, so it is included by the header, not compiled on its own. |
| `B_3.cpp` | the definition of `Node<Binary>::toInt()` | A full specialisation is an ordinary function, not a template. It needs exactly one definition, in a file that is compiled once. `B_3.cpp` is on the `g++` line. `Node.cpp` is not compiled on its own: `Node.h` includes it. A body placed at the end of `Node.cpp` does not link: g++ reports `undefined reference to 'Node<Binary>::toInt()'`. |

Without the declaration in `Node.h`, `main.cpp` would try to build `Node<Binary>::toInt()` from the general version, and `(int)data` does not compile for a `Binary`.

## Trace

| Call in `main.cpp` | Version | Steps | Result |
|---|---|---|---|
| `Node<int>` with 7 | general | `(int)7` | 7 |
| `Node<double>` with 3.9 | general | `(int)3.9` drops the fraction | 3 |
| `Node<bool>` with `true` | general | `(int)true` | 1 |
| `Node<Binary>` with `1010` | specialisation | 1, 2, 5, 10 | 10 |

`main.cpp` then builds the list `000 -> 0011 -> 1101 -> 0101` (each `prepend` puts the new string at the front) and walks it with `curr`:

| Node | Loop: value after each bit | `toInt()` |
|---|---|---|
| `000` | 0, 0, 0 | 0 |
| `0011` | 0, 0, 1, 3 | 3 |
| `1101` | 1, 3, 6, 13 | 13 |
| `0101` | 0, 1, 2, 5 | 5 |

`curr->toInt()` uses the arrow because `curr` is a pointer to a `Node<Binary>`. The type of `*curr` is `Node<Binary>`, so the call goes to the specialisation.

The output of `main.cpp` is:

```text
Node<int> 7: 7
Node<double> 3.9: 3
Node<bool> true: 1
Node<Binary> 1010: 10
000 -> 0011 -> 1101 -> 0101
000 -> 0
0011 -> 3
1101 -> 13
0101 -> 5
```

## Common mistakes

- **`template <class T>` instead of `template <>`.** g++ reports `no declaration matches 'int Node<Binary>::toInt()'`. The build fails, and the mark is 0.
- **Putting the type after the function name**, as in `int Node::toInt<Binary>()`. `toInt` is not a template, and `Node` needs its type. g++ reports `'template<class T> class Node' used without template arguments`.
- **Counting the 1 bits instead of working out the value.** `1010` then gives 2, and `1101` gives 3.
- **Writing the body of the specialisation in `Node.h` without `inline`.** `main.cpp`, `BinaryStrings.cpp` and `B_3.cpp` all include `Node.h`, so each gets a copy, and the linker reports `multiple definition of 'Node<Binary>::toInt()'`. A body at the end of `Node.cpp` fails in a different way: the link reports `undefined reference to 'Node<Binary>::toInt()'`.
- **Writing `data->getSize()`.** `data` is a `Binary`, not a pointer, so this does not compile.
- **Removing `#include "Binary.h"` from `Node.h`.** The declaration of `Node<Binary>::toInt()` needs the full `Binary` class, so the build fails with `'Binary' was not declared in this scope`.
