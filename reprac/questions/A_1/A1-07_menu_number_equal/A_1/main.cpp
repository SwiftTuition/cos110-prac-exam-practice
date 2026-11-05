
#include <iostream>

#include "Exception.h"
#include "Item.h"
#include "Menu.h"

using namespace std;

void show(Menu& menu, string type, float value) {
    try {
        int count = menu.numberEqual(type, value);
        cout << type << " equal to R" << value << ": " << count << endl;
    } catch (InvalidType& e) {
        cout << "InvalidType caught: ";
        e.printException();
    } catch (NothingAboveMinimumValue& e) {
        cout << "NothingAboveMinimumValue caught: ";
        e.printException();
    } catch (NothingBelowMaximumValue& e) {
        cout << "NothingBelowMaximumValue caught: ";
        e.printException();
    } catch (NothingMatchingFilter& e) {
        cout << "NothingMatchingFilter caught: ";
        e.printException();
    } catch (Exception& e) {
        cout << "Exception caught: ";
        e.printException();
    }
}

int main() {
    Menu menu(7);
    menu + new Item('S', "Garlic bread", 45.5) + new Item('M', "Beef burger", 120);
    menu + new Item('M', "Veg curry", 95.5) + new Item('D', "Malva pudding", 60);
    menu + new Item('S', "Soup", 50) + new Item('M', "Pap and wors", 95.5);
    show(menu, "Main", 95.5);
    show(menu, "Main", 120);
    show(menu, "Main", 100);
    show(menu, "Dessert", 45.5);
    show(menu, "Starter", 45.5);
    show(menu, "Snack", 45.5);
    return 0;
}
/*
ExpectedOutput:
*/
/*
Main equal to R95.5: 2
Main equal to R120: 1
NothingMatchingFilter caught: Exception: Nothing matching filter: Main
NothingMatchingFilter caught: Exception: Nothing matching filter: Dessert
Starter equal to R45.5: 1
InvalidType caught: Exception: Invalid type: Snack
*/
