#include <iostream>
#include "UserSession.h"

int main() {
  UserSession a("ayanda");
  UserSession* b = new UserSession("bongi");
  std::cout << UserSession::getActiveSessionCount() << std::endl;
  delete b;
  a.updateDuration(45);
  std::cout << UserSession::getActiveSessionCount() << std::endl;
  return 0;
}
