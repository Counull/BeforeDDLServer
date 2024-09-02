//
// Created by root on 9/2/24.
//

#ifndef BEFOREDDLSERVER_UTIL_H
#define BEFOREDDLSERVER_UTIL_H
#include <fstream>
#include <sstream>
#include <stdexcept>

class Util {
public:
   static std::string readFile(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + filePath);
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
};


#endif //BEFOREDDLSERVER_UTIL_H
