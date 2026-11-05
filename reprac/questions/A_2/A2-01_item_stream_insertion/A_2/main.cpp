
#include <iostream>

#include "Item.h"
#include "Menu.h"

using namespace std;

int main() {
    Item bread('S', "Garlic bread", 45.5);
    Item burger('M', "Beef burger", 120);
    Item pudding('D', "Malva pudding", 60.25);
    cout << bread << endl;
    cout << burger << " | " << pudding << endl;

    Menu menu(3);
    menu + new Item(bread) + new Item('M', "Veg curry", 95.5);
    cout << menu;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Garlic bread (S) R45.5
Beef burger (M) R120 | Malva pudding (D) R60.25
Menu (max 3):
  [0] Garlic bread (S) R45.5
  [1] Veg curry (M) R95.5
  [2] empty
*/
