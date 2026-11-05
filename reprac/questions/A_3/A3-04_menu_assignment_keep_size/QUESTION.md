Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A3-04. Assignment operator: `Menu::operator=` that keeps its own size (100)

Implement the assignment operator of the `Menu` class in `A_3.cpp`. In this version the menu on the left keeps its own `maxSize`: its array is not replaced.

```text
Menu
- maxSize: int
- items: Item**
+ Menu(int)
+ ~Menu()
+ operator=(const Menu&): Menu&     <- implement
+ operator+(Item*): Menu&
+ findFirst(string): Item
+ findLast(string): Item
+ averagePrice(string): float
+ numberAbove(string, float): int
+ numberBelow(string, float): int
+ numberEqual(string, float): int

Item
- type: char
- name: string
- price: float
+ Item(char, string, float)
+ Item(const Item&)
+ ~Item()
+ getType(): char
+ getName(): string
+ getPrice(): float
```

## What the function must do

- `maxSize` is the length of the `items` array. An empty slot holds `NULL`.
- The menu owns its items: `~Menu()` deletes every item and then the array.
- `operator+(Item*)` puts the item in the first `NULL` slot. If the menu is full, it deletes the item.
- `Item` has a copy constructor, so `new Item(*p)` makes a new item with the same type, name and price as `*p`.
- `operator<<` prints `Menu (max N):` and then one line per slot: `  [i] <item>` or `  [i] empty`.
- After `a = b;`, `a` keeps its own `maxSize`. All of `a`'s old items are deleted.
- For every slot number that both menus have, slot `i` of `a` gets a new copy of the item in slot `i` of `b` (or stays `NULL` if that slot of `b` is `NULL`).
- If `b` has more slots than `a`, the items in `b`'s extra slots are not copied. If `a` has more slots than `b`, `a`'s extra slots are `NULL`.
- `a = a;` must leave `a` unchanged. `a = b = c;` must work.

## Rules

- Write only this one function in `A_3.cpp`. Do not change the other files: they are replaced when marked.
- The program must compile with `-Wall -Werror`, print exactly the output at the end of `main.cpp`, and have no memory errors or leaks under valgrind.

## Build and upload

In the `A_3` folder, run `make A_3`. Upload only `A_3.cpp`.
