#ifndef DATABASE_H
#define DATABASE_H

#include "utils.h"
#include "user.h"
#include <string>

class database {
  private:
    std::string fileName;

  public:
    // constructor
    database(std::string fileName);

    // member functions
    void printAllEntrys();
    void deleteAllEntrys();
    void addUserEntry(const user &passwordUser);
};

#endif
