#pragma once
#include <iostream>
#include <iomanip>

using namespace std;
class Display{
public:
        void displayBookHeader()  {
                cout << left << setw(13) << "|Id"
                << setw(20) << "Title Name"
                << setw(20) << "Author Name"
                << setw(10) << "Year"
                << setw(13) << "Type     |" << endl;
                cout << "-------------------------------------------------------------------------" <<endl;
        };

        void displayMemberHeader() {
                cout << left << setw(13) <<"|Id"
                << setw(20) << "Name"
                << setw(30) << "Phone Number" 
                << setw(13) << "Type      |" << endl;
                cout << "----------------------------------------------------------------------" <<endl;
        };

        void displayMainMenu(){
        cout <<"=============== Welcome to ===============\n";
        cout <<"======== Library Management System =======\n";
        cout <<"\n1. Book Management\n";
        cout <<"2. Member Management\n";
        cout <<"0. EXIT\n";
        cout <<"==========================================";
        };

        void displayBookMenu(){
                cout << "======== Book Management =======\n";
                cout << "\n1. Add Book\n";
                cout << "2. View Book\n";
                cout << "3. Update Book\n";
                cout << "4. Delete Book\n";
                cout << "5. Search Book\n";
                cout << "6. Sort Book\n";
                cout << "7. Save Data\n";
                cout << "8. Load Data\n";
                cout << "0. Back to Main Menu\n";
                cout << "================================\n";
        };

        void displayMemberMenu(){
                cout << "======= Member Management ======\n";
                cout << "\n1. Add Member\n";
                cout << "2. View Member\n";
                cout << "3. Update Member\n";
                cout << "4. Delete Member\n";
                cout << "5. Search Book\n";
                cout << "6. Sort Book\n";
                cout << "7. Save Data\n";
                cout << "8. Load Data\n";
                cout << "0. Back to Main Menu\n";
                cout << "================================\n";
        };

        void LoginDisplay(){
                cout << "============= Welcome to ==============\n";
                cout << "=========== log in section ============\n";
                cout << "\nPlease Enter your username and password\n";
                cout << "=======================================\n";
        };
};

// int main()
// {
//     displayBook();
//     displayMember();
//     displayMainMenu();
//     displayBookMenu();
//     displayMemberMenu();
//     LoginDisplay();

// }
