#include "Templates.h"

// Adding two binary strings is not allowed, so this specialisation throws
// (the same pattern as the L19 example for two chars).
template <>
Binary addition<Binary, Binary>(Binary v1, Binary v2) {
    throw "Cannot add two binary strings";
}
