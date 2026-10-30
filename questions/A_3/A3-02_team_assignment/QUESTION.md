Practice question based on the published HRMS scenario. The real exam's complete UML may differ.

# A3-02. Assignment operator: `Team::operator=` (100)

For this question, implement the assignment operator of the `Team` class in the file `A_3.cpp`. All the other functions of `Team`, `Employee` and `Exception` are given in the other files.

## UML (only the classes this question needs)

```text
Team
- members: Employee**
- size: int
+ Team(int)
+ ~Team()
+ operator=(const Team&): Team&   <- implement
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

Not on the published partial UML: `Team::operator=` (the target), `Team::addMember`, `Team::removeMember`, `Team::getMemberCount`, `operator<<` (not drawn; the scenario says every class has one). The real exam's complete UML may add members like these.

How the given `Team` works:

- `members` is an array of `size` pointers. Each slot holds an `Employee*` or `NULL`. `NULL` means the slot is empty.
- The team owns its employees. `~Team()` deletes every employee and then the array.
- `addMember` puts an employee in the first empty slot. It throws `Exception("Team is full")` when there is no empty slot.
- `removeMember(i)` deletes the employee in slot `i` and sets the slot to `NULL`.
- The `Team` copy constructor is not used in this question. `Team.h` declares it private, so a `Team` cannot be copied by mistake.

## What `operator=` must do

The statement `a = b;` makes team `a` a deep copy of team `b`. A deep copy gets its own new objects; it does not share them with the original.

1. If the team is assigned to itself (`a = a;`), do nothing and return the team.
2. Delete every employee that this team owns, and then delete the `members` array.
3. Set `size` to the other team's size and create a new array of that size.
4. For every slot of the other team: if the slot is `NULL`, this slot is `NULL`. Otherwise, this slot gets a **new copy** of that employee (use the `Employee` copy constructor). Every employee stays in the same slot number.
5. Return the current object by reference (`*this`), so that `a = b = c;` works.

After the assignment, the two teams must not share any `Employee` object. A change to one team must not show in the other team, and deleting both teams must not delete any employee twice.

## Rules

- Implement only `Team::operator=` in `A_3.cpp`. The declaration is already in `Team.h`.
- `other` is a `const Team&`. `getSize()` and `getMemberCount()` are not `const` functions, so use `other.size` and `other.members` directly. This is allowed inside the class's own operator.
- Your code must compile with `-std=c++98 -Wall -Werror`. Memory is marked: `valgrind` must show no leaks and no invalid reads or frees.

Print formats: the print formats in this question (the given `operator<<` functions and the `ExpectedOutput` block) belong to this question only. Other questions in this bank may print the same class differently.

## Build and upload

1. Open a terminal in the `A_3` folder.
2. Run `make A_3`. This compiles with `g++ -g -std=c++98 -Wall -Werror` and runs the program with `valgrind`.
3. Compare your output with the `ExpectedOutput` block at the end of `main.cpp`. It must match exactly.
4. You may change `main.cpp` to test more cases. Do not change any other given file.
5. Upload only `A_3.cpp`. Every other file, `main.cpp` included, is replaced when your work is marked.

Marking: the code must compile with no warnings, print exactly the expected output and free all memory (valgrind is used). If the code does not compile, or the program stops abnormally (for example because of an uncaught exception), the mark is 0.
