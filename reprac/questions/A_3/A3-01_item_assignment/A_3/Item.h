#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

using namespace std;

class Item {
   private:
    char type;
    string name;
    float price;

   public:
    Item(char type, string name, float price);
    Item(const Item& other);
    ~Item();
    Item& operator=(const Item& other);
    char getType() const;
    string getName() const;
    float getPrice() const;

    friend ostream& operator<<(ostream& out, const Item& item);
};

#endif
