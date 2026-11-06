#include <iostream>

class Circle {
 private:
  double radius;

 public:
  Circle() {
    radius = 0;
    std::cout << "default" << std::endl;
  }
  Circle(double r) {
    radius = r;
    std::cout << "parameterised " << radius << std::endl;
  }
  Circle(const Circle& other) {
    radius = other.radius;
    std::cout << "copy " << radius << std::endl;
  }
};

int main() {
  Circle c1;
  Circle c2(5.5);
  Circle c3(c2);
  Circle* c4 = new Circle(2);
  delete c4;
  return 0;
}
