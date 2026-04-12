#ifndef USER_H
#define USER_H

#include <string>
#include <ctime>

class user {
  private:
    std::string password;
    std::string timeStamp;
    unsigned int id;
    static int globalCounter;
  public:
    user();
    void generatePassword();
};

#endif
