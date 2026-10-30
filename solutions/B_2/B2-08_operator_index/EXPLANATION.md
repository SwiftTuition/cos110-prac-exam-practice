# B2-08 Explanation: List::operator[]

## What the function must do

The function `operator[]` lets the caller write `list[index]` to read the value at position `index`. Position 0 is the head. If `index` is negative, or equal to or larger than the number of nodes, the function throws an `Exception` with the message `Index out of bounds`. Otherwise, the function returns a reference to the value that is stored inside the node. The function does not change the list.

## How the solution works

A pointer is a variable that holds the address of an object. The operator `->` uses a pointer to reach a member. `NULL` means the pointer points to nothing. `T` is the template type. A reference is another name for an existing object. A return type of `const T&` returns the stored object itself, not a copy, and the caller cannot change it through the reference.

The function starts here:

```cpp
template <class T>
const T& List<T>::operator[](int index) {
```

Calling `list[2]` runs `list.operator[](2)`. The function takes the index as an `int`.

The range check:

```cpp
    if (index < 0 || index >= size) {
        throw Exception("Index out of bounds");
    }
```

- `index < 0` rejects negative positions. No node has a negative position.
- `index >= size` rejects positions at or past the end. The valid positions are 0 to `size - 1`.
- The operator `||` is true if either test is true.
- An empty list has `size` 0, so every index fails `index >= size`. The function throws and the code below never reads `headNode`, which is `NULL`.
- `throw Exception("Index out of bounds");` creates an `Exception` object and throws it by value. The function stops at this line. No value is returned.
- The check comes before any `new`. The function allocates nothing, so a throw cannot leak memory.
- The caller must catch the exception. The given `tryIndex` function uses `catch (Exception& e)` and prints `e.what()`, which returns the message. An uncaught exception ends the program, and the mark is 0.

The walk to the node:

```cpp
    Node<T>* curr = headNode;
    for (int i = 0; i < index; i++) {
        curr = curr->next();
    }
```

- `curr` starts at the head, which is position 0.
- The condition `i < index` makes the loop run `index` times. Each pass moves `curr` one node forward with `curr->next()`.
- For `index` equal to 0, the loop body does not run, and `curr` stays at the head.
- The loop does not test `curr` for `NULL`. The range check guarantees that position `index` exists, so each step stays inside the list.

The return line:

```cpp
    return curr->getData();
```

- `getData()` returns a `const T&` to the value that the node owns.
- The function returns that same reference. The reference stays valid as long as the node exists.
- The function must not copy the value into a local variable and return that variable. A local variable is destroyed when the function ends, so the reference would point to a variable that no longer exists. g++ warns about this, and `-Werror` makes the warning an error.

Memory: the function allocates nothing and frees nothing. The list is unchanged, so valgrind shows no leak.

## Trace

Call from `main.cpp`: `tryIndex(numbers, 2);`, which runs `list[index]`. The list is `10->20->30` and `size` is 3.

| Step | `i` | `curr` points to | Action |
|---|---|---|---|
| Range check | | | `2 < 0` is false and `2 >= 3` is false. No throw. |
| Setup | | node 10 | `curr = headNode`. |
| Loop test | 0 | node 10 | `0 < 2` is true. `curr` moves to node 20. |
| Loop test | 1 | node 20 | `1 < 2` is true. `curr` moves to node 30. |
| Loop test | 2 | node 30 | `2 < 2` is false. The loop ends. |
| Return | | node 30 | The function returns the reference to 30. |

The function `tryIndex` copies the value into `T value` and prints it. For `tryIndex(numbers, 3)`, the test `3 >= 3` is true. The function throws, `catch` runs, and the program prints the message.

The program output is:

```text
10->20->30
list[0]: 10
list[2]: 30
list[1]: 20
list[3]: Caught: Index out of bounds
list[-1]: Caught: Index out of bounds
```

## Common mistakes

- Writing `index > size` in the range check. The value `index == size` then passes. The walk ends with `curr` equal to `NULL`, and `curr->getData()` reads through `NULL`. The main test calls `list[3]` on a three-node list: valgrind reports "Invalid read of size 8" and the program stops with a segmentation fault (SIGSEGV).
- Leaving out `index < 0`. A negative index does not throw. The loop does not run, and the function returns the head value. In the main test, `list[-1]` prints `10` and not `Caught: Index out of bounds`. On an empty list, `curr` would be `NULL`, so `curr->getData()` would read through `NULL`.
- Returning a value such as -1 or a default value instead of throwing. The expected output shows `Caught: Index out of bounds`, so the output is wrong. For example, a function that returns a default `T()` prints `list[3]: 0` in the main test.
- Throwing a different type, such as `throw "Index out of bounds";`. The `catch (Exception& e)` does not match, so the exception is not caught. The program prints "terminate called after throwing an instance of 'char const*'" and stops with SIGABRT at `list[3]`. The mark is 0.
- Returning a copy, for example `T value = curr->getData(); return value;`. The return type is `const T&`, so the function returns a reference to a local variable that no longer exists. The code does not compile: g++ reports "reference to local variable 'value' returned [-Werror=return-local-addr]". The mark is 0.
