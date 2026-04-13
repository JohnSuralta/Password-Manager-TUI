#ifndef UTILS_H
#define UTILS_H

#include <string>

// COLORS
const std::string RESET = "\033[0m";
const std::string GREEN = "\033[32m";
const std::string RED = "\033[31m";

// clear after each continue
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

// functions

void runMessageAnimation(std::string message, int padding, int msPerPeriod);
void printPressEnterToContinue();


#endif
