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
#include <string>
#include <cstdlib>
#include <fstream>
#include "user.h"

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

void printTitleScreen();
void displayActionMenu(bool isAdmin);
int getUserOption();
void generatePassword(user &passwordUser);
void getUserPassword(const user &passwordUser);
void updateDataBase(const user &passwordUser);

int main() {
  char adminResponse;
  bool isAdmin;
  int userOption;
  printTitleScreen();

  // getting admin status from user
  std::cout << std::setw(53) << "Are you an admin (y|n): ";
  while (!(std::cin >> adminResponse) ||
        (adminResponse != 'y' && adminResponse != 'n')) {
    std::cout << std::setw(56) << "Invalid repsonse, try again: ";
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
    system(CLEAR);
    printTitleScreen();
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
          generatePassword(passwordUser);
          updateDataBase(passwordUser);
          break;
        case 2:
          getUserPassword(passwordUser);
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
    std::cout << std::setw(56) << "Invalid option, try again: ";
    std::cin.clear();
    std::cin.ignore(10000, '\n');
  }

  return userOption;
}

void generatePassword(user &passwordUser) {
  passwordUser.generatePassword();
  std::cout << std::setw(48) << "Generating password";
  std::cout.flush();  // Force "Generating password" to show before the pause

  for (int i = 0; i < 3; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(750));
    std::cout << ".";
    std::cout.flush();  // Ensure each dot shows one by one
  }
  std::cout << " SUCCESS!\n\n" << std::endl;

  std::cout << std::setw(55) << "Press Enter To Continue...";
  std::cin.ignore();
  std::cin.get();
  std::cout << "\n\n";
}

void getUserPassword(const user &passwordUser) {
  std::cout << std::setw(43) << "Your password is: "
            << passwordUser.getUserPassword() << "\n" << std::endl;
  std::cout << std::setw(55) << "Press Enter To Continue...";
  std::cin.ignore();
  std::cin.get();
  std::cout << "\n\n";
}

void updateDataBase(const user &passwordUser) {
  std::string fileName = "passwordDatabase.csv";

  std::ifstream infile;
  bool fileExists = infile.good();

  if (fileExists) {
    // checks if any char in file
    if (infile.peek() != std::ifstream::traits_type::eof()) {
      fileExists = false;
    }
  }
  infile.close();


  std::ofstream outFile;
  outFile.open(fileName, std::ios::app);  // append mode

  if (outFile.is_open()) {
    if (!fileExists) {
      outFile << "ID,Password,Timestamp" << std::endl;
    }

    outFile << passwordUser.getUserID() << ","
            << passwordUser.getUserPassword() << ","
            << passwordUser.getPasswordTimeStamp()
            << std::endl;

    outFile.close();
  } else {
    std::cout << "ERROR: Could not find database";
  }
}
