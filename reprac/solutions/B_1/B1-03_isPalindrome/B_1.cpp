#include "Binary.h"

// True when the bits from start to end (both included) read the same in both directions.
bool Binary::isPalindrome(int start, int end) {
    // Invalid input: start or end outside the array.
    if (start < 0 || end >= size) {
        return false;
    }
    // Base case: one bit or no bits left in the range.
    if (start >= end) {
        return true;
    }
    // The two outer bits differ: not a palindrome.
    if (array[start] != array[end]) {
        return false;
    }
    // Recursive case: check the range without the two outer bits.
    return isPalindrome(start + 1, end - 1);
}
