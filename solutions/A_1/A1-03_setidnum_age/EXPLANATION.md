# A1-03 Explanation: Employee::setIDNum with the age check

## What the function must do

The function `setIDNum` checks a new ID number against the employee. It checks the length, then the age that the birth year gives, then the gender digits. If all three checks pass, the function stores the ID number in `idNum`. If one check fails, the function throws an `Exception` with the message for that check and leaves `idNum` unchanged.

## How the solution works

```cpp
void Employee::setIDNum(string idNum) {
```

The parameter `idNum` has the same name as the member `idNum`. Inside the function, the plain name means the parameter. The member is written `this->idNum`. The word `this` is a pointer to the object on which the function was called.

**Check 1: the length.**

```cpp
    if ((int)idNum.length() != 13) {
        throw Exception("ID number must have 13 digits");
    }
```

The function `length()` returns an unsigned number. The cast `(int)` makes both sides of the comparison `int`. The condition is true for any string that does not have 13 characters. This check comes first because the next steps read index 0 and 1, and later index 6 to 9. A string with fewer than 10 characters would make `extractIntFromString` throw `Invalid range` instead of the expected message.

**Check 2: the age.**

```cpp
    int yy = extractIntFromString(idNum, 0, 2);
    int birthYear = 1900 + yy;
    if (yy <= 26) {
        birthYear = 2000 + yy;
    }
    if (age != 2026 - birthYear) {
        throw Exception("ID number does not match age");
    }
```

- The call reads index 0 and 1 (the end index 2 is not included) and returns the two digits as a number. If one of them is not a digit, the helper throws `Not a digit`. The solution does not catch it, so it goes to the caller.
- The variable `birthYear` starts as the 1900s year.
- The `if` condition `yy <= 26` follows the rule in the question. A value of 26 or less belongs to the 2000s. The value 26 must be included, so the test uses `<=` and not `<`. The value 27 gives 1927.
- The condition `age != 2026 - birthYear` compares the stored `age` of the employee with the age that the ID number gives. The year 2026 is the current year in this question. A difference means the ID number does not fit the employee, so the function throws.

**Check 3: the gender.**

```cpp
    char idGender = 'F';
    if (extractIntFromString(idNum, 6, 10) >= 5000) {
        idGender = 'M';
    }
    if (idGender != gender) {
        throw Exception("ID number does not match gender");
    }
```

The letter starts as `'F'`. The gender digits at index 6 to 9 form a number. A value of 5000 or more means `'M'`. The second `if` compares this letter with the member `gender`. A difference makes the function throw.

**Store the value.**

```cpp
    this->idNum = idNum;
```

This line comes last. The function changes the object only after all three checks pass.

The order of the checks matters. An ID that is wrong for both age and gender must report the age message. The edge test checks this order. The function allocates no memory, so there is nothing to free.

## Trace

The call is `tryID(anna, "8503305800089")`. The employee Anna has `age` 41 and `gender` `'F'`.

| Step | Code | Values | Result |
|---|---|---|---|
| 1 | length check | length is 13 | continue |
| 2 | `extractIntFromString(idNum, 0, 2)` | characters `85` | `yy` is 85 |
| 3 | `birthYear = 1900 + yy` | 1900 + 85 | `birthYear` is 1985 |
| 4 | `yy <= 26` | 85 <= 26 is false | `birthYear` stays 1985 |
| 5 | `age != 2026 - birthYear` | 41 != 41 is false | continue |
| 6 | `extractIntFromString(idNum, 6, 10)` | characters `5800` | value is 5800 |
| 7 | `>= 5000` | 5800 >= 5000 is true | `idGender` is `'M'` |
| 8 | `idGender != gender` | `'M'` != `'F'` is true | throw `Exception("ID number does not match gender")` |

The function `tryID` catches the exception by reference and prints `Rejected 8503305800089: ID number does not match gender`. The next call uses `"8503300800089"`. Its gender digits are `0800`, so `idGender` stays `'F'` and the ID number is stored.

The output of `main.cpp` is:

```text
Accepted: Thandi Mokoena, 29, F, ID: 9702140123081
Accepted: Sipho Dlamini, 35, M, ID: 9105225800087
Rejected 8503305800089: ID number does not match gender
Accepted: Anna Botha, 41, F, ID: 8503300800089
Rejected 9001015800083: ID number does not match age
Accepted: Bongani Zulu, 30, M, ID: 9601015800083
```

## Common mistakes

- **Write `yy < 26`.** The year `26` then gives 1926 and age 100. An employee with age 0 and the ID `2601010001080` is rejected. The edge test rejected this change because its output differed.
- **Check the gender before the age.** An ID that is wrong in both ways then reports `ID number does not match gender`. The edge output expects `ID number does not match age` for `9901010001080`. The edge test rejected this change.
- **Use the wrong current year or the wrong direction.** The age is `2026 - birthYear`. If the code uses `birthYear - 2026` or another year, correct IDs are rejected and the output differs.
- **Catch the exception from `extractIntFromString`.** The caller then never receives `Not a digit`. The edge test expects the line `Rejected 0A01015001080: Not a digit`.
- **Store `idNum` before the checks.** A failed call then changes the object, and the printed ID is wrong. The last three lines of the edge output show the IDs of failed calls.
