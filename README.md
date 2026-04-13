## Password Manager TUI

This project emulates an enterprise password manager.

---

## Description

This project utilizes Object-Oriented Programming concepts like classes
and implements external C++ libraries like vector, fstream, sstream, and
string for the 'database'. Additionally it has a sleek ui created with
libraries like iomanip for tabular data creation and chrono + thread for
text 'loading' animations. Lastly, the user class has a password generator
that uses cstdlib for rand and ctime for seeding to generate a password of
length 20. This generator can yield 60^20 permutations, making brute force
attacks nearly impossible.

---

## Features

- Interactive admin/user menu
- Persistent read/write from a 'database'
- Baseline-entropy password generator
- Timestamp indicator for time of password creation
- Unique ID per user
- Error checking

---

## Error Checking
![Admin Error Check](https://github.com/JohnSuralta/Password-Manager-TUI/blob/main/Error%20Checking%20Demos/Admin%20Error%20Check.png?raw=true)
![No User Generated Passwords Check](https://github.com/JohnSuralta/Password-Manager-TUI/blob/main/Error%20Checking%20Demos/No%20User%20Generated%20Passwords%20Check.png?raw=true)
![Option Error Check](https://github.com/JohnSuralta/Password-Manager-TUI/blob/main/Error%20Checking%20Demos/Option%20Error%20Check.png?raw=true)
![Printing Passwords When Database Empty Check](https://github.com/JohnSuralta/Password-Manager-TUI/blob/main/Error%20Checking%20Demos/Printing%20Passwords%20When%20Database%20Empty%20Check.png?raw=true)





---

## Installation

- Clone the repo via "git clone https://github.com/JohnSuralta/Password-Manager-TUI ~/your_desired_directory"
- Go into the directory where you cloned the repo and run
  clang++ main.cpp utils.cpp database.cpp user.cpp -o passwordManager (clang)
  g++ main.cpp utils.cpp database.cpp user.cpp -o passwordManager.exe (GCC)
- Run and Enjoy the program
