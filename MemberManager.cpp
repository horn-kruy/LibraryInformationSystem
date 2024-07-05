#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <fstream>
#include "DataValidInput.cpp"
#include "MemberRepository.cpp"
#include "Member.cpp"
#include "OldMember.cpp"
#include "NewMember.cpp"
#include "Display.cpp"
#include <sstream>

using namespace std;
class MemberManager : public MemberRepository{
private:
    vector<Member*> members;
    Display display;

    Member* findMemberById(int id) {
        auto it = find_if(members.begin(), members.end(), [id](Member* member) {
            return member->getId() == id;
        });
        return (it != members.end()) ? *it : nullptr;
    }

public:  
    ~MemberManager() {
        for (auto member : members) {
            delete member;
        }
    }

    void addMember(int id, string name, string phoneNumber, int type) {
        if (type == 1) {
            members.push_back(new OldMember(id, name, phoneNumber));
        } else if (type == 2) {
            members.push_back(new NewMember(id, name, phoneNumber));
        } else {
            throw invalid_argument("Invalid member type.");
        }

        cout << "Member have added successfully.\n";
    }

    void viewMembers() {
        if (members.empty()) {
            throw invalid_argument("No member available.\n");
            return;
        }

        display.displayMemberHeader();
        for (const auto& member : members) {
            member->displayMember();
        }
        cout << endl;
    }

    void updateMember(int id) {
        Member* member = findMemberById(id);
        if (member == nullptr) {
            throw invalid_argument("Member have not found.\n");
            return;
        }

        display.displayMemberHeader();
        member->displayMember();
        int choice;
        cout << "What do you want to update?\n";
        cout << "1. Id\n";
        cout << "2. Name\n";
        cout << "3. Phone Number\n";
        cout << "4. Type\n";
        cout << "0. Back to Member Menu\n";
        cout << "***************************\n";
        choice = DataValidInput::getIntInput("Enter your choice(0-4): ");

        enum choiceUpdateMember{
            EXIT, ID, NAME, PHONENUMBER, TYPE
        };
        switch (choice) {
            case ID:{
                    cout << "\n~~~~~~ UPDATE ID ~~~~~~\n";
                    int newId = DataValidInput::getIntInput("Enter new id: ");
                    member->setId(newId);
                break;
            }

            case NAME:{
                    cout << "\n~~~~~ UPDATE NAME ~~~~~\n";
                    string newName = DataValidInput::getStringInput("Enter new name: ");
                    member->setName(newName);
                break;
            }

            case PHONENUMBER:{
                    cout << "\n~ UPDATE PHONE NUMBER ~\n";
                    string newPhoneNumber;
                    cout << ("Enter new phone number(start with 0 with 8 digit): ");
                    cin >> newPhoneNumber;

                    if(DataValidInput::validatePhoneNumber(newPhoneNumber)){
                        break;
                    }else{
                        cout << "Invalid phone number. Please enter exactly 9 digits." << endl;
                    }

                    member->setPhoneNumber(newPhoneNumber);
                break;
            }

            case TYPE:{
                    cout << "\n~~~~~ UPDATE TYPE ~~~~~\n";
                    int newType = DataValidInput::getIntInput("Enter 1 for Old Book, 2 for New Book: ");
                    if(newType == 1){
                        member = new OldMember(member->id, member->name, member->phoneNumber);
                    }else if(newType == 2){
                        member = new NewMember(member->id, member->name, member->phoneNumber);
                    }else{
                        throw invalid_argument("Invalid member type.");
                    }
                break;
            }

            case 0:{
                    cout << "Exit from update process.\n";
                break;
            }

            default:
                cout << "Invalid choice. Please try again.\n";
                return;
        }

        cout << "Member have updated successfully.\n\n";
    }

    void deleteMember(int id) {
        Member* member = findMemberById(id);
        if(member == nullptr){
            throw invalid_argument("Member have not found.\n");
        }

        display.displayMemberHeader();
        member->displayMember();
        int comfirm = DataValidInput::getIntInput("Are you sure you want to delete this member? (1 for yes, 2 for no): ");
        if(comfirm == 1){
            auto it = remove_if(members.begin(), members.end(), [id](Member* member) {
                if (member->getId() == id) {
                    delete member;
                    return true;
                }
                return false;
            });

            if (it != members.end()) {
                members.erase(it, members.end());
                cout << "Member have deleted successfully.\n";
            } else {
                throw invalid_argument("Member have not found in the list.");
            }
        }else{
            cout << "Member have canceled delete.\n";
        }
    }

    void searchMember(int id){
        id = DataValidInput::getIntInput("Enter member id: ");
        DataValidInput::validateNumber(id);
        Member* member = findMemberById(id);
            if (member == nullptr) {
            cout << "No member available.\n";
        } else {
            cout << "Search results:\n";
            display.displayMemberHeader();
            member->displayMember();
        }

    }
    void sortMember(){
        cout << "Sort book by: \n";
        cout << "1.Id\n";
        cout << "2.Name\n";
        int choice = DataValidInput::getIntInput("Enter your choice(1-2): ");
        cout << endl;

        enum choiceSortMember{
            ID = 1, NAME
        };
        switch(choice){
            case ID:
                    sort(members.begin(), members.end(), [](Member* a, Member* b) {
                        return a->getId() < b->getId();
                    });
                    cout << "Member sorted by id.\n" << endl;
                break;

            case NAME:
                    sort(members.begin(), members.end(), [](Member* a, Member* b) {
                        return a->getName() < b->getName();
                    });
                    cout << "Member sorted by name.\n" << endl;
                break;

            default:
                    cout << "Invalid sort option.\n";
                break;      
        }
        
        viewMembers();
    }

    void saveToFile(const string &filename) const{
        ofstream outFile(filename);
        if (!outFile){
            throw std::runtime_error("Cannot open file for writing");
        }
        for (const auto &member : members){
            outFile << member->id << " " << member->name << " " << member->phoneNumber << " " << member->getType() << endl;
        }
    }

    void loadFromFile(const string &filename){
        ifstream inFile(filename);
        if (!inFile){
            throw runtime_error("Cannot open file for reading");
        }

        members.clear();
        int id;
        string name;
        string phoneNumber;
        string type;
        bool hasMembers = false;

        string line;
        while (getline(inFile, line)){
            istringstream iss(line);
            if (!(iss >> id >> name >> phoneNumber >> type)){
                cerr << "Error parsing line: " << line << endl;
                continue;                                       
            }

            if (type == "Old_Member" || type == "Old" || type == "Old member"){
                members.push_back(new OldMember(id, name, phoneNumber));
                hasMembers = true;
            }else if (type == "New_Member" || type == "New" || type == "New member"){
                members.push_back(new NewMember(id, name, phoneNumber));
                hasMembers = true;
            }else{
                cerr << "Unknown member type in file: " << type << endl;
                continue;
            }
        }

        if (!hasMembers){
            cout << "No member available!\n";
        }else{
            cout << "List of all members:\n";
            cout << endl;
            display.displayMemberHeader();
            for (const auto &member : members){
                member->displayMember();
            }
            cout << endl;
            cout << "Data have loaded successfully" << endl;
        }
    }
};