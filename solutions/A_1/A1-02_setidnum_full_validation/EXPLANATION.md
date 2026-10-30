# A1-02 Explanation: Employee::setIDNum with full validation

## What the function must do

The function `setIDNum` checks a new ID number with five checks in a fixed order: length, digits, month, day and gender. The first check that fails stops the function with an `Exception` and a message for that check. If all five checks pass, the function stores the ID number in `idNum`. If a check fails, `idNum` keeps its old value.

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

The function `length()` returns an unsigned number. The cast `(int)` makes both sides of the comparison `int`. Here the other side is the fixed number 13, so g++ gives no warning even without the cast. The cast is required in check 2, where the loop compares the variable `i` with the length. There, `-Wall -Werror` turns the signed/unsigned warning into an error. The condition is true for a string that is too short or too long. A `throw` stops the function at once. This check comes first, so the later steps can read index 0 to 12 without leaving the string.

**Check 2: every character is a digit.**

```cpp
    for (int i = 0; i < (int)idNum.length(); i++) {
        if (idNum[i] < '0' || idNum[i] > '9') {
            throw Exception("ID number must contain only digits");
        }
    }
```

The loop visits all 13 characters. The characters `'0'` to `'9'` have consecutive codes. A character below `'0'` or above `'9'` is not a digit. This includes letters, a space and `'-'`. The loop compares characters one by one because a 13-digit number does not fit in an `int`.

This check comes before the month, the day and the gender. Those steps call `extractIntFromString`, and the helper throws `Exception("Not a digit")` for a non-digit. The question requires the message `ID number must contain only digits` for any non-digit in the whole string. For example, the letter `O` at index 2 must give this message and not the helper's message.

**Check 3: the month.**

```cpp
    int month = extractIntFromString(idNum, 2, 4);
    if (month < 1 || month > 12) {
        throw Exception("Invalid birth month");
    }
```

The helper reads index 2 and 3 (the end index 4 is not included) and returns them as a number. The condition is true for 0 and for 13 or more. A valid month is 1 to 12. The two parts are joined with `||`, so one true part is enough to throw.

**Check 4: the day.**

```cpp
    int day = extractIntFromString(idNum, 4, 6);
    if (day < 1 || day > 31) {
        throw Exception("Invalid birth day");
    }
```

The helper reads index 4 and 5. A valid day is 1 to 31. The value 0 is invalid, so the test is `day < 1` and not `day < 0`. The function does not check how many days the month has, so day 30 in month 02 is accepted.

**Check 5: the gender.**

```cpp
    char idGender = 'F';
    if (extractIntFromString(idNum, 6, 10) >= 5000) {
        idGender = 'M';
    }
    if (idGender != gender) {
        throw Exception("ID number does not match gender");
    }
```

The letter starts as `'F'`. The gender digits at index 6 to 9 form a number. A value of 5000 or more means `'M'`. The second `if` compares the letter with the member `gender`. A difference makes the function throw.

**Store the value.**

```cpp
    this->idNum = idNum;
```

This line comes last. The function changes the object only after all five checks pass.

The function never catches an exception and prints nothing. The function allocates no memory.

## Trace

The call is `tryID(sipho, "9105220800087")`. Sipho has `gender` equal to `'M'`.

| Step | Code | Values | Result |
|---|---|---|---|
| 1 | length check | length is 13 | continue |
| 2 | digit loop, `i` from 0 to 12 | all 13 characters are between `'0'` and `'9'` | no throw |
| 3 | `month` | characters at index 2 and 3 are `05` | `month` is 5 |
| 4 | month test | 5 < 1 is false, 5 > 12 is false | continue |
| 5 | `day` | characters at index 4 and 5 are `22` | `day` is 22 |
| 6 | day test | 22 < 1 is false, 22 > 31 is false | continue |
| 7 | gender digits | characters at index 6 to 9 are `0800` | value is 800, `idGender` stays `'F'` |
| 8 | `idGender != gender` | `'F'` != `'M'` is true | throw `Exception("ID number does not match gender")` |

The function `tryID` catches the exception by reference and prints `Rejected 9105220800087: ID number does not match gender`. The ID number is not stored. The last call, `"9105225800087"`, has gender digits `5800`, so `idGender` becomes `'M'`, and the function stores the value.

The call with `"91O5225800087"` stops in step 2 at `i` equal to 2, where the character is the letter `O`. The call with `"9113225800087"` stops in step 4, because the month is 13.

The output of `main.cpp` is:

```text
Accepted: Thandi Mokoena, 29, F, ID: 9702140123081
Rejected 91052258000: ID number must have 13 digits
Rejected 91O5225800087: ID number must contain only digits
Rejected 9113225800087: Invalid birth month
Rejected 9105005800087: Invalid birth day
Rejected 9105220800087: ID number does not match gender
Accepted: Sipho Dlamini, 35, M, ID: 9105225800087
```

## Common mistakes

- **Check the gender before the day.** An ID with a bad day and a gender mismatch then reports the gender message. The edge test uses `9101320800087` and expects `Invalid birth day`. The edge test rejected this change.
- **Accept day 0.** If the test is `day < 0`, the ID `9105005800087` passes the day check. The main output then changes. The main test rejected this change.
- **Skip the digit loop.** The helper then throws `Not a digit` for the ID `91O5225800087`. The question requires `ID number must contain only digits`.
- **Check only the characters that the helper reads.** The ID `910230580008X` has the letter at index 12. No helper call reads index 12, so the function would accept the ID. The edge test expects a rejection.
- **Compare `i` with `idNum.length()` without a cast.** The compiler warns about a signed/unsigned comparison. Under `-Wall -Werror` the build fails, and the mark is 0.
- **Reject day 30 in month 02.** The question says the function does not check how many days a month has. The edge test expects `9102305800087` to be accepted.
