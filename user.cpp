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
  const int numChars = 76;
  const int passwordLen = 20;
  char passwordChars[numChars] = "~!@#$%^&*()_+-={}[]|\\;:\"<>,./?abcdefghijklmnopABCDEFGHIJKLMNOP0123456789";

  // seed
  std::srand(time(NULL));

  for (int i = 0; i < passwordLen; i++) {
    password.push_back(passwordChars[rand() % numChars]);
  }

  // set time password is assigned
  std::time_t now = std::time(nullptr);
  char *timePtr = std::ctime(&now);
  timeStamp = timePtr;
}

std::string user::getUserPassword() const {
  return password;
}

std::string user::getPasswordTimeStamp() const {
  return timeStamp;
}

int user::getUserID() const {
  return id;
}


