#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "BookMenuApplication.cpp"
#include "MemberMenuApplication.cpp"
#include "DataValidInput.cpp"
#include "Login.cpp"

using namespace std;
class Library : public Login{
private: 
    Display display;
public:
    void run()
    {
        if (!login())
        {
            cout << "Maximum login attempts reached. Exiting...\n";
            return;
        }

        int choice;
        cout.setf(ios::fixed | ios::showpoint);
        cout << setprecision(2);

        do
        {
            display.displayMainMenu();
            cout << endl;
            choice = DataValidInput::getIntInput("Enter your choice(0-2): ");
            cout << endl;
            
            switch (choice)
            {
            case 1:
                    BookMenuApplication bookApp;
                    bookApp.run();
                break;

            case 2:
                    MemberMenuApplication memberApp;
                    memberApp.run();
                break;

            case 0:
                    cout << "Thanks for using my program.\n";
                break;

            default:
                    cout << "\aInvalid choice. Please try again.\n";
            }
        } while (choice != 0);
    }
};