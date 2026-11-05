#include <iostream>

#include "Item.h"

using namespace std;

int main() {
    Item a('S', "Soup", 50);
    Item b('M', "Beef burger", 120);
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    a = b;
    cout << "after a = b, a: " << a << endl;
    cout << "type " << a.getType() << ", name " << a.getName() << ", price " << a.getPrice() << endl;

    a = a;
    cout << "after a = a, a: " << a << endl;

    Item c('D', "Malva pudding", 60);
    a = b = c;
    cout << "after a = b = c, a: " << a << endl;
    cout << "b: " << b << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
a: Soup (S) R50
b: Beef burger (M) R120
after a = b, a: Beef burger (M) R120
type M, name Beef burger, price 120
after a = a, a: Beef burger (M) R120
after a = b = c, a: Malva pudding (D) R60
b: Malva pudding (D) R60
*/
