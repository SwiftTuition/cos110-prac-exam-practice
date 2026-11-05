#include <iostream>

#include "Item.h"
#include "Menu.h"

using namespace std;

int main() {
    Menu a(3);
    a + new Item('S', "Garlic bread", 45.5) + new Item('M', "Beef burger", 120);

    Menu b(a);
    cout << "a:" << endl << a;
    cout << "b, made with Menu b(a):" << endl << b;

    a + new Item('D', "Malva pudding", 60);
    cout << "a after adding Malva pudding:" << endl << a;
    cout << "b has not changed:" << endl << b;

    Menu c = b;
    cout << "c, made with Menu c = b:" << endl << c;

    Menu empty(2);
    Menu d(empty);
    cout << "d, a copy of an empty menu:" << endl << d;
    return 0;
}
/*
ExpectedOutput:
*/
/*
a:
Menu (max 3):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] empty
b, made with Menu b(a):
Menu (max 3):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] empty
a after adding Malva pudding:
Menu (max 3):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] Malva pudding (D) R60
b has not changed:
Menu (max 3):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] empty
c, made with Menu c = b:
Menu (max 3):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] empty
d, a copy of an empty menu:
Menu (max 2):
  [0] empty
  [1] empty
*/
