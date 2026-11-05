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
    // Not in the published UML. Like operator+, but a full menu grows by one slot.
    Menu& operator+=(Item* item);

    friend ostream& operator<<(ostream& out, const Menu& menu);
};

#endif
