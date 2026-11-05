# B3-03 Explanation: isEqual<Binary>

## What the function must do

The general template `isEqual<T>(a, b)` returns `a == b`. `Binary` has no `operator==`, so the general version cannot be built for it. The specialisation returns `true` when the two strings have the same size and the same bit at every index, and `false` otherwise. So `011` and `11` are not equal, even though both have the value 3.

## How the solution works

```cpp
template <>
bool isEqual<Binary>(const Binary& a, const Binary& b) {
```

- `template <>` marks a specialisation, and `isEqual<Binary>` sets `T` to `Binary`.
- The general parameters are `const T&`, so here they are `const Binary&`. No copy is made, and the function cannot change either string. The definition must match the declaration in `Templates.h` exactly.

```cpp
    if (a.getSize() != b.getSize()) {
        return false;
    }
```

- Strings of different sizes are never equal, so the function returns `false` at once.
- This test also protects the loop below. The loop runs to `a.getSize()`. If `b` were shorter, `b[i]` would read past the end of `b`'s array.

```cpp
    for (int i = 0; i < a.getSize(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}
```

- The sizes are equal here, so `i` is a valid index in both strings.
- `a[i]` and `b[i]` use the `const` version of `operator[]`, because `a` and `b` are `const`.
- At the first bit that differs, the function returns `false`. There is no need to check the rest.
- If the loop ends, every bit matched, so the result is `true`. For two empty strings the loop does not run, and the result is `true`.

## Where the code lives, and why

`Templates.h` holds the general template and, after it, the declaration `template <> bool isEqual<Binary>(const Binary& a, const Binary& b);`. `B_3.cpp` holds the one definition. A full specialisation is an ordinary function, so it is defined once. The declaration comes after the general template and before any call, so `main.cpp` uses the specialisation.

## Trace

`main.cpp` calls the general template twice and the specialisation four times.

| Call | Version | Steps | Result |
|---|---|---|---|
| `isEqual(3, 3)` | general, `T = int` | `3 == 3` | equal |
| `isEqual(string("on"), string("off"))` | general, `T = string` | `"on" == "off"` | not equal |
| `0101`, `0101` | specialisation | sizes 4, 4; bits 0 to 3 all match | equal |
| `0101`, `0100` | specialisation | sizes 4, 4; indexes 0 to 2 match; at index 3, `a` has 1 and `b` has 0 | not equal |
| `011`, `11` | specialisation | sizes 3, 2: differ | not equal |
| `11`, `011` | specialisation | sizes 2, 3: differ | not equal |

The loop for `0101` and `0100` (the sizes are equal, so the loop runs):

| i | `a[i]` | `b[i]` | `a[i] != b[i]` | Result |
|---|---|---|---|---|
| 0 | 0 | 0 | false | continue |
| 1 | 1 | 1 | false | continue |
| 2 | 0 | 0 | false | continue |
| 3 | 1 | 0 | true | return `false` |

For `0101` and `0101`, rows 0 to 2 are the same. At `i` = 3 both bits are 1, so the test is false. At `i` = 4, `4 < 4` is false, the loop ends, and the function returns `true`.

The output of `main.cpp` is:

```text
3 and 3: equal
on and off: not equal
0101 and 0101: equal
0101 and 0100: not equal
011 and 11: not equal
11 and 011: not equal
```

## Common mistakes

- **No size test.** For `011` and `11`, the loop runs to 3 and reads `b[2]`, past the end of `b`'s array of 2. valgrind reports `Invalid read of size 1`.
- **Comparing decimal values.** `011` and `11` then count as equal. The question defines equal as the same size and the same bits.
- **`template <class T>` instead of `template <>`.** Written as `template <class T> bool isEqual(const Binary& a, const Binary& b)`, this declares a second, different template that is never called. The specialisation declared in `Templates.h` has no definition, and the link fails with `undefined reference to 'bool isEqual<Binary>(Binary const&, Binary const&)'`. The mark is 0. Written with `isEqual<Binary>` in the name, it fails earlier: `template-id 'isEqual<Binary>' in declaration of primary template`.
- **Returning `true` at the first matching bit.** The rest of the bits are never checked, so `0101` and `0100` count as equal.
- **Writing `return a == b;`.** `Binary` has no `operator==`, so this does not compile.
