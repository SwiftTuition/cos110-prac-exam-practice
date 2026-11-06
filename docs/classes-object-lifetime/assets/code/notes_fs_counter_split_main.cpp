#include <iostream>
#include "Counter.h"

int main() {
  Counter c;
  c.increment(60);
  c.increment(50);
  std::cout << c.getCount() << std::endl;
  Counter::setMaxLimit(200);
  c.increment(50);
  std::cout << c.getCount() << std::endl;
  return 0;
}
