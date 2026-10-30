Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A3-07. Copy constructor: `Team::Team(const Team&)` (100)

For this question, implement the copy constructor of the `Team` class in the file `A_3.cpp`. All the other functions of `Team`, `Employee` and `Exception` are given in the other files, including `Team::operator=`.

The exam's A_3 question asks for an assignment operator. The copy constructor is its partner in the rule of three (a destructor, a copy constructor and an assignment operator that copies deeply), and it is often written by reusing `operator=`, so it is practised in this section.

## UML (only the classes this question needs)

```text
Team
- members: Employee**
- size: int
+ Team(int)
+ Team(const Team&)   <- implement
+ ~Team()
+ operator=(const Team&): Team&
+ addMember(Employee*): void
+ removeMember(int): void
+ operator[](int): const Employee&
+ getSize(): int
+ getMemberCount(): int
+ operator<<(ostream&, const Team&): ostream&   {friend}

Employee
- age: int
- firstName: string
- surName: string
- idNum: string
- gender: char
+ Employee(string, string, int, char)
+ Employee(const Employee&)
+ operator<<(ostream&, const Employee&): ostream&   {friend}

Exception
+ message: string
+ Exception(string)
+ what(): string
```

The other `Employee` members are in `Employee.h`.

Not on the published partial UML: `Team(const Team&)` (the target), `Team::operator=`, `Team::addMember`, `Team::removeMember`, `Team::getMemberCount`, `operator<<` (not drawn; the scenario says every class has one). The real exam's complete UML may add members like these.

How the given `Team` works:

- `members` is an array of `size` pointers. Each slot holds an `Employee*` or `NULL`. `NULL` means the slot is empty.
- The team owns its employees. `~Team()` deletes every employee and then the array.
- `Team::operator=` is given. It checks for self-assignment, deletes every employee in `members` and the old array, and then makes a deep copy of the other team (a new array, a new copy of every employee, `NULL` slots stay `NULL`).

## What the copy constructor must do

The copy constructor runs when a new team is made from an existing team, for example `Team b(a);`, `Team b = a;`, or when a `Team` is passed to a function by value. It makes a deep copy: the copy gets its own new objects; it does not share them with the original.

1. The new team gets the same `size` as the other team and a **new** array of that size.
2. For every slot of the other team: if the slot is `NULL`, the new slot is `NULL`. Otherwise, the new slot gets a **new copy** of that employee (use the `Employee` copy constructor). Every employee stays in the same slot number.
3. The two teams must not share any `Employee` object.

You may write the deep copy yourself, or you may reuse the given `operator=`.

## Rules

- Implement only `Team::Team(const Team&)` in `A_3.cpp`. The declaration is already in `Team.h`.
- `getSize()` and `getMemberCount()` are not `const` functions, so use `other.size` and `other.members` directly. This is allowed inside the class's own constructor.
- Your code must compile with `-std=c++98 -Wall -Werror`. Memory is marked: `valgrind` must show no leaks and no invalid reads or frees.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_3` folder.
2. Run `make A_3`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_3.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.

Hints for this practice question are in `HINTS.md` in this folder.
