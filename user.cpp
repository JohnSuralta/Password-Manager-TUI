#include "user.h"
#include <ctime>
#include <string>

// for id
int user::globalCounter = 1000;

// unique id for each user
user::user() {
  id = globalCounter++;
}

// generate password and time stamp for user
void user::generatePassword() {
  password = "";
  const int numChars = 62;
  const int passwordLen = 20;
  char passwordChars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

  // seed
  std::srand(time(NULL));

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
  if (password.empty()) {
    return "Unavailable";
  } else {
    return password;
  }
}

std::string user::getPasswordTimeStamp() const {
  return timeStamp;
}

int user::getUserID() const {
  return id;
}


