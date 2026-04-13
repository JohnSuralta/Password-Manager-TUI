/*
Program: Final Project (Password Manager)
Name: John Suralta
Due: April 12, 2026
Description: TUI that allows employees or members to enter their name and a 4
digit ID, the program will assign them a password. If the user is an admin they
can print out all the employee's passwords.
Version: 1.0
*/

#include "utils.h"
#include "user.h"
#include "database.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>

void printTitleScreen();
void displayActionMenu(bool isAdmin);
int getUserOption();
void generatePassword(user &passwordUser);
void getUserPasswordHistory(const std::vector<std::string> &userPasswordHistory);

int main() {
  bool isAdmin = false;
  char adminResponse;
  int userOption;

  srand(std::time(NULL));  // seeding for id and password
  database db("passwordDatabase.csv");
  user passwordUser;

  std::vector<std::string>
    userPasswordHistory;  // passwords generated in one session


  // getting admin status from user
  printTitleScreen();
  std::cout << std::setw(53) << "Are you an admin (y|n): ";
  while (!(std::cin >> adminResponse) ||
        (adminResponse != 'y' && adminResponse != 'n')) {
    std::cout << std::setw(28) << RED << "ERROR:" << RESET
                               << " Invalid repsonse, try again: ";
    std::cin.clear();
    std::cin.ignore(10000, '\n');
  }
  std::cout << std::endl;

  if (adminResponse == 'y') {
    isAdmin = true;
  } else {
    isAdmin = false;
  }


  // printing option menu based on admin status
  do {
    system(CLEAR);
    printTitleScreen();
    displayActionMenu(isAdmin);
    userOption = getUserOption();
    if (isAdmin) {
      switch (userOption) {
        case 1:
          db.deleteAllEntrys();
          // clearDatabase();
          break;
        case 2:
          db.printAllEntrys();
          // printDatabase();
          break;
        case 3:
          break;
      }
    } else {
      switch (userOption) {
        case 1: {
          generatePassword(passwordUser);
          db.addUserEntry(passwordUser);
          userPasswordHistory.push_back(passwordUser.getUserPassword());
          break;
        }
        case 2:
          getUserPasswordHistory(userPasswordHistory);
          break;
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
  std::cout << "▐▌   ▐▌ ▐▌▗▄▄▞▘▗▄▄▞▘▐▙█▟▌▝▚▄▞▘▐▌ ▐▌▐▙▄▄▀    ▐▌  ▐▌▐▌ ▐▌▐▌  ▐▌▐▌ ▐▌▝▚▄▞▘▐▙▄▄▖▐▌ ▐▌\n\n\n";
}

void displayActionMenu(bool isAdmin) {
  std::cout << std::setw(62) << "╔═════════════ "
            << (isAdmin ? "ADMIN" : "USERS") << " DASHBOARD "
            << "══════════════╗" << std::endl;

  std::cout << std::setw(22) << "║" << std::string(44, ' ') << "║" << std::endl;

  if (isAdmin) {
    std::cout << std::setw(22) << "║"  << std::setw(36)
      << "[1] Clear Password Database" << std::setw(11) << "║" << std::endl;

    std::cout << std::setw(22) << "║" << std::setw(32)
              << "[2] Print All Passwords" << std::setw(15) << "║" << std::endl;
  } else {
    std::cout << std::setw(22) << "║" << std::setw(30)
              << "[1] Generate Password" << std::setw(17) << "║" << std::endl;

    std::cout << std::setw(22) << "║" << std::setw(26)
              << "[2] View Password" << std::setw(21) << "║" << std::endl;
  }

  std::cout << std::setw(22) << "║" << std::setw(17) << "[3] Exit"
            << std::setw(30) << "║" << std::endl;

  std::cout << std::setw(22) << "║" << std::string(44, ' ') << "║" << std::endl;

  std::cout << std::setw(22) << "╚";
  for (int i = 0; i < 44; i++) {
    std::cout << "═";
  }
  std::cout << "╝" << std::endl;
}


int getUserOption() {
  int userOption;

  std::cout << "\n" << std::setw(52) << "Enter your option: ";
  while (!(std::cin >> userOption) || userOption < 1 || userOption > 3) {
    std::cout << std::setw(32) << RED << "ERROR:" << RESET
              << "Invalid option, try again: ";
    std::cin.clear();
    std::cin.ignore(10000, '\n');
  }
  std::cout << "\n\n";

  return userOption;
}

void generatePassword(user &passwordUser) {
  passwordUser.generatePassword();
  runMessageAnimation("Generating Password:", 52, 750);
  std::cout << std::setw (44) << GREEN << "SUCCESS!" << RESET
            << "\n\n"<< std::endl;
  printPressEnterToContinue();
}

void getUserPasswordHistory(const std::vector<std::string> &userPasswordHistory) {
  if (userPasswordHistory.empty()) {
    std::cout << std::setw(34) << RED << "ERROR:" << RESET
              << " No generated passwords" << std::endl;
  } else {
    int passwordCounter = 0;
    std::cout << std::setw(57) << "Your Generated Passwords:\n" << std::endl;
    for (const auto& password : userPasswordHistory) {
      passwordCounter++;

      std::cout << std::setw(32) << "[" << passwordCounter << "]  " << password
                << std::endl;
    }
  }
  printPressEnterToContinue();
}

