#include "database.h"
#include "utils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// constructor
database::database(std::string name) : fileName(name) {}

/*
 * @brief adds all user generated passwords in program instance
 * * pass by reference for better memory conservation
 * @param passwordUser  instance of user class to use getUserPassword method
 */
void database::addUserEntry(const user &passwordUser) {
  std::ifstream inFile(fileName);
  bool requiresHeader = true;
  if (inFile.is_open()) {
    // if there are chars in the file then no header
    if (inFile.peek() != std::ifstream::traits_type::eof()) {
      requiresHeader = false;
    }

    inFile.close();
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
    std::cout << RED << "ERROR:" << RESET << "Could not find database"
              << std::endl;
  }
}

/*
 * @brief removes all ids, passwords, and timestamps in database
 * * included animations and colors for 'processing' effect
 */

void database::deleteAllEntrys() {
  std::ofstream outFile(fileName);

  if (outFile.is_open()) {
    // reinitialize headers
    outFile << "ID,Password,Timestamp" << std::endl;
    outFile.close();

    // animations
    runMessageAnimation("Clearing IDs", 45, 500);
    runMessageAnimation("Clearing Passwords", 51, 500);
    runMessageAnimation("Clearing Timestamps", 52, 500);

    // success message
    std::cout << "\n\n"
              << std::setw(44) << GREEN << "SUCCESS!" << RESET << "\n\n"
              << std::endl;
  } else {
    // error message
    std::cout << std::setw(35) << RED << "ERROR:" << RESET
              << " Could not access database" << std::endl;
  }

  printPressEnterToContinue();
}

/*
 * @brief prints a tabular representation of all the information in the database
 * * included animations and colors for 'processing' effect
 */
void database::printAllEntrys() {
  std::ifstream inFile(fileName);

  if (!inFile.is_open()) {
    std::cout << std::setw(35) << RED << "ERROR:" << RESET
              << " Could not access database" << std::endl;
    printPressEnterToContinue();
    return;
  }
  std::string currentFileLine;
  std::vector<std::vector<std::string>> allData;

  // read line by line storing substrings
  while (std::getline(inFile, currentFileLine)) {
    std::stringstream stringStream(currentFileLine);
    std::string value;
    std::vector<std::string> row;

    while (std::getline(stringStream, value, ',')) {
      // store each substring(value) delimited by ',' in row vector
      row.push_back(value);
    }

    // put each row in 2D vector all data
    allData.push_back(row);
  }

  if (allData.empty()) {
    std::cout << std::setw(33) << RED << "ERROR:" << RESET
              << " Database is currently empty";
    printPressEnterToContinue();

    return;
  }

  // animations
  runMessageAnimation("Fetching IDs", 45, 500);
  runMessageAnimation("Fetching Passwords", 51, 500);
  runMessageAnimation("Fetching Timestamps", 52, 500);
  std::cout << "\n\n"
            << std::setw(44) << GREEN << "SUCCESS!" << RESET << "\n\n"
            << std::endl;

  // upper border
  std::cout << std::setw(195)
            << "╔══════════════════════════════════════════════════════════════"
            << "════════════╗" << std::endl;

  // print headers
  std::cout << std::setw(9) << "║" << std::setw(6) << allData[0][0]
            << std::setw(7) << "║" << std::setw(19) << "PASSWORDS"
            << std::setw(13) << "║" << std::setw(21) << "TIMESTAMP"
            << std::setw(15) << "║" << std::endl;

  // print seperator
  std::cout << std::setw(195)
            << "║══════════════════════════════════════════════════════════════"
            << "════════════║" << std::endl;

  // print data
  for (int i = 1; i < allData.size(); i++) {
    const std::vector<std::string> row = allData[i];
    std::cout << std::setw(9) << "║" << std::setw(7) << row[0] << std::setw(6)
              << "║" << std::setw(24) << row[1] << std::setw(8) << "║"
              << std::setw(28) << row[2] << std::setw(8) << "║" << std::endl;
  }

  // print footer
  std::cout << std::setw(195)
            << "╚══════════════════════════════════════════════════════════════"
            << "════════════╝" << std::endl;

  printPressEnterToContinue();
}
