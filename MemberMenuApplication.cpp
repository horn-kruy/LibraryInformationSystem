#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "DataValidInput.cpp"
#include "MemberManager.cpp"
#include "OldMember.cpp"
#include "NewMember.cpp"
#include "Display.cpp"

using namespace std;
class MemberMenuApplication{
private:
    Display display;

    enum choiceMenu{
        EXIT, ADD, VIEW, UPDATE, DELETE, SEARCH, SORT, SAVE, LOAD
    };

public:
    void run(){
        MemberManager manager;
        int choice;

    bool done = false;
    while (!done) {
        display.displayMemberMenu();
        choice = DataValidInput::getIntInput("Enter your choice(0-8): ");
        cout << endl;
        try {
            switch (choice) {
                case ADD:{
                    bool addMore = true;
                    while(addMore){
                        int id;
                        string name;
                        string phoneNumber;
                        int type;

                        cout << "********* ADD MEMBER *********\n";

                        // Get and validate member id
                        while (true){
                            id = DataValidInput::getIntInput("Enter member id: ");
                            if (DataValidInput::validateNumber(id)) break;
                        }

                        // Get and validate member name
                        while (true){
                            name = DataValidInput::getStringInput("Enter member name: ");
                            if (DataValidInput::validateName(name)) break;
                        }

                        // Get and validate member phone number
                        while (true){
                            cout<<"Enter member phone number(start with 0 with 8 digit): ";
                            cin >> phoneNumber;
                            if (DataValidInput::validatePhoneNumber(phoneNumber)) {
                                break;  // Valid phone number, exit the loop
                            }
                             cout << "Invalid phone number. Please enter exactly 9 digits." << endl;
                        }

                        // Get and validate member type
                        type = DataValidInput::getIntInput("Enter 1 for Old member, 2 for New member: ");
                        manager.addMember(id, name, phoneNumber, type);

                        int more;
                        while (true) {
                            try {
                                more = DataValidInput::getIntInput("\nDo you want to add more member? (1 for yes, 2 for no): ");
                                cout << endl;
                                if (more == 1) {
                                    break;
                                } else if (more == 2) {
                                    addMore = false;
                                    break;
                                } else {
                                    throw invalid_argument("Invalid choice. Please enter 1 for yes or 2 for no.");
                                }
                            } catch (const invalid_argument& e) {
                                cout << "Error: " << e.what() << endl;
                            }
                        }
                    }
                    break;
                }

                case VIEW:{
                        cout << "********* VIEW MEMBER ********\n";

                        manager.viewMembers();
                    break;
                }

                case UPDATE:{
                        int id;
                        cout << "******** UPDATE MEMBER ********\n";
                        id = DataValidInput::getIntInput("Enter member id: ");
                        DataValidInput::validateNumber(id);

                        manager.updateMember(id);
                    break;
                }

                case DELETE:{
                        int id;
                        cout << "******** DELETE MEMBER *******\n";
                        id = DataValidInput::getIntInput("Enter member id: ");
                        DataValidInput::validateNumber(id);

                        manager.deleteMember(id);
                    break;
                }

                case SEARCH:{
                        int id;
                        cout << "******** Search Member *******\n";

                        manager.searchMember(id);
                    break;
                }

                case SORT:{
                        int sortOption;
                        cout << "********* Sort Member ********\n";

                        manager.sortMember();
                    break;
                }

                case SAVE:{
                        cout << "********* SAVE MEMBER ********\n";

                        manager.saveToFile("Members.txt");
                        cout << "Data have saved successfully." << endl;
                    break;
                }

                case LOAD:{
                        cout << "********** LOAD MEMBER ********\n";

                        manager.loadFromFile("Members.txt");
                        cout << endl;
                    break;

                }

                case EXIT:
                        done = true;
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    }
};
