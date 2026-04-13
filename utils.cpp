#include "utils.h"

#include <thread>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

/*
 * @brief runs ... message animation
 * @param message of std::string type defines what to print out before ...
 * @param padding std::setw() before message
 * @param msPerPeriod num milliseconds per . in ...
 */
void runMessageAnimation(std::string message, int padding, int msPerPeriod) {
  std::cout << std::setw(padding) << message;
  std::cout.flush();  // force message to print before animation

  for (int i = 0; i < 3; i++) {
    std::this_thread::sleep_for(std::chrono::milliseconds(msPerPeriod));
    std::cout << ".";
    std::cout.flush();  // force dots to print before next cout
  }

  std::cout << std::endl;
}

/*
 * @brief hangs and waits for user input
 * * prevents everything from printing out
 */
void printPressEnterToContinue() {
  std::cout << "\n\n";
  std::cout << std::setw(55) << "Press Enter To Continue...";
  std::cin.ignore();
  std::cin.get();
}
