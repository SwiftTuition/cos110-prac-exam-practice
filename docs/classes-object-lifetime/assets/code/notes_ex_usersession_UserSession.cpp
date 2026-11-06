#include "UserSession.h"

int UserSession::activeSessionCount = 0;

UserSession::UserSession(std::string username)
    : username(username), sessionDuration(0) {
  activeSessionCount++;
}

UserSession::~UserSession() {
  activeSessionCount--;
}

std::string UserSession::getUsername() const {
  return this->username;
}

int UserSession::getActiveSessionCount() {
  return activeSessionCount;
}

void UserSession::updateDuration(int sessionDuration) {
  this->sessionDuration = sessionDuration;
}
