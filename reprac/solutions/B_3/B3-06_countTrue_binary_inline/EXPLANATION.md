# B3-06 Explanation: countTrue<Binary> (inline, in a header-included file)

## What the function must do

The general template `countTrue<T>(head)` walks a list of `Node<T>` from `head` to the end and counts the nodes whose data is true (for numbers: not 0). For a list of `Binary` strings, "true" has a different meaning. The specialisation must count every true bit in every string, from `head` to the end. A `NULL` head gives 0.

## What is different about this question

In this question `Templates.h` ends with `#include "B_3.cpp"`, the way a template class header includes its `.cpp` file. `B_3.cpp` is also on the `g++` line. So the definition in `B_3.cpp` is compiled twice: once inside `main.cpp` (through `Templates.h`) and once as `B_3.cpp` itself.

A full specialisation is an ordinary function. An ordinary function may be defined only once in the program, unless it is `inline`. `inline` tells the linker that identical copies in different files are the same function, so it keeps one. That is why the definition must start with `template <> inline`.

## How the solution works

```cpp
#ifndef B_3_CPP
#define B_3_CPP

#include "Templates.h"
```

The include guard is given in the starter file. When `B_3.cpp` is compiled on its own, the compiler reads the files in this order:

1. The compiler starts `B_3.cpp`. `B_3_CPP` is not defined, so `#ifndef B_3_CPP` is true, and the next line defines `B_3_CPP`.
2. `#include "Templates.h"` brings in the general template, the declaration of the specialisation, and `#include "B_3.cpp"`.
3. `B_3.cpp` is read a second time. `B_3_CPP` is now defined, so `#ifndef B_3_CPP` is false, and everything up to `#endif` is skipped.
4. The compiler returns to the first `B_3.cpp`, after `#include "Templates.h"`, and reads the definition once.

For `main.cpp`, `B_3_CPP` is not defined when `Templates.h` reaches `#include "B_3.cpp"`. So the guard does not skip the file, and the definition is read inside `main.cpp`. That is the second copy, and it is why `inline` is needed.

The general template and the declaration of the specialisation come from `Templates.h`, so the definition comes after both.

```cpp
template <>
inline int countTrue<Binary>(Node<Binary>* head) {
```

- `template <>` marks a specialisation, and `countTrue<Binary>` sets `T` to `Binary`.
- `inline` goes after `template <>` and before the return type.
- The general parameter is `Node<T>* head`, so here it is `Node<Binary>* head`.

```cpp
    int count = 0;
    Node<Binary>* curr = head;
    while (curr != NULL) {
```

- `curr` starts at `head`. The loop runs while `curr` points to a node. If `head` is `NULL`, the loop does not run, and the result is 0.

```cpp
        Binary& b = curr->getData();
        for (int i = 0; i < b.getSize(); i++) {
            if (b[i]) {
                count++;
            }
        }
```

- `getData()` returns a `T&`, so `b` is another name for the node's own `Binary`. No copy is made.
- The inner loop visits every bit of this string and adds 1 for each true bit. An empty string has size 0, so the inner loop does not run.

```cpp
        curr = curr->next();
    }
    return count;
}

#endif
```

- `curr` moves to the next node. After the last node, `next()` returns `NULL`, and the outer loop stops.
- The function does not change or free any node. The list still owns its nodes.

## Where the code lives, and why

| File | Holds | Why |
|---|---|---|
| `Templates.h` | the general template, then the declaration `template <> int countTrue<Binary>(Node<Binary>* head);`, then `#include "B_3.cpp"` | The declaration comes after the general template and before any call. |
| `B_3.cpp` | the guarded, `inline` definition | It is included by `Templates.h` and compiled on its own, so it ends up in two object files. `inline` allows that. |

The declaration in `Templates.h` has no `inline`. g++ accepts a later `inline` definition after a declaration without it, and the solution builds cleanly with `-Wall -Werror`.

## Trace

**The `Node<int>` list `0 -> 3 -> 0 -> -2`** uses the general template (`T = int`):

| Node | `if (curr->getData())` | count |
|---|---|---|
| 0 | false | 0 |
| 3 | true | 1 |
| 0 | false | 1 |
| -2 | true (not 0) | 2 |

**The empty list.** `list.getHead()` is `NULL`. The outer loop does not run. Result 0.

**The list `000 -> 0011 -> 1101 -> 0101`** uses the specialisation:

| Node | true bits in this string | count after |
|---|---|---|
| `000` | 0 | 0 |
| `0011` | 2 | 2 |
| `1101` | 3 | 5 |
| `0101` | 2 | 7 |

The inner loop for `1101` (the third node), with `count` at 2 before it:

| i | `b[i]` | `if (b[i])` | count after |
|---|---|---|---|
| 0 | 1 | true | 3 |
| 1 | 1 | true | 4 |
| 2 | 0 | false | 4 |
| 3 | 1 | true | 5 |

At `i` = 4, `4 < 4` is false, so the inner loop ends, and `curr` moves to `0101`.

**From the third node**, `list.getHead()->next()->next()` points to `1101`. The loop counts `1101` (3) and `0101` (2), so the result is 5.

The output of `main.cpp` is:

```text
Node<int> chain 0 3 0 -2: 2 not zero
Empty: 0 true bits
000 -> 0011 -> 1101 -> 0101: 7 true bits
from the third node: 5 true bits
```

## Common mistakes

- **No `inline`.** The build compiles, then the link fails: `multiple definition of 'int countTrue<Binary>(Node<Binary>*)'; ... B_3.cpp:10: first defined here`, followed by `collect2: error: ld returned 1 exit status`. The mark is 0.
- **Deleting the include guard from `B_3.cpp`.** When `B_3.cpp` is compiled, it includes `Templates.h`, which includes `B_3.cpp` again, so the definition appears twice in one file. g++ reports `redefinition of 'int countTrue(Node<T>*) [with T = Binary]'`.
- **Counting the strings that have a true bit**, with a `break` after the first one. The full list then gives 3 instead of 7.
- **`inline` in the wrong place**, as in `inline template <> int countTrue<Binary>(...)`. `template <>` must come first; g++ reports `expected unqualified-id before '<' token`.
- **Copying the data**, as in `Binary b = curr->getData();`. This works, because `Binary` has a deep copy constructor, but it allocates and frees an array for every node. The reference `Binary&` avoids that.
- **Deleting the nodes while counting.** The list still owns them, so its destructor frees them again. valgrind reports `Invalid free() / delete / delete[]`.
