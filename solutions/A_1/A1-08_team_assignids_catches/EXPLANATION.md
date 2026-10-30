# A1-08 Explanation: Team::assignIDs

## What the function must do

The function `assignIDs` gives the ID number `ids[i]` to the employee in slot `i` of the team. For each `i` from 0 to `n - 1`, the function prints one line. The function `setIDNum` can throw an `Exception`. The function `assignIDs` must catch each exception, print the message and continue with the next slot. The function returns the number of ID numbers that were set.

## How the solution works

The parameter `string* ids` is a pointer to the first element of an array of `string` values. The expression `ids[i]` is the element at position `i`. The member `members` is an array of `Employee*` pointers. An empty slot holds `NULL`.

**Guard for bad input.**

```cpp
    if (ids == NULL || n <= 0) {
        return 0;
    }
```

If `ids` is `NULL`, the array does not exist, and `ids[i]` would read from address 0. If `n` is 0 or negative, the loop has nothing to do. In both cases the function prints nothing and returns 0, as the question requires. The check comes before the loop, so the loop never reads `ids` when `ids` is `NULL`.

**The counter and the loop.**

```cpp
    int count = 0;
    for (int i = 0; i < n; i++) {
        cout << "Slot " << i << ": ";
```

The variable `count` holds the number of ID numbers that were set. The loop runs once for each position in `ids`. Each pass starts the line with `Slot <i>: `. Every case prints this start, so the code prints it once, before the cases.

**Case 1: no such slot.**

```cpp
        if (i >= size) {
            cout << "no such slot" << endl;
```

The array `ids` can be longer than the team. The valid slots are 0 to `size - 1`. This test comes first. The next test reads `members[i]`, and for `i >= size` that read would be outside the array. Valgrind reports such a read.

**Case 2: an empty slot.**

```cpp
        } else if (members[i] == NULL) {
            cout << "empty" << endl;
```

The slot exists but holds no employee. The function must not call `getFirstName` on a `NULL` pointer, because that stops the program abnormally. This case is not an error and needs no `try`.

**Case 3: an employee is present.**

```cpp
        } else {
            cout << members[i]->getFirstName() << " " << members[i]->getSurName() << " -> ";
```

The arrow `->` follows a pointer to a member. The function prints the name and the arrow first, before the call that can fail. If `setIDNum` throws, the name is already on the line, and the error text continues the same line.

```cpp
            try {
                members[i]->setIDNum(ids[i]);
                cout << ids[i] << endl;
                count++;
            } catch (Exception& e) {
                cout << "Error: " << e.what() << endl;
            }
```

- A `try` block holds code that can throw. If the code throws, C++ jumps to the matching `catch` and skips the rest of the `try` block.
- The `catch (Exception& e)` clause catches an `Exception` by reference. The reference `e` is the thrown object, not a copy. The call `e.what()` gives the message.
- If `setIDNum` returns normally, the two lines after it run. The function prints the new ID number and adds 1 to `count`. If `setIDNum` throws, these two lines are skipped, so `count` counts only the successful calls.
- The `try` and `catch` are inside the loop body. After a `catch`, the loop goes on with the next `i`. A `try` around the whole loop would end the loop at the first error.

```cpp
    return count;
```

The function returns the number of successful calls. No exception leaves `assignIDs`. The function allocates and deletes nothing.

## Trace

The team in `main.cpp` has `size` 3. Slot 0 holds Thandi (`'F'`), slot 1 holds Sipho (`'M'`), and slot 2 is `NULL`. The array `ids` has four values, so `n` is 4.

| `i` | `i >= size` | `members[i]` | `setIDNum` | Printed after `Slot i: ` | `count` |
|---|---|---|---|---|---|
| 0 | 0 >= 3 false | Thandi | `9702140123081` has 13 characters, gender digits `0123` give `'F'`, match | `Thandi Mokoena -> 9702140123081` | 1 |
| 1 | 1 >= 3 false | Sipho | `9105220800087` has gender digits `0800`, give `'F'`, Sipho is `'M'`, throw | `Sipho Dlamini -> Error: ID number does not match gender` | 1 |
| 2 | 2 >= 3 false | `NULL` | not called | `empty` | 1 |
| 3 | 3 >= 3 true | not read | not called | `no such slot` | 1 |

The function returns 1. Then `main` prints `IDs set: 1` and the team. Sipho still has no ID number, because `setIDNum` keeps the old value when it throws.

The output of `main.cpp` is:

```text
Slot 0: Thandi Mokoena -> 9702140123081
Slot 1: Sipho Dlamini -> Error: ID number does not match gender
Slot 2: empty
Slot 3: no such slot
IDs set: 1
Team:
  Thandi Mokoena, 29, F, ID: 9702140123081
  Sipho Dlamini, 35, M, ID: none
```

## Common mistakes

- **Put one `try` around the whole loop.** The first exception ends the loop. Slots 2 and 3 never print, and the output differs. The main test rejected this change.
- **Skip the `NULL` check.** For slot 2, the call `members[2]->getFirstName()` uses a `NULL` pointer. Valgrind reports `Invalid read of size 8`, and the program stops with a segmentation fault (SIGSEGV) after it prints `Slot 2: `. The main test rejected this change.
- **Test `members[i]` before `i >= size`.** For `i` equal to 3, the code reads `members[3]`, outside the array. Valgrind reports `Invalid read of size 8`. The value read there is undefined. In the test run it was 0, so the line printed `Slot 3: empty` instead of `Slot 3: no such slot`.
- **Add 1 to `count` before `setIDNum`, or in the `catch`.** The count then includes failed calls. The line `IDs set: 1` would show `IDs set: 2`.
- **Skip the guard for a `NULL` array.** The call `assignIDs(NULL, 3)` then reads `ids[0]` from address 0, which is not a valid array. This is undefined behaviour. In the edge test, valgrind reports `Invalid read of size 8`, and the program stops with a segmentation fault (SIGSEGV).
- **Let an exception leave the function.** If a `catch` clause names another type, such as `catch (string& e)`, the `Exception` is not caught. The program stops with `terminate called after throwing an instance of 'Exception'`, and the mark is 0.
