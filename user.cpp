#include "user.h"
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>

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

  // password generating output
  std::cout << std::setw(48) << "Generating password";
  std::cout.flush(); // Force "Generating password" to show before the pause

  for (int i = 0; i < 3; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(750));
      std::cout << ".";
      std::cout.flush(); // Ensure each dot shows one by one
  }
  std::cout << " SUCCESS!";
}
