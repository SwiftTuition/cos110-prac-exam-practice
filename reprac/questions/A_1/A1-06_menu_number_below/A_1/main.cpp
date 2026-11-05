
#include <iostream>

#include "Exception.h"
#include "Item.h"
#include "Menu.h"

using namespace std;

void show(Menu& menu, string type, float value) {
    try {
        int count = menu.numberBelow(type, value);
        cout << type << " below R" << value << ": " << count << endl;
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
    Menu menu(6);
    menu + new Item('S', "Garlic bread", 45.5) + new Item('M', "Beef burger", 120);
    menu + new Item('M', "Veg curry", 95.5) + new Item('D', "Malva pudding", 60);
    menu + new Item('S', "Soup", 50);
    show(menu, "Main", 100);
    show(menu, "Main", 200);
    show(menu, "Main", 95.5);
    show(menu, "Starter", 50);
    show(menu, "Dessert", 60);
    show(menu, "Desserts", 60);
    return 0;
}
/*
ExpectedOutput:
*/
/*
Main below R100: 1
Main below R200: 2
NothingBelowMaximumValue caught: Exception: Nothing matching filter: below maximum value
Starter below R50: 1
NothingBelowMaximumValue caught: Exception: Nothing matching filter: below maximum value
InvalidType caught: Exception: Invalid type: Desserts
*/
