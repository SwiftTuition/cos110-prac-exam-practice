
#include <iostream>

#include "Exception.h"
#include "Item.h"
#include "Menu.h"

using namespace std;

void showLast(Menu& menu, string type) {
    try {
        Item item = menu.findLast(type);
        cout << "Last " << type << ": " << item << endl;
    } catch (InvalidType& e) {
        cout << "InvalidType caught: ";
        e.printException();
    } catch (StarterNotFound& e) {
        cout << "StarterNotFound caught: ";
        e.printException();
    } catch (MainNotFound& e) {
        cout << "MainNotFound caught: ";
        e.printException();
    } catch (DessertNotFound& e) {
        cout << "DessertNotFound caught: ";
        e.printException();
    } catch (Exception& e) {
        cout << "Exception caught: ";
        e.printException();
    }
}

int main() {
    Menu menu(6);
    menu + new Item('S', "Garlic bread", 45.5) + new Item('M', "Beef burger", 120);
    menu + new Item('M', "Veg curry", 95.5) + new Item('D', "Malva pudding", 60);
    menu + new Item('S', "Soup", 50);
    showLast(menu, "Starter");
    showLast(menu, "Main");
    showLast(menu, "Dessert");
    showLast(menu, "Drinks");

    Menu mainsOnly(3);
    mainsOnly + new Item('M', "Beef burger", 120);
    showLast(mainsOnly, "Main");
    showLast(mainsOnly, "Starter");
    showLast(mainsOnly, "Dessert");

    Menu empty(2);
    showLast(empty, "Main");
    return 0;
}
/*
ExpectedOutput:
*/
/*
Last Starter: Soup (S) R50
Last Main: Veg curry (M) R95.5
Last Dessert: Malva pudding (D) R60
InvalidType caught: Exception: Invalid type: Drinks
Last Main: Beef burger (M) R120
StarterNotFound caught: Exception: Item not found
DessertNotFound caught: Exception: Item not found
MainNotFound caught: Exception: Item not found
*/
