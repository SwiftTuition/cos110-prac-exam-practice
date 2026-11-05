# B1-07 Explanation: recursive Binary::setBits

## What the function must do

`setBits(bits, index)` copies characters of `bits` into `array`, from position `index` onward, at the same positions. A `'1'` gives `true`; any other character gives `false`. It stops when `index` reaches the end of the array or the end of the string, the smaller of the two. A negative `index` changes nothing. The given constructor calls `setBits(bits, 0)`, so every `Binary` in the program is filled by this function. Loops and helper functions score 0.

## How the solution works

```cpp
void Binary::setBits(string bits, int index) {
```

The function is a member of `Binary`, so it uses `array` and `size` directly. `bits` is passed by value, so each call gets its own copy of the string. This costs a little time, but it does not leak memory: each copy is freed when its call ends.

```cpp
    if (index < 0 || index >= size || index >= (int)bits.length()) {
        return;
    }
```

This one test has three parts. Any true part ends the call.

- `index < 0`: invalid input. Without it, `setBits("0000", -1)` writes to `array[-1]`, which is before the array.
- `index >= size`: the end of the array. This is the normal base case when the string is at least as long as the array. Without it, `setBits("111111", 0)` on a 4-bit `Binary` writes to `array[4]` and `array[5]`.
- `index >= (int)bits.length()`: the end of the string. Without it, a short string such as `"1"` is read past its last character.
- `bits.length()` returns an unsigned type. Comparing it with the `int` `index` gives the warning `comparison of integer expressions of different signedness`. Under `-Werror` that is a build error. The cast `(int)` removes the warning.
- The function returns `void`, so `return;` has no value.

```cpp
    array[index] = (bits[index] == '1');
    setBits(bits, index + 1);
}
```

- `bits[index] == '1'` is a `bool`: `true` for the character `'1'`, `false` for anything else (`'0'`, `'x'`, a space).
- That value goes into `array[index]`. The array already exists. The constructor made it with `new bool[size]` before the call.
- `setBits(bits, index + 1)` sets the rest, one position to the right. Each call moves toward `size` and toward the string length, so the recursion ends.

## Trace

`main.cpp` makes `Binary b("0000")` and then calls `b.setBits("11", 0)`. The array is `0000`, `size` is 4, and the string length is 2.

| Call | index | `< 0`? | `>= 4`? | `>= 2`? | Action | Array after |
|---|---|---|---|---|---|---|
| 1 | 0 | no | no | no | `array[0]` = (`'1'` == `'1'`) = true | `1000` |
| 2 | 1 | no | no | no | `array[1]` = true | `1100` |
| 3 | 2 | no | no | yes | return | `1100` |

Then `b.setBits("0110", 2)`, string length 4:

| Call | index | Stops? | Action | Array after |
|---|---|---|---|---|
| 1 | 2 | no | `array[2]` = (`'1'` == `'1'`) = true | `1110` |
| 2 | 3 | no | `array[3]` = (`'0'` == `'1'`) = false | `1110` |
| 3 | 4 | `4 >= 4` | return | `1110` |

Bits 0 and 1 are not touched, so they stay `11`.

- `b.setBits("111111", 0)`: calls 0 to 3 set four `true` bits. Call 4 stops at `4 >= size`. The result is `1111`. The last two characters of the string are never read.
- `b.setBits("0000", -1)`: `-1 < 0`, so the first call returns. The array stays `1111`.
- `Binary a("1011")` at the top of `main.cpp`: the constructor calls `setBits("1011", 0)`, which runs 4 setting calls and stops at index 4.

The output of `main.cpp` is:

```text
a: 1011 (size 4)
after setBits("11", 0): 1100
after setBits("0110", 2): 1110
after setBits("111111", 0): 1111
after setBits("0000", -1): 1111
```

## Common mistakes

- **`index >= bits.length()` without the cast.** g++ reports `comparison of integer expressions of different signedness: 'int' and 'std::__cxx11::basic_string<char>::size_type'`. Under `-Werror` the build fails, and the mark is 0.
- **No test for the end of the string.** The function reads characters after the end of `bits`. Those bytes are not part of the string. In `main.cpp` the output still looks right, but valgrind reports `Conditional jump or move depends on uninitialised value(s)`, so the memory mark is lost.
- **No `index < 0` test.** `setBits("0000", -1)` writes `array[-1]`. valgrind reports `Invalid write of size 1`.
- **Creating the array inside `setBits`** (`array = new bool[size];`). The constructor already did this. Every call then makes a new array and loses the old one: valgrind reports `definitely lost`.
- **Setting `array[index] = bits[index];`** without the comparison. A `char` converted to `bool` is `true` for every character except `'\0'`. So `'0'` becomes `true`, and `0000` prints `1111`.
- **A loop or a helper function.** Either one scores 0.
