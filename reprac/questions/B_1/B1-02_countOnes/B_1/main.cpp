#include <iostream>

#include "Binary.h"

using namespace std;

int main() {
    Binary a("10110");
    cout << a << " from index 0: " << a.countOnes(0) << endl;
    cout << a << " from index 2: " << a.countOnes(2) << endl;
    cout << a << " from index 4: " << a.countOnes(4) << endl;
    cout << a << " from index 5: " << a.countOnes(5) << endl;
    cout << a << " from index -1: " << a.countOnes(-1) << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
10110 from index 0: 3
10110 from index 2: 2
10110 from index 4: 0
10110 from index 5: 0
10110 from index -1: 0
*/
