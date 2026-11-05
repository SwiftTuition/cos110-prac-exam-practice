#include <iostream>

#include "Item.h"
#include "Menu.h"

using namespace std;

int main() {
    cout << "--- 1. a = b, where b is bigger ---" << endl;
    Menu a(2);
    a + new Item('S', "Soup", 50);
    Menu b(4);
    b + new Item('S', "Garlic bread", 45.5) + new Item('M', "Beef burger", 120) + new Item('D', "Malva pudding", 60);
    cout << "a before:" << endl << a;
    cout << "b:" << endl << b;
    a = b;
    cout << "a after a = b:" << endl << a;

    cout << "--- 2. the copy is deep ---" << endl;
    b + new Item('M', "Veg curry", 95.5);
    cout << "b after adding Veg curry:" << endl << b;
    cout << "a has not changed:" << endl << a;

    cout << "--- 3. self-assignment ---" << endl;
    a = a;
    cout << "a after a = a:" << endl << a;

    cout << "--- 4. chaining ---" << endl;
    Menu c(1);
    c + new Item('D', "Lemon tart", 55);
    a = b = c;
    cout << "a after a = b = c:" << endl << a;
    cout << "b:" << endl << b;
    return 0;
}
/*
ExpectedOutput:
*/
/*
--- 1. a = b, where b is bigger ---
a before:
Menu (max 2):
  [0] Soup (S) R50
  [1] empty
b:
Menu (max 4):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] Malva pudding (D) R60
  [3] empty
a after a = b:
Menu (max 4):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] Malva pudding (D) R60
  [3] empty
--- 2. the copy is deep ---
b after adding Veg curry:
Menu (max 4):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] Malva pudding (D) R60
  [3] Veg curry (M) R95.5
a has not changed:
Menu (max 4):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] Malva pudding (D) R60
  [3] empty
--- 3. self-assignment ---
a after a = a:
Menu (max 4):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] Malva pudding (D) R60
  [3] empty
--- 4. chaining ---
a after a = b = c:
Menu (max 1):
  [0] Lemon tart (D) R55
b:
Menu (max 1):
  [0] Lemon tart (D) R55
*/
