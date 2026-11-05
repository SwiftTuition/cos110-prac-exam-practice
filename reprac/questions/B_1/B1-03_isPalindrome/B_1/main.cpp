#include <iostream>

#include "Binary.h"

using namespace std;

void show(Binary& b, int start, int end) {
    cout << b << " [" << start << ", " << end << "]: ";
    if (b.isPalindrome(start, end)) {
        cout << "palindrome" << endl;
    } else {
        cout << "not a palindrome" << endl;
    }
}

int main() {
    Binary a("1001");
    Binary b("1011");
    Binary c("10101");
    show(a, 0, 3);
    show(b, 0, 3);
    show(c, 0, 4);
    show(b, 0, 2);
    show(b, 1, 2);
    show(a, 0, 4);
    show(a, -1, 2);
    return 0;
}
/*
ExpectedOutput:
*/
/*
1001 [0, 3]: palindrome
1011 [0, 3]: not a palindrome
10101 [0, 4]: palindrome
1011 [0, 2]: palindrome
1011 [1, 2]: not a palindrome
1001 [0, 4]: not a palindrome
1001 [-1, 2]: not a palindrome
*/
