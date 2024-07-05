#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
//#include "StudentApplication.cpp"
//#include "CourseApplication.cpp"
#include "DataValidInput.cpp"
#include "Display.cpp"

using namespace std;
class Login{
private:
    Display display;
protected:
    bool login(){
        const string correctUsername = "kruy";
        const string correctPassword = "2024";
        const int maxAttempts = 3;
        int attempts = 0;

        string username;
        string password;

        while (attempts < maxAttempts){
            cout << endl;
            display.LoginDisplay();
    
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            cout << endl;

            if (username == correctUsername && password == correctPassword){
                cout << "You have login successfully.\n " << endl;

                return true;
            }else{
                attempts++;
                cout << "Invalid username or passeord. Attempt " << attempts << " of " << maxAttempts << ".\n";
            }
        }

        return false;
    }
};