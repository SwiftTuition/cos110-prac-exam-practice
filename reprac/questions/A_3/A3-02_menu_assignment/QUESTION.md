Practice question based on the published re-practical scenario. The real exam's complete UML may differ.

# A3-02. Assignment operator: `Menu::operator=` (100)

Implement the assignment operator of the `Menu` class in `A_3.cpp`. After `a = b;`, menu `a` must be a deep copy of menu `b`: the same `maxSize`, and its own copy of every item, in the same slots.

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
- After `a = b;`, `a` has the same `maxSize` as `b`. Slot `i` of `a` holds a new copy of the item in slot `i` of `b`, or `NULL` if that slot of `b` is `NULL`.
- The items and the array that `a` held before must be freed.
- Changing `b` afterwards (for example adding an item) must not change `a`.
- `a = a;` must leave `a` unchanged. `a = b = c;` must work.

## Rules

- Write only this one function in `A_3.cpp`. Do not change the other files: they are replaced when marked.
- The program must compile with `-Wall -Werror`, print exactly the output at the end of `main.cpp`, and have no memory errors or leaks under valgrind.

## Build and upload

In the `A_3` folder, run `make A_3`. Upload only `A_3.cpp`.
