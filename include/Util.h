//
// Created by root on 9/2/24.
//

#ifndef BEFOREDDLSERVER_UTIL_H
#define BEFOREDDLSERVER_UTIL_H

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <random>

class Util {
public:
    static std::string ReadFile(const std::string &filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + filePath);
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    static uint GenerateSixDigitRandomNumber() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> distr(100000, 999999);
        return distr(gen);
    }


    static bool IsValidPhoneNumber(const std::string &phoneNumber) {
        if (phoneNumber.length() != 11) {
            return false;
        }
        for (char c: phoneNumber) {
            if (!std::isdigit(c)) {
                return false;
            }
        }
        return true;
    }

};


#endif //BEFOREDDLSERVER_UTIL_H
