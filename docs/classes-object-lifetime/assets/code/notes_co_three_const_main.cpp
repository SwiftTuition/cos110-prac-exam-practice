#include <iostream>
#include <string>

class Book {
 private:
  std::string title;

 public:
  Book(std::string title) : title(title) {}
  std::string getTitle() const {
    return title;
  }
  void setTitle(std::string title) {
    this->title = title;
  }
};

class Shelf {
 private:
  Book first;
  int count;

 public:
  Shelf() : first("none"), count(0) {}
  void add(const Book& book);
  const Book& getFirst() const;
  int getCount() const;
};

void Shelf::add(const Book& book) {
  if (count == 0) {
    first = book;
  }
  count++;
}

const Book& Shelf::getFirst() const {
  return first;
}

int Shelf::getCount() const {
  return count;
}

int main() {
  Shelf shelf;
  Book dune("Dune");
  shelf.add(dune);
  shelf.add(Book("Emma"));
  std::cout << shelf.getFirst().getTitle() << " " << shelf.getCount() << std::endl;
  return 0;
}
