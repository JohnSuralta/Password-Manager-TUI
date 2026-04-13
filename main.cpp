/*
Program: Final Project (Password Manager)
Name: John Suralta
Due: April 14, 2026
Description: TUI that allows employees or members to enter their name and a 4
digit ID, the program will assign them a password. If the user is an admin they
can print out all the employee's passwords.
Version: 1.0
*/

#include <ctime>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include "user.h"

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

void printEnterToContinue();
void printTitleScreen();
void displayActionMenu(bool isAdmin);
int getUserOption();
void generatePassword(user &passwordUser);
void getUserPassword(std::vector<std::string> userPasswordHistory);
void updateDataBase(const user &passwordUser);
void clearDatabase();
void printDatabase();

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

  srand(std::time(NULL));  // seeding for id and password
  std::vector<std::string>
    userPasswordHistory; // passwords generated in one session


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
          clearDatabase();
          break;
        case 2:
          printDatabase();
          break;
        case 3:
          break;
      }
    } else {
      switch (userOption) {
        case 1: {
          generatePassword(passwordUser);
          updateDataBase(passwordUser);
          userPasswordHistory.push_back(passwordUser.getUserPassword());
          break;
        }
        case 2:
          getUserPassword(userPasswordHistory);
          break;
        case 3:
          break;
      }
    }
  } while (userOption != 3);

  return 0;
}

void printEnterToContinue() {
  std::cout << "\n\n";
  std::cout << std::setw(55) << "Press Enter To Continue...";
  std::cin.ignore();
  std::cin.get();
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
  std::cout << "\n\n";

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
  std::cout << GREEN << "SUCCESS!" << RESET << "\n\n"<< std::endl;

  printEnterToContinue();
}

void getUserPassword(std::vector<std::string> userPasswordHistory) {
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

  printEnterToContinue();
}

void updateDataBase(const user &passwordUser) {
  std::string fileName = "passwordDatabase.csv";
  std::ifstream infile(fileName);
  bool requiresHeader = true;

  if (infile.is_open()) {
    // if there are chars in file then no header
    if (infile.peek() != std::ifstream::traits_type::eof()) {
      requiresHeader = false;
    }

    infile.close();
  }


  std::ofstream outFile(fileName, std::ios::app);  // open in append mode
  if (outFile.is_open()) {
    if (requiresHeader) {
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

void clearDatabase() {
  std::string fileName = "passwordDatabase.csv";

  std::ofstream outFile;
  outFile.open(fileName);

  if (outFile.is_open()) {
    outFile << "ID,Password,Timestamp" << std::endl;
    outFile.close();

    //  animations
    std::cout << std::setw(45) << "Clearing IDs";
    std::cout.flush();
    for (int i = 0; i < 3; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      std::cout << ".";
      std::cout.flush();
    }
    std::cout << std::endl;

    std::cout << std::setw(51) << "Clearing Passwords";
    std::cout.flush();
    for (int i = 0; i < 3; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      std::cout << ".";
      std::cout.flush();
    }
    std::cout << std::endl;

    std::cout << std::setw(52) << "Clearing Timestamps";
    std::cout.flush();
    for (int i = 0; i < 3; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      std::cout << ".";
      std::cout.flush();
    }
    std::cout << std::endl;

    std::cout << "\n\n" << std::setw(44) << GREEN << "SUCCESS!"
              << RESET <<  "\n\n" << std::endl;
  } else {
    std::cout << std::setw(35) << RED << "ERROR:" << RESET
              << " Could not acces database" << std::endl;
  }

  std::cout << std::setw(55) << "Press Enter To Continue...";
  std::cin.ignore();
  std::cin.get();
  std::cout << "\n\n";
}

void printDatabase() {
  std::string fileName = "passwordDatabase.csv";
  std::string currentFileLine;

  std::ifstream inFile;
  inFile.open(fileName);

  std::vector<std::vector<std::string>> allData;


  // read each item and store into row vector
  while (std::getline(inFile, currentFileLine)) {
    std::stringstream stringStream(currentFileLine);
    std::string value;
    std::vector<std::string> row;

    while (std::getline(stringStream, value, ',')) {
      // store each substring(value) (delimited by ',') in row
      row.push_back(value);
    }

    // put each row in all data
    allData.push_back(row);
  }

  // loading database animation
  if (inFile.is_open()) {
    std::cout << std::setw(45) << "Fetching IDs";
    std::cout.flush();
    for (int i = 0; i < 3; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      std::cout << ".";
      std::cout.flush();
    }
    std::cout << std::endl;

    std::cout << std::setw(51) << "Fetching Passwords";
    std::cout.flush();
    for (int i = 0; i < 3; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      std::cout << ".";
      std::cout.flush();
    }
    std::cout << std::endl;

    std::cout << std::setw(52) << "Fetching Timestamps";
    std::cout.flush();
    for (int i = 0; i < 3; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      std::cout << ".";
      std::cout.flush();
    }
    std::cout << std::endl;

    std::cout << "\n\n" << std::setw(44) << GREEN << "SUCCESS!"
              << RESET <<  "\n\n" << std::endl;

  } else {
    std::cout << std::setw(35) << RED << "ERROR:" << RESET
              << " Could not acces database" << std::endl;
  }

  // upper border
  std::cout << std::setw(195)
    << "╔══════════════════════════════════════════════════════════════"
    << "════════════╗" << std::endl;

  // print headers
  std::cout << std::setw(9)
            << "║" << std::setw(6) << allData[0][0] << std::setw(7) << "║"
            << std::setw(19) << "PASSWORDS" << std::setw(13) << "║"
            << std::setw(21) << "TIMESTAMP" << std::setw(15) << "║"
            << std::endl;

  // print seperator
  std::cout << std::setw(195)
            << "║══════════════════════════════════════════════════════════════"
            << "════════════║" << std::endl;

  // print data
  for (int i = 1; i < allData.size(); i++) {
    const std::vector<std::string> row = allData[i];

    std::cout << std::setw(9)
              << "║" << std::setw(7) << row[0] << std::setw(6) << "║"
              << std::setw(24) << row[1] << std::setw(8) << "║"
              << std::setw(28) << row[2] << std::setw(8) << "║"
              << std::endl;
  }

  // print footer
  std::cout << std::setw(195)
            << "╚══════════════════════════════════════════════════════════════"
            << "════════════╝" << std::endl;

  printEnterToContinue();
}
