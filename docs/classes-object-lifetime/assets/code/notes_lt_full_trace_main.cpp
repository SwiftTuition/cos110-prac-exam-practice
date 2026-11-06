#include <iostream>
#include <string>

class Seat {
 private:
  int number;
  static int seatCount;

 public:
  Seat(int number = 0) : number(number) {
    seatCount++;
    std::cout << "  Seat " << number << " made, seatCount " << seatCount << std::endl;
  }
  ~Seat() {
    seatCount--;
    std::cout << "  Seat " << number << " gone, seatCount " << seatCount << std::endl;
  }
  static int getSeatCount() {
    return seatCount;
  }
};

int Seat::seatCount = 0;

class Bus {
 private:
  std::string route;
  Seat** seats;
  int numSeats;

 public:
  Bus(std::string route, int numSeats) : route(route), numSeats(numSeats) {
    std::cout << "  Bus " << route << " body starts" << std::endl;
    seats = new Seat*[numSeats];
    for (int i = 0; i < numSeats; i++) {
      seats[i] = new Seat(i + 1);
    }
  }
  ~Bus() {
    std::cout << "  ~Bus " << route << " starts" << std::endl;
    for (int i = 0; i < numSeats; i++) {
      delete seats[i];
    }
    delete[] seats;
  }
};

int main() {
  std::cout << "line 1: Seat spare(9);" << std::endl;
  Seat spare(9);
  std::cout << "line 2: Bus* b = new Bus(\"R5\", 2);" << std::endl;
  Bus* b = new Bus("R5", 2);
  std::cout << "line 3: count is " << Seat::getSeatCount() << std::endl;
  std::cout << "line 4: { Bus local(\"R7\", 1); }" << std::endl;
  {
    Bus local("R7", 1);
  }
  std::cout << "line 5: delete b;" << std::endl;
  delete b;
  std::cout << "line 6: count is " << Seat::getSeatCount() << std::endl;
  return 0;
}
