Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A2-01. Operator overloading: `operator<<` for `Employee` (100)

For this question, implement the stream insertion operator `operator<<` for the `Employee` class in the file `A_2.cpp`. It is a `friend` function of `Employee`, so it can read the private members.

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
+ operator<<(ostream&, const Employee&): ostream&   {friend}   <- implement
```

Not on the published partial UML: `operator<<` (not drawn; the scenario says every class has one; the one for `Employee` is the target), the `int` return type of `extractIntFromString` (the UML shows no return type). The real exam's complete UML may add members like these.

## What `operator<<(ostream& out, const Employee& e)` must print

```text
<firstName> <surName>, <age>, <gender>, ID: <idNum>
```

- If `idNum` is the empty string `""` (no ID number set yet), print `none` in its place.
- Examples: `Thandi Mokoena, 29, F, ID: 9702140123081` and `Sipho Dlamini, 35, M, ID: none`.
- There is one space after each comma and after `ID:`. Nothing is printed after the ID number: **no newline**. `main` adds `endl` itself.
- Write to the stream `out`, not to `cout`. The marking program may send the output to a different stream.
- Return `out`, so that calls can be chained: `cout << a << " | " << b << endl;`
- Write the word `friend` only in the class. Do not write it again in `A_2.cpp`.

Note: `e` is a `const` reference, and the getters (`getFirstName()` and so on) are not `const` member functions. A `const` object cannot call them. Use the data members directly (`e.firstName`), which a friend may do.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
