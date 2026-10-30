#include "Templates.h"

// Adding two employees makes no sense, so this specialization throws.
template <>
Employee addition<Employee, Employee>(Employee v1, Employee v2) {
    throw Exception("Cannot add two employees");
}
