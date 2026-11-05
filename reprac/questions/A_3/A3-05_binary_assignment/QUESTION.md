Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A3-05. Assignment operator: `Binary::operator=` (a `bool*` array) (100)

`Binary` is from Section B of the scenario. Its `operator=` is not in the published UML; this question practises the four steps of `operator=` on a plain array. Implement the assignment operator of the `Binary` class in `A_3.cpp`.

```text
Binary
- array: bool*
- size: int
+ Binary(string)
+ Binary(const Binary&)
+ ~Binary()
+ operator=(const Binary&): Binary&     <- implement
+ operator[](int): bool&
+ operator[](int): const bool&
+ getSize(): int
```

## What the function must do

- `array` holds `size` bools. `Binary("1101")` makes `true, true, false, true`.
- After `a = b;`, `a` has the same `size` as `b` and its own new array with the same bits.
- `a`'s old array must be freed.
- Changing `b` afterwards (for example `b[0] = false;`) must not change `a`.
- `a = a;` must leave `a` unchanged. `a = b = c;` must work.
- `operator<<` prints the bits as `0` and `1` characters.

## Rules

- Write only this one function in `A_3.cpp`. Do not change the other files: they are replaced when marked.
- The program must compile with `-Wall -Werror`, print exactly the output at the end of `main.cpp`, and have no memory errors or leaks under valgrind.

## Build and upload

In the `A_3` folder, run `make A_3`. Upload only `A_3.cpp`.
