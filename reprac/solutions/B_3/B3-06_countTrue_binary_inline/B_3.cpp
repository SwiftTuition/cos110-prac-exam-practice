#ifndef B_3_CPP
#define B_3_CPP

#include "Templates.h"

// For a list of Binary strings, count every true bit in every string.
// inline: Templates.h includes this file, so this definition is compiled in every
// .cpp file that includes Templates.h (main.cpp and B_3.cpp). Without inline the
// link fails with "multiple definition".
template <>
inline int countTrue<Binary>(Node<Binary>* head) {
    int count = 0;
    Node<Binary>* curr = head;
    while (curr != NULL) {
        Binary& b = curr->getData();
        for (int i = 0; i < b.getSize(); i++) {
            if (b[i]) {
                count++;
            }
        }
        curr = curr->next();
    }
    return count;
}

#endif
