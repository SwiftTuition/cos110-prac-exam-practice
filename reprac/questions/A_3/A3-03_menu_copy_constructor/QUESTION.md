Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A3-03. Copy constructor: `Menu::Menu(const Menu&)` (100)

The copy constructor is not in the published UML; this question practises the same deep copy as `operator=`. Implement the copy constructor of the `Menu` class in `A_3.cpp`. The new menu must be a deep copy of `other`.

```text
Menu
- maxSize: int
- items: Item**
+ Menu(int)
+ Menu(const Menu&)     <- implement
+ ~Menu()
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
- The new menu has the same `maxSize` as `other`. Slot `i` holds a new copy of `other`'s item in slot `i`, or `NULL`.
- Changing `other` afterwards must not change the copy.
- The copy constructor runs for `Menu b(a);`, for `Menu c = b;` and when a `Menu` is passed by value.

## Rules

- Write only this one function in `A_3.cpp`. Do not change the other files: they are replaced when marked.
- The program must compile with `-Wall -Werror`, print exactly the output at the end of `main.cpp`, and have no memory errors or leaks under valgrind.

## Build and upload

In the `A_3` folder, run `make A_3`. Upload only `A_3.cpp`.
