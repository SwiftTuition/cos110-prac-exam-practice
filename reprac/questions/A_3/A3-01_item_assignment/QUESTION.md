Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A3-01. Assignment operator: `Item::operator=` (100)

Implement the assignment operator of the `Item` class in `A_3.cpp`. After `a = b;`, item `a` has the same type, name and price as item `b`.

```text
Item
- type: char
- name: string
- price: float
+ Item(char, string, float)
+ Item(const Item&)
+ ~Item()
+ operator=(const Item&): Item&     <- implement
+ getType(): char
+ getName(): string
+ getPrice(): float
```

## What the function must do

- Copy all three members: `type`, `name` and `price`.
- Assigning an item to itself (`a = a;`) must leave it unchanged.
- Return `*this`, so that `a = b = c;` works.
- `operator<<` for `Item` prints `<name> (<type>) R<price>`, for example `Soup (S) R50`.

## Rules

- Write only this one function in `A_3.cpp`. Do not change the other files: they are replaced when marked.
- The program must compile with `-Wall -Werror`, print exactly the output at the end of `main.cpp`, and have no memory errors or leaks under valgrind.

## Build and upload

In the `A_3` folder, run `make A_3`. Upload only `A_3.cpp`.
