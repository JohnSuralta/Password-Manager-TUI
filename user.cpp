#include "user.h"

#include <ctime>
#include <cstdlib>
#include <string>

// constructor: unique id for each user
user::user() {
  id = 1000 + (rand() & 9000);
}

/*
 * @brief generates a length 20 password consisting of a-z, A-Z, 0-9
 * * included timestamp assignment after password generation
 */
void user::generatePassword() {
  password = "";
  const int numChars = 62;
  const int passwordLen = 20;
  char passwordChars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

  for (int i = 0; i < passwordLen; i++) {
    password.push_back(passwordChars[rand() % numChars]);
  }

  // set time password is assigned
  std::time_t now = std::time(nullptr);
  char *timePtr = std::ctime(&now);
  timeStamp = timePtr;

  // prep for csv (remove '\n')
  if (!(timeStamp.empty()) &&
      (timeStamp.back() == '\n' || timeStamp.back() == '\r')) {
    timeStamp.pop_back();
  }
}

std::string user::getUserPassword() const {
  return password.empty() ? "Unavailable" : password;
}

std::string user::getPasswordTimeStamp() const {
  return timeStamp;
}

int user::getUserID() const {
  return id;
}


