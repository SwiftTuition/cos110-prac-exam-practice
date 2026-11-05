#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>

#include "Exception.h"
#include "Item.h"

using namespace std;

class Menu {
   private:
    int maxSize;
    Item** items;

   public:
    Menu(int maxSize);
    ~Menu();
    Menu& operator+(Item* item);
    // Not in the published UML. Returns slot index of the array by reference; no range check.
    Item*& operator[](int index);

    friend ostream& operator<<(ostream& out, const Menu& menu);
};

#endif
