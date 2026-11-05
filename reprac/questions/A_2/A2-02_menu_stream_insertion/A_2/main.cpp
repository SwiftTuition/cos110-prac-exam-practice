
#include <iostream>

#include "Item.h"
#include "Menu.h"

using namespace std;

int main() {
    Menu menu(4);
    cout << menu;
    menu + new Item('S', "Garlic bread", 45.5) + new Item('M', "Beef burger", 120);
    cout << menu;
    menu + new Item('D', "Malva pudding", 60) + new Item('M', "Veg curry", 95.5);
    cout << menu << "(end)" << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Menu (max 4):
  [0] empty
  [1] empty
  [2] empty
  [3] empty
Menu (max 4):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] empty
  [3] empty
Menu (max 4):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] Malva pudding (D) R60
  [3] Veg curry (M) R95.5
(end)
*/
