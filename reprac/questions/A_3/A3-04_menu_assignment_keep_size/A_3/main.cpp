#include <iostream>

#include "Item.h"
#include "Menu.h"

using namespace std;

int main() {
    cout << "--- 1. b has more items than a can hold ---" << endl;
    Menu a(2);
    a + new Item('S', "Soup", 50);
    Menu b(4);
    b + new Item('S', "Garlic bread", 45.5) + new Item('M', "Beef burger", 120) + new Item('D', "Malva pudding", 60);
    a = b;
    cout << "a after a = b:" << endl << a;

    cout << "--- 2. c has fewer items than b ---" << endl;
    Menu c(1);
    c + new Item('D', "Lemon tart", 55);
    b = c;
    cout << "b after b = c:" << endl << b;

    cout << "--- 3. the copy is deep ---" << endl;
    b + new Item('M', "Veg curry", 95.5);
    cout << "b after adding Veg curry:" << endl << b;
    cout << "c has not changed:" << endl << c;

    cout << "--- 4. self-assignment ---" << endl;
    a = a;
    cout << "a after a = a:" << endl << a;

    cout << "--- 5. chaining ---" << endl;
    a = b = c;
    cout << "a after a = b = c:" << endl << a;
    return 0;
}
/*
ExpectedOutput:
*/
/*
--- 1. b has more items than a can hold ---
a after a = b:
Menu (max 2):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
--- 2. c has fewer items than b ---
b after b = c:
Menu (max 4):
  [0] Lemon tart (D) R55
  [1] empty
  [2] empty
  [3] empty
--- 3. the copy is deep ---
b after adding Veg curry:
Menu (max 4):
  [0] Lemon tart (D) R55
  [1] Veg curry (M) R95.5
  [2] empty
  [3] empty
c has not changed:
Menu (max 1):
  [0] Lemon tart (D) R55
--- 4. self-assignment ---
a after a = a:
Menu (max 2):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
--- 5. chaining ---
a after a = b = c:
Menu (max 2):
  [0] Lemon tart (D) R55
  [1] empty
*/
