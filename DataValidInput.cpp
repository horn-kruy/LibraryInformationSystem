#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <regex>
#include "Book.cpp"
#include "OldBook.cpp"
#include "NewBook.cpp"

using namespace std;

class DataValidInput {
public:
    static string getStringInput(const string& prompt) {
        string input;
        bool hasNumber;

        do {
            hasNumber = false;
            cout << prompt;
            getline(cin, input);

            // Check if input contains any digit
            for (char c : input) {
                if (isdigit(c)) {
                    hasNumber = true;
                    cout << "Invalid input. Please enter a string without numbers." << endl;
                    break;
                }
            }
        } while (hasNumber);

        return input;
    }

    static int getIntInput(const string& prompt) {
        int input;
        cout << prompt;
        while (!(cin >> input)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer: ";
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }

    static bool validateNumber(int number) {
        if (number <= 0) {
            cout << "Number must be a positive integer.\n";
            return false;
        }
        return true;
    }

    static bool validateName(const string& name) {
        regex namePattern("^[A-Za-z]+( [A-Za-z]+)*$");
        return regex_match(name, namePattern);
    }

    static bool validatePhoneNumber(const string& phoneNumber) {
        // Check if the length is exactly 9
        if (phoneNumber.length() != 9) {
            return false;
        }

        // Check if the first character is '0'
        if (phoneNumber[0] != '0') {
            return false;
        }

        // Check if all characters are digits
        for (char c : phoneNumber) {
            if (!isdigit(c)) {
                return false;
            }
        }

        return true;
    }
};
