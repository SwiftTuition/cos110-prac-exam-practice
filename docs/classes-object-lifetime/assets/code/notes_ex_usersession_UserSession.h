#ifndef USERSESSION_H
#define USERSESSION_H

#include <string>

class UserSession {
 public:
  UserSession(std::string username);
  ~UserSession();
  std::string getUsername() const;
  static int getActiveSessionCount();
  void updateDuration(int sessionDuration);

 private:
  std::string username;
  int sessionDuration;
  static int activeSessionCount;
};

#endif
