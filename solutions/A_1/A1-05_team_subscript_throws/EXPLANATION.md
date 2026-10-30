# A1-05 Explanation: Team::operator[]

## What the function must do

The operator `operator[]` of `Team` returns the employee stored in slot `index` of the array `members`. The return type is a reference, so the function has no way to return `NULL`. If the index is outside the array, the function throws `Exception("Index out of bounds")`. If the slot is empty, the function throws `Exception("No employee at this index")`.

## How the solution works

```cpp
const Employee& Team::operator[](int index) {
```

The return type `const Employee&` is a reference to an `Employee` that the caller cannot change. A reference is another name for an existing object. The function returns the employee that is already in the team. The function makes no copy.

The member `members` has the type `Employee**`. It points to an array of `Employee*` pointers. Each pointer is either the address of an employee or `NULL`. The slot of an empty position holds `NULL`. The member `size` is the number of slots.

**Check 1: the range.**

```cpp
    if (index < 0 || index >= size) {
        throw Exception("Index out of bounds");
    }
```

- `index < 0` is true for a negative index.
- `index >= size` is true when the index is `size` or larger. The valid indexes are 0 to `size - 1`, so the index `size` is already outside the array.
- The two parts are joined with `||`. One true part is enough to throw.
- For a team with `size` 0, every index fails this check.

**Check 2: the slot.**

```cpp
    if (members[index] == NULL) {
        throw Exception("No employee at this index");
    }
```

The condition is true when the slot exists but holds no employee. An empty slot occurs at the end of a team that is not full. It also occurs after `removeMember`, which deletes the employee and sets the slot to `NULL`. If the function returned `*members[index]` for a `NULL` pointer, the program would use the address 0 and crash.

The order of the two checks matters. The condition `members[index]` reads memory. With a bad index, this read is outside the array. Valgrind reports an invalid read. The range check must run first, so the function reads `members[index]` only for a valid index.

**Return the employee.**

```cpp
    return *members[index];
```

The expression `members[index]` is a pointer. The star `*` follows the pointer and gives the employee. The function returns this employee as a reference. The team still owns the employee and deletes it in `~Team()`. The function allocates and deletes nothing.

The function throws the `Exception` object by value with `throw Exception(...)`. The caller catches it with `catch (Exception& ex)`. The `&` makes the catch use the thrown object without a copy.

## Trace

The team in `main.cpp` has `size` 3. The calls to `addMember` fill slots 0 and 1. Slot 2 is `NULL`.

| Call | `index < 0` | `index >= size` | `members[index]` | Result |
|---|---|---|---|---|
| `show(*team, 0)` | false | 0 >= 3 false | address of Thandi | return Thandi |
| `show(*team, 1)` | false | 1 >= 3 false | address of Sipho | return Sipho |
| `show(*team, 2)` | false | 2 >= 3 false | `NULL` | throw `No employee at this index` |
| `show(*team, 3)` | false | 3 >= 3 true | not read | throw `Index out of bounds` |
| `show(*team, -1)` | true | not evaluated | not read | throw `Index out of bounds` |

For `-1`, the first part of `||` is true, so C++ does not evaluate the second part. The function `show` prints the employee when the call returns and prints `Caught:` plus the message when the call throws.

The output of `main.cpp` is:

```text
[0] Thandi Mokoena, 29, F, ID: none
[1] Sipho Dlamini, 35, M, ID: none
[2] Caught: No employee at this index
[3] Caught: Index out of bounds
[-1] Caught: Index out of bounds
```

## Common mistakes

- **Check the slot before the range.** For index 3 in a team of size 3, the code reads `members[3]`, which is outside the array. For index -1, it reads `members[-1]`, which is before the array. Valgrind reports `Invalid read of size 8` for both calls. The value read there is undefined. In the test run it was 0, so both lines printed `No employee at this index` instead of `Index out of bounds`. The main test rejected this change.
- **Write `index > size` in the range check.** The index `size` then passes the check and `members[size]` is read outside the array. Valgrind reports `Invalid read of size 8`. In the test run the line for index 3 printed `No employee at this index` instead of `Index out of bounds`. The main test rejected this change.
- **Skip the `NULL` check.** For an empty slot, `*members[index]` follows a `NULL` pointer. When the caller prints the employee, valgrind reports `Invalid read of size 8` and the program stops with a segmentation fault (SIGSEGV). The mark is 0.
- **Write `return members[index];`.** This returns a pointer, and the return type is a reference. The compiler reports an error.
- **Write `throw new Exception(...)`.** This throws a pointer. The clause `catch (Exception& ex)` does not match a pointer, so the exception is not caught. The program stops with `terminate called after throwing an instance of 'Exception*'`, and the mark is 0.
- **Use one message for both errors.** The question requires two different messages. With only `Index out of bounds`, the line for index 2 is wrong. With only `No employee at this index`, the lines for index 3 and -1 are wrong.
