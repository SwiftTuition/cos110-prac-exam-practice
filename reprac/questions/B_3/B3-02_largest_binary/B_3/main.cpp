#include <iostream>
#include <string>

#include "Binary.h"
#include "Templates.h"

using namespace std;

int main() {
    cout << largest(3, 7) << endl;
    cout << largest(2.5, 1.5) << endl;
    cout << largest(string("apple"), string("pear")) << endl;

    Binary x("0111");
    Binary y("1000");
    Binary big = largest(x, y);
    cout << "largest(" << x << ", " << y << "): " << big << endl;

    Binary small = largest(Binary("11"), Binary("0001"));
    cout << "largest(11, 0001): " << small << endl;

    Binary tie = largest(Binary("011"), Binary("11"));
    cout << "largest(011, 11): " << tie << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
7
2.5
pear
largest(0111, 1000): 1000
largest(11, 0001): 11
largest(011, 11): 011
*/
