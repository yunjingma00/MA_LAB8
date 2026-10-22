#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Calculator.h"
#include "validator.h"
int main(){
    std::ifstream file("tests.txt");
    if (!file.is_open()){
        std::cerr << "error can't open the file" << std::endl;
        return 1;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)){
        lineNumber++;
        std::istringstream input(line);
        std::string a, b, extra;

        if (!(input >> a >> b) || (input >> extra)) {
            std::cout << "line " << lineNumber
                      << ": ERROR: expected exactly two numbers"
                      << std::endl;
            continue;
        }

        if (!isValidNumber(a) && !isValidNumber(b)) {
            std::cout << "line " << lineNumber
                      << ": ERROR: invalid number \"" << a
                      << "\" \"" << b << "\"" << std::endl;
            continue;
        }

        if (!isValidNumber(a)) {
            std::cout << "line " << lineNumber
                      << ": ERROR: invalid number \"" << a << "\""
                      << std::endl;
            continue;
        }

        if (!isValidNumber(b)) {
            std::cout << "line " << lineNumber
                      << ": ERROR: invalid number \"" << b << "\""
                      << std::endl;
            continue;
        }

        std::cout << "line " << lineNumber << ": "
                  << a << " + " << b << " = "
                  << addNumbers(a, b) << std::endl;
    }

    file.close();
    return 0;
}

