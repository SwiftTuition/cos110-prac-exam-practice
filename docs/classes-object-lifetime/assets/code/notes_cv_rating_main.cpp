#include <iostream>

class Rating {
 private:
  int stars;

 public:
  Rating(int stars) : stars(stars) {
    std::cout << "Rating(" << stars << ")" << std::endl;
  }
  int getStars() const {
    return stars;
  }
};

void review(const Rating& r) {
  std::cout << "review " << r.getStars() << std::endl;
}

int main() {
  review(5);
  return 0;
}
