Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A3-01. Assignment operator: `Employee::operator=` (100)

For this question, implement the assignment operator of the `Employee` class in the file `A_3.cpp`. All the other functions of `Employee` and `Exception` are given in the other files.

## UML (only the classes this question needs)

```text
Employee
- age: int
- firstName: string
- surName: string
- idNum: string
- gender: char
+ Employee(string, string, int, char)
+ Employee(const Employee&)
+ operator=(const Employee&): Employee&   <- implement
+ getFirstName(): string
+ getSurName(): string
+ getIDNum(): string
+ getAge(): int
+ getGender(): char
+ setIDNum(string): void
+ extractIntFromString(string, int, int): int   {static}
+ operator<<(ostream&, const Employee&): ostream&   {friend}

Exception
+ message: string
+ Exception(string)
+ what(): string
```

Not on the published partial UML: `Employee::operator=` (the target), `operator<<` (not drawn; the scenario says every class has one), the `int` return type of `extractIntFromString` (the UML shows no return type). The real exam's complete UML may add members like these.

## What `operator=` must do

The statement `a = b;` makes the employee `a` hold the same details as the employee `b`. Write the four steps of an assignment operator:

1. If the object is assigned to itself (`a = a;`), do nothing and return the object.
2. Free the old memory of this object. `Employee` has no pointers (its attributes are `string`, `int` and `char`), so there is nothing to delete in this step.
3. Copy every attribute from the other employee: `firstName`, `surName`, `age`, `gender` and `idNum`. An empty `idNum` (`""`) is copied too.
4. Return the current object by reference (`*this`), so that chaining works: `a = b = c;` first does `b = c`, then `a = b`.

The given `operator<<` in `Employee.cpp` prints `<firstName> <surName>, <age>, <gender>, ID: <idNum>`, and `none` when `idNum` is empty.

## Rules

- Implement only `Employee::operator=` in `A_3.cpp`. The declaration is already in `Employee.h`.
- The other employee is passed as `const Employee&`. The getters are not `const` functions, so you cannot call them on `other`. Use the attributes directly (`other.firstName` and so on). This is allowed inside the class's own operator.
- The marking program checks every attribute, self-assignment (`a = a;`) and chaining (`a = b = c;`).
- Your code must compile with `-std=c++98 -Wall -Werror`. Memory is marked: `valgrind` must show no leaks and no invalid reads or frees.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_3` folder.
2. Run `make A_3`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_3.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
