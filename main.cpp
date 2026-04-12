/*
Program: Final Project (Password Manager)
Name: John Suralta
Due: April 14, 2026
Description: TUI that allows employees or members to enter their name and a 4
digit ID, the program will assign them a password. If the user is an admin they
can print out all the employee's passwords.
Version: 1.0
*/

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "user.h"

void printTitleScreen();
void displayActionMenu(bool isAdmin);
int getUserOption();

int main() {
  char adminResponse;
  bool isAdmin;
  int userOption;
  printTitleScreen();

  // getting admin status from user
  std::cout << "\n\n" << std::setw(53) << "Are you an admin (y|n): ";
  while (!(std::cin >> adminResponse) ||
        (adminResponse != 'y' && adminResponse != 'n')) {
    std::cout << std::setw(58) << "Invalid repsonse, try again: ";
    std::cin.clear();
    std::cin.ignore(10000, '\n');
  }
  std::cout << std::endl;

  if (adminResponse == 'y') {
    isAdmin = true;
  } else {
    isAdmin = false;
  }

  user passwordUser;

  // printing option menu based on admin status
  do {
    displayActionMenu(isAdmin);
    userOption = getUserOption();
    if (isAdmin) {
      switch (userOption) {
        case 1:
        case 2:
          // print all passwords place holder
        case 3:
          break;
      }
    } else {
      switch (userOption) {
        case 1:
          passwordUser.generatePassword();
        case 2:
          // view password
        case 3:
          break;
      }
    }
  } while (userOption != 3);

  return 0;
}

void printTitleScreen() {
  std::cout << "▗▄▄▖  ▗▄▖  ▗▄▄▖ ▗▄▄▖▗▖ ▗▖ ▗▄▖ ▗▄▄▖ ▗▄▄▄     ▗▖  ▗▖ ▗▄▖ ▗▖  ▗▖ ▗▄▖  ▗▄▄▖▗▄▄▄▖▗▄▄▖ \n";
  std::cout << "▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▐▌  █    ▐▛▚▞▜▌▐▌ ▐▌▐▛▚▖▐▌▐▌ ▐▌▐▌   ▐▌   ▐▌ ▐▌\n";
  std::cout << "▐▛▀▘ ▐▛▀▜▌ ▝▀▚▖ ▝▀▚▖▐▌ ▐▌▐▌ ▐▌▐▛▀▚▖▐▌  █    ▐▌  ▐▌▐▛▀▜▌▐▌ ▝▜▌▐▛▀▜▌▐▌▝▜▌▐▛▀▀▘▐▛▀▚▖\n";
  std::cout << "▐▌   ▐▌ ▐▌▗▄▄▞▘▗▄▄▞▘▐▙█▟▌▝▚▄▞▘▐▌ ▐▌▐▙▄▄▀    ▐▌  ▐▌▐▌ ▐▌▐▌  ▐▌▐▌ ▐▌▝▚▄▞▘▐▙▄▄▖▐▌ ▐▌\n";
}

void displayActionMenu(bool isAdmin) {
  if (isAdmin) {
    std::cout << "\n" << std::setw(55) << "1. Clear Password Database" << std::endl;
    std::cout << std::setw(51) << "2. Print All Passwords"
              << std::endl;
    std::cout << std::setw(36) << "3. Exit" << std::endl;
  } else {
    std::cout << "\n" << std::setw(49) << "1. Generate Password" << std::endl;
    std::cout << std::setw(45) << "2. View Password" << std::endl;
    std::cout << std::setw(36) << "3. Exit" << std::endl;
  }
}

int getUserOption() {
  int userOption;

  std::cout << "\n" << std::setw(48) << "Enter your option: ";
  while (!(std::cin >> userOption) || userOption < 0 || userOption > 3) {
    std::cout << std::setw(56) << "Invalid option, try again: ";
    std::cin.clear();
    std::cin.ignore(10000, '\n');
  }

  return userOption;
}
