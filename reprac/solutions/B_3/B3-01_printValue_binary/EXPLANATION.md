# B3-01 Explanation: printValue<Binary>

## What the function must do

The general template `printValue<T>` prints `Value: ` and the value. The specialisation for `Binary` must print `Binary: `, the bits, and the decimal value in parentheses, for example `Binary: 0101 (5)`, followed by `endl`.

## What a specialisation is

A **function template** is a recipe: `template <class T> void printValue(const T& value)` lets the compiler build one version for each type that is used. `printValue(5)` builds a version with `T = int`.

A **specialisation** is a version that you write yourself for one exact type. When the program calls `printValue` with a `Binary`, the compiler uses your version instead of building one from the recipe. Lecture 19 defines it as overloading a template function "to have a different behaviour if a specific type is used".

## How the solution works

```cpp
#include "Templates.h"

template <>
void printValue<Binary>(const Binary& value) {
```

- `#include "Templates.h"` brings in the general template and the declaration of this specialisation. The definition must come after both.
- `template <>` with empty angle brackets says: this is a specialisation, and no type is left open.
- `printValue<Binary>` names the type for `T`.
- The parameter is `const Binary&` because the general parameter is `const T&`, and `T` is `Binary`. The definition must match the declaration in `Templates.h` exactly.
- `const` means the function cannot change the `Binary`. It can still call `getSize()` and the `const` `operator[]`, because both are `const` members.

```cpp
    int decimal = 0;
    for (int i = 0; i < value.getSize(); i++) {
        decimal = decimal * 2;
        if (value[i]) {
            decimal = decimal + 1;
        }
    }
```

- The loop reads the bits from the left (index 0), which is the most significant bit.
- Each bit doubles the value so far, then adds 1 if the bit is 1. This builds the number without a power function.
- For an empty string the loop does not run, and `decimal` stays 0.

```cpp
    cout << "Binary: " << value << " (" << decimal << ")" << endl;
}
```

- `cout << value` uses the given `operator<<` for `Binary`, which prints the bits.
- The function allocates nothing, so there is nothing to free.

## Where the code lives, and why

| File | Holds | Why |
|---|---|---|
| `Templates.h` | the general template (full body), then the declaration `template <> void printValue<Binary>(const Binary& value);` | The general template must be visible wherever it is used, so its body is in the header. The declaration comes after the general template and before any call (Lecture 19 rule), so every file that includes the header calls the specialisation. |
| `B_3.cpp` | the definition of the specialisation | A full specialisation is an ordinary function. It needs exactly one definition in the whole program. `B_3.cpp` is compiled once. |

If the body were placed in `Templates.h` without `inline`, both `main.cpp` and `B_3.cpp` would contain it, and the linker would report `multiple definition of 'void printValue<Binary>(Binary const&)'`.

## Trace

| Call in `main.cpp` | Version used | Output |
|---|---|---|
| `printValue(5)` | general, `T = int` | `Value: 5` |
| `printValue(2.5)` | general, `T = double` | `Value: 2.5` |
| `printValue(string("embedded"))` | general, `T = string` | `Value: embedded` |
| `printValue('c')` | general, `T = char` | `Value: c` |
| `printValue(a)`, `a` = `0101` | specialisation | `Binary: 0101 (5)` |
| `printValue(Binary("11111111"))` | specialisation | `Binary: 11111111 (255)` |

The loop for `0101`:

| i | `value[i]` | decimal after |
|---|---|---|
| 0 | 0 | 0 × 2 = 0 |
| 1 | 1 | 0 × 2 + 1 = 1 |
| 2 | 0 | 1 × 2 = 2 |
| 3 | 1 | 2 × 2 + 1 = 5 |

The output of `main.cpp` is:

```text
Value: 5
Value: 2.5
Value: embedded
Value: c
Binary: 0101 (5)
Binary: 11111111 (255)
```

## Common mistakes

- **`Binary&` instead of `const Binary&`.** The definition then does not match any specialisation of the template. g++ reports `template-id 'printValue<Binary>' for 'void printValue(Binary&)' does not match any template declaration`. The build fails, and the mark is 0.
- **Reading the bits from the right.** The last bit becomes the most significant bit: `0101` prints `(10)`.
- **`template <class T>` instead of `template <>`, with `<Binary>` in the name**, as in `template <class T> void printValue<Binary>(const Binary& value)`. g++ reports `template-id 'printValue<Binary>' in declaration of primary template`. The build fails, and the mark is 0.
- **`template <class T>` instead of `template <>`, without `<Binary>` in the name**, as in `template <class T> void printValue(const Binary& value)`. The file compiles, but it declares a new template, not a specialisation. The specialisation declared in `Templates.h` stays undefined. The link fails with `undefined reference to 'void printValue<Binary>(Binary const&)'`, and the mark is 0.
- **Writing the general template again in `B_3.cpp`.** g++ reports `redefinition of 'template<class T> void printValue(const T&)'`.
- **Forgetting `endl`, or printing `Value: ` as well.** The output must match the given format exactly.
