# B1-06 Explanation: recursive BinaryStrings::printReverse

## What the function must do

`printReverse(curr)` prints the strings of the list in reverse order: from the last node back to `curr`, one string per line, with `cout` and `endl`. A list has only forward links (`next()`), so the function cannot walk backward. If `curr` is `NULL`, it prints nothing. It must not change the list.

## How the solution works

```cpp
void BinaryStrings::printReverse(Node<Binary>* curr) {
    if (curr == NULL) {
        return;
    }
```

This is the base case. `NULL` comes after the last node. It is also the head of an empty list. There is nothing to print, so the function returns. The function returns `void`, so `return;` has no value.

```cpp
    printReverse(curr->next());
    cout << curr->getData() << endl;
}
```

This is the recursive case. The order of the two lines is what reverses the output.

- First the function calls itself for the rest of the list, starting at `curr->next()`. That call prints every later node, from the last one back.
- Only after that call returns does the function print its own string. `curr->getData()` is the `Binary` in this node, and the given `operator<<` prints its bits.
- `curr->next()` moves one node forward, toward `NULL`, so the recursion ends.
- The function changes no pointer, so the list stays the same.

This is the recursive answer to the lecture's `printInReverse`, which uses two nested loops. The call stack remembers the nodes on the way down, and the prints happen on the way back up.

## Trace

In `main.cpp`, the list is `000 -> 0011 -> 1101 -> 0101`. The call is `printReverse(list.getHead())`.

| Call | curr | `curr == NULL`? | Branch | Prints after the next call returns |
|---|---|---|---|---|
| 1 | `000` | false | recursive, calls call 2 first | `000` |
| 2 | `0011` | false | recursive, calls call 3 first | `0011` |
| 3 | `1101` | false | recursive, calls call 4 first | `1101` |
| 4 | `0101` | false | recursive, calls call 5 first | `0101` |
| 5 | `NULL` | true | base case, returns | nothing (it makes no call) |

The calls return in the order 5, 4, 3, 2, 1. After each return, the caller runs its print line:

- Call 4 prints `0101`.
- Call 3 prints `1101`.
- Call 2 prints `0011`.
- Call 1 prints `000`.

`printReverse(list.getHead()->next())` starts at call 2 and prints `0101`, `1101` and `0011`. The empty list's head is `NULL`, so that call prints nothing.

The output of `main.cpp` is:

```text
000 -> 0011 -> 1101 -> 0101
Reverse:
0101
1101
0011
000
Reverse from the second node:
0101
1101
0011
Reverse of an empty list:
(end)
```

## Common mistakes

- **Printing before the recursive call.** The strings then appear in forward order: `000`, `0011`, `1101`, `0101`. The output is wrong.
- **Calling `printReverse(curr)` instead of `printReverse(curr->next())`.** The argument never changes, so the recursion never ends. The program compiles, but valgrind reports a stack overflow and the program stops with `SIGSEGV`. Nothing after `Reverse:` is printed, and the mark is 0.
- **No `NULL` test.** Every call makes another call. g++ may warn `infinite recursion detected`. Under `-Werror` the build fails, and the mark is 0.
- **Printing without `endl`, or with a separator.** The strings then run together on one line, for example `010111010011000`. Each string must be on its own line.
- **Printing the bits one by one in reverse.** The question reverses the order of the strings, not the bits inside a string. `0011` stays `0011`.
- **A loop or a helper function.** Either one scores 0.
