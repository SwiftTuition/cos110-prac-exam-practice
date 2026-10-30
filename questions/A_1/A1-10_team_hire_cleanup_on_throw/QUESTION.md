Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A1-10. Exceptions: `Team::hire` frees memory before it throws again (100)

For this question, implement the `hire` function of the `Team` class in the file `A_1.cpp`. The function makes a new employee with `new`, gives it an ID number and adds it to the team. Two of the given functions can throw an `Exception` while `hire` runs. When that happens, your function must free the new employee (no memory leak) and then let the **same** exception reach the caller.

## UML (only the classes this question needs)

```text
Exception
+ message: string
+ Exception(string)
+ what(): string

Employee
- age: int
- firstName: string
- surName: string
- idNum: string
- gender: char
+ Employee(string, string, int, char)
+ Employee(const Employee&)
+ getFirstName(): string
+ getSurName(): string
+ getIDNum(): string
+ getAge(): int
+ getGender(): char
+ setIDNum(string): void
+ extractIntFromString(string, int, int): int   {static}
+ operator<<(ostream&, const Employee&): ostream&   {friend}

Team
- members: Employee**
- size: int
+ Team(int)
+ ~Team()
+ addMember(Employee*): void
+ operator[](int): const Employee&
+ getSize(): int
+ getMemberCount(): int
+ hire(string, string, int, char, string): void   <- implement
+ operator<<(ostream&, const Team&): ostream&   {friend}
```

Not on the published partial UML: `Team::addMember`, `Team::getMemberCount`, `Team::hire` (the target), `operator<<` (not drawn; the scenario says every class has one), the `int` return type of `extractIntFromString` (the UML shows no return type). The real exam's complete UML may add members like these.

## Given code you will use

- `Employee::setIDNum(string)` throws `Exception("ID number must have 13 digits")`, `Exception("Not a digit")` or `Exception("ID number does not match gender")`. (Digits 6 to 9 give the gender: 5000 or more is `'M'`.)
- `Team::addMember(Employee*)` puts the employee in the first empty slot. It throws `Exception("Team is full")` when there is no empty slot. When it throws, the team does not keep the pointer.
- The team owns the employees it holds and deletes them in `~Team()`.

## What `hire(string firstName, string surName, int age, char gender, string idNum)` must do

1. Make a new employee with `new Employee(firstName, surName, age, gender)`.
2. Call `setIDNum(idNum)` on the new employee.
3. Call `addMember` with the new employee.

If step 2 or step 3 throws an `Exception`, `hire` must free the new employee and then throw the same exception, so that the caller gets the same message. If nothing throws, the team owns the new employee, and `hire` must not delete it.

More rules:

- Do the steps in this order. When the ID number is bad **and** the team is full, the caller must get the ID number message.
- `hire` must not print anything.
- valgrind must report no leaks, also after many failed hires.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_1` folder.
2. Run `make A_1`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_1.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.

Hints for this practice question are in `HINTS.md` in this folder.
