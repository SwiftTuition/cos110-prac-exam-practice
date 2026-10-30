Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A2-10. Operator overloading: `Team::operator+` returns a merged team (100)

For this question, implement the addition operator `operator+` of the `Team` class in the file `A_2.cpp`. `a + b` makes a **new** team that holds copies of the members of `a` and then copies of the members of `b`. Neither `a` nor `b` changes.

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
+ Team(const Team&)
+ operator=(const Team&): Team&
+ addMember(Employee*): void
+ removeMember(int): void
+ operator[](int): const Employee&
+ getSize(): int
+ getMemberCount(): int
+ operator+(const Team&): Team   {const}   <- implement
+ operator<<(ostream&, const Team&): ostream&   {friend}
```

Not on the published partial UML: `Team(const Team&)`, `Team::operator=`, `Team::addMember`, `Team::removeMember`, `Team::getMemberCount`, `Team::operator+` (the target), `operator<<` (not drawn; the scenario says every class has one), the `int` return type of `extractIntFromString` (the UML shows no return type). The real exam's complete UML may add members like these.

## Given code you will use

- `Team(int size)` makes an array of `size` pointers, all `NULL`. The team owns its employees and deletes them in `~Team()`.
- `Team` has a destructor, a copy constructor and an assignment operator that copies deeply (the rule of three). A deep copy gets its own new `Employee` objects; it does not share them. All three are given: `~Team()`, `Team(const Team& other)` and `Team& operator=(const Team& other)`. So both `Team c = a + b;` (copy constructor) and `c = a + b;` on a team that already exists (assignment operator) are safe.
- `removeMember(int index)` deletes the employee in that slot and sets the slot to `NULL`.
- `Employee(const Employee&)` is the copy constructor of `Employee`.
- `operator<<` prints `Team (<count>/<size>):` and then each employee.

## What `operator+(const Team& other) const` must do

1. Count the members (slots that are not `NULL`) in this team and in `other`. Call the total `count`.
2. Make a new team with exactly `count` slots.
3. Fill it in this order, with no gaps: first a copy of each member of this team (in slot order), then a copy of each member of `other` (in slot order). Skip `NULL` slots. Each copy is made with `new Employee(*...)`.
4. Return the new team **by value**.

Example: this team is `[Thandi, Sipho, NULL]` and `other` is `[Anna, NULL]`. The result has size 3: `[Thandi, Sipho, Anna]`.

More rules:

- The new team must own its own copies. Do not copy the pointers, or two teams would delete the same employee.
- If both teams have no members, the result is a team of size 0.
- `a + a` is allowed and gives every member twice.
- The function is `const`: it must not change this team. Write `const` after the parameter list in `A_2.cpp` too.
- Inside the function you may read `other.members` and `other.size`, and you may set the members of the new team directly, because they are objects of the same class.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_2` folder.
2. Run `make A_2`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_2.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
