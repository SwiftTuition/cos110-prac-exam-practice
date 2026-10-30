# A1-01 Explanation: Employee::setIDNum

## What the function must do

The function `setIDNum` receives a new ID number as a `string`. It checks two things in a fixed order: the length is 13, and the gender digits match the employee's `gender`. If both checks pass, the function stores the ID number in the member `idNum`. If a check fails, the function throws an `Exception` and leaves the old `idNum` unchanged.

## How the solution works

```cpp
void Employee::setIDNum(string idNum) {
```

The parameter has the same name as the member `idNum`. Inside the function, the plain name `idNum` means the parameter. The member is written `this->idNum`. The word `this` is a pointer to the object on which the function was called.

**Step 1: the length check.**

```cpp
    if ((int)idNum.length() != 13) {
        throw Exception("ID number must have 13 digits");
    }
```

- The function `length()` returns an unsigned number. The cast `(int)` turns it into an `int`, so both sides of the comparison have the same type.
- The condition is true when the string is shorter or longer than 13 characters. This includes the empty string.
- A `throw` stops the function at once. The line `this->idNum = idNum;` never runs, so the old value stays.
- This check comes first. The next step reads index 6 to 9. If the string has fewer than 10 characters, `extractIntFromString` would throw `Exception("Invalid range")` instead. The question asks for the length message in that case.

**Step 2: read the gender digits.**

```cpp
    int genderDigits = extractIntFromString(idNum, 6, 10);
```

The given static function reads index 6, 7, 8 and 9 and returns them as one number. The end index 10 is not included. If one of these four characters is not a digit, `extractIntFromString` throws `Exception("Not a digit")`. The solution has no `try` and no `catch`, so the exception goes to the caller. The question says the function must not catch its own exceptions.

**Step 3: turn the number into a letter.**

```cpp
    char idGender = 'F';
    if (genderDigits >= 5000) {
        idGender = 'M';
    }
```

The letter starts as `'F'`. The `if` condition checks the boundary of the male range. The value 5000 is male, so the test uses `>=` and not `>`. The value 4999 stays female.

**Step 4: compare with the employee.**

```cpp
    if (idGender != gender) {
        throw Exception("ID number does not match gender");
    }
```

The name `gender` is the member of the employee. If the letters differ, the function throws and does not store the ID number.

**Step 5: store the value.**

```cpp
    this->idNum = idNum;
```

This line comes last. The function changes the object only after both checks pass. If the line came first, a failed call would still change the object.

No memory is allocated in this function, so there is nothing to free. The `string` objects manage their own memory.

## Trace

The call is `sipho->setIDNum("9105220800087")`. The employee Sipho has `gender` equal to `'M'` and `idNum` equal to `""`.

| Step | Code | Values | Result |
|---|---|---|---|
| 1 | length check | length is 13 | condition false, continue |
| 2 | `extractIntFromString(idNum, 6, 10)` | characters at index 6 to 9 are `0800` | `genderDigits` is 800 |
| 3 | `genderDigits >= 5000` | 800 >= 5000 is false | `idGender` stays `'F'` |
| 4 | `idGender != gender` | `'F'` != `'M'` is true | throw `Exception("ID number does not match gender")` |
| 5 | store | not reached | `idNum` stays `""` |

The `catch (Exception& e)` in `main` receives the exception. A catch by reference uses the thrown object itself and does not copy it. The line `cout << "Caught: " << e.what() << endl;` prints the message. The later `cout << *sipho` prints `ID: none`, because `operator<<` prints `none` when `idNum` is empty.

The first call in `main` uses the ID `"910522580008"`, which has 12 characters. Step 1 throws. The last call uses `"9105225800087"`, whose gender digits are `5800`. Step 3 gives `'M'`, step 4 passes, and step 5 stores the ID.

The output of `main.cpp` is:

```text
Thandi Mokoena, 29, F, ID: 9702140123081
Caught: ID number must have 13 digits
Caught: ID number does not match gender
Sipho Dlamini, 35, M, ID: none
Sipho Dlamini, 35, M, ID: 9105225800087
```

## Common mistakes

- **Use `>` instead of `>=` for 5000.** The ID `8001015000081` belongs to a male employee. With `>`, the function reads 5000 as female and throws. The edge test rejected this change because its output differed.
- **Store the ID before the checks.** If the first line is `this->idNum = idNum;`, a failed call still changes the object. The fourth output line would be `Sipho Dlamini, 35, M, ID: 9105220800087`, the ID that failed the gender check, and not `ID: none`. The main test rejected this change.
- **Write `idNum = idNum;` at the end.** Inside the function, both names mean the parameter. The member never changes. The compiler gives no warning for this line. The first and the last output lines would show `ID: none`.
- **Catch `Exception` inside `setIDNum`.** The caller then never sees `Not a digit`. The edge test expects the line `Caught: Not a digit`.
- **Check the gender before the length.** For a string with fewer than 10 characters, such as the empty string, `extractIntFromString` cannot read index 6 to 9 and throws `Invalid range`. The expected message is `ID number must have 13 digits`. The edge test prints `Caught: Invalid range` for the empty string and rejects this change.
