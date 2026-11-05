# B3-02 Explanation: largest<Binary>

## What the function must do

The general template `largest<T>(a, b)` returns `b` if `b > a`, otherwise `a`. `Binary` has no `>` operator, so the general version cannot be built for it. The specialisation compares the two strings by decimal value and returns the larger one, or `a` when the values are equal.

## How the solution works

```cpp
template <>
Binary largest<Binary>(Binary a, Binary b) {
```

- `template <>` marks a specialisation. `largest<Binary>` sets `T` to `Binary`.
- The general template takes `T a, T b` **by value** and returns `T`. So the specialisation takes `Binary a, Binary b` by value and returns a `Binary`. It must match the declaration in `Templates.h` exactly.
- By value means each call copies the two arguments with the `Binary` copy constructor. The copy constructor is deep, so `a` and `b` have their own arrays, and the caller's objects cannot change.

```cpp
    int valueA = 0;
    for (int i = 0; i < a.getSize(); i++) {
        valueA = valueA * 2;
        if (a[i]) {
            valueA = valueA + 1;
        }
    }
```

This loop works out the decimal value of `a`, reading from the leftmost (most significant) bit. Each bit doubles the value so far and adds 1 if the bit is 1. The same loop with `b` gives `valueB`.

```cpp
    if (valueB > valueA) {
        return b;
    }
    return a;
}
```

- The test has the same shape as the general template: `b` only wins if it is strictly larger. When the values are equal, the function returns `a`, as the question requires.
- `return b;` returns a copy of `b` (copy constructor). When the function ends, the parameters `a` and `b` are destroyed and free their arrays. The returned copy has its own array, so nothing is freed twice and nothing leaks.

## Where the code lives, and why

`Templates.h` holds the general template and, after it, the declaration `template <> Binary largest<Binary>(Binary a, Binary b);`. `B_3.cpp` holds the one definition. A full specialisation is an ordinary function, so it must be defined once in the program. The declaration in the header makes every file that calls `largest` with two `Binary` objects use the specialisation, and it comes after the general template, as Lecture 19 requires.

## Trace

| Call in `main.cpp` | Version | Values | Result |
|---|---|---|---|
| `largest(3, 7)` | general, `T = int` | `7 > 3` | `7` |
| `largest(2.5, 1.5)` | general, `T = double` | `1.5 > 2.5` false | `2.5` |
| `largest(string("apple"), string("pear"))` | general, `T = string` | `"pear" > "apple"` (alphabetical) | `pear` |
| `largest(x, y)`, `0111` and `1000` | specialisation | 7 and 8, `8 > 7` | `1000` |
| `largest(Binary("11"), Binary("0001"))` | specialisation | 3 and 1, `1 > 3` false | `11` |
| `largest(Binary("011"), Binary("11"))` | specialisation | 3 and 3, `3 > 3` false | `011` (a) |

The value loops for `largest(x, y)`, with `a` = `0111` and `b` = `1000`. The two loops run one after the other; the table puts them side by side.

| i | `a[i]` | `valueA` after | `b[i]` | `valueB` after |
|---|---|---|---|---|
| 0 | 0 | 0 × 2 = 0 | 1 | 0 × 2 + 1 = 1 |
| 1 | 1 | 0 × 2 + 1 = 1 | 0 | 1 × 2 = 2 |
| 2 | 1 | 1 × 2 + 1 = 3 | 0 | 2 × 2 = 4 |
| 3 | 1 | 3 × 2 + 1 = 7 | 0 | 4 × 2 = 8 |

At `i` = 4, `4 < 4` is false, so each loop ends. Then `valueB > valueA` is `8 > 7`, which is true, so the function returns `b` (`1000`).

The output of `main.cpp` is:

```text
7
2.5
pear
largest(0111, 1000): 1000
largest(11, 0001): 11
largest(011, 11): 011
```

## Common mistakes

- **Comparing the number of bits.** `largest("11", "0001")` then returns `0001`, because it has more bits.
- **Comparing the number of 1 bits.** `0111` has three 1 bits and `1000` has one, so `0111` wins, but its value is smaller.
- **Reference parameters** (`Binary& a, Binary& b`). The definition does not match the declaration, and g++ reports `template-id 'largest<Binary>' ... does not match any template declaration`. The build fails, and the mark is 0.
- **Returning `b` when the values are equal** (`>=`). `largest("011", "11")` then prints `11`.
- **Writing `Binary result = a; result = b;`.** `operator=` of `Binary` is private here, so g++ reports `'Binary& Binary::operator=(const Binary&)' is private within this context`. Return `a` or `b` directly.
- **Trying to compare with `b > a`.** `Binary` has no `operator>`, so this does not compile. That is why the specialisation exists.
