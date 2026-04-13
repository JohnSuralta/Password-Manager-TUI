#ifndef USER_H
#define USER_H

#include <string>
#include <ctime>

class user {
  private:
    std::string password;
    std::string timeStamp;
    unsigned int id;
  public:
    user();
    std::string getUserPassword() const;
    std::string getPasswordTimeStamp() const;
    void generatePassword();
    int getUserID() const;
};

#endif
