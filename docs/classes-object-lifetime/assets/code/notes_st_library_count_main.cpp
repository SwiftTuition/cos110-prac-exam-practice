#include <iostream>

class Library {
  static int libraryCount;

 public:
  Library() {
    libraryCount++;
  }
  ~Library() {
    libraryCount--;
  }
  static int howMany() {
    return libraryCount;
  }
};

int Library::libraryCount = 0;

int main() {
  std::cout << "A " << Library::howMany() << std::endl;
  Library a;
  Library b;
  std::cout << "B " << Library::howMany() << std::endl;
  {
    Library c;
    std::cout << "C " << Library::howMany() << std::endl;
  }
  std::cout << "D " << Library::howMany() << std::endl;
  Library* d = new Library;
  std::cout << "E " << Library::howMany() << std::endl;
  delete d;
  std::cout << "F " << Library::howMany() << std::endl;
  return 0;
}
