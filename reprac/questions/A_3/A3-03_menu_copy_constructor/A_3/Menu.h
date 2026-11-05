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
    Menu(const Menu& other);
    ~Menu();
    Menu& operator+(Item* item);
    Item findFirst(string type);
    Item findLast(string type);
    float averagePrice(string type);
    int numberAbove(string type, float value);
    int numberBelow(string type, float value);
    int numberEqual(string type, float value);

    friend ostream& operator<<(ostream& out, const Menu& menu);
};

#endif
