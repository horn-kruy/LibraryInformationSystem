#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "DataValidInput.cpp"
#include "BookManager.cpp"
#include "OldBook.cpp"
#include "NewBook.cpp"
#include "Display.cpp"

using namespace std;
class BookMenuApplication{
private:
    Display display;

    enum choiceMenu{
        EXIT, ADD, VIEW, UPDATE, DELETE, SEARCH, SORT, SAVE, LOAD
    };

public:
    void run(){
        BookManager manager;
        int choice;

    bool done = false;
    while (!done) {
        display.displayBookMenu();
        choice = DataValidInput::getIntInput("Enter your choice(0-8): ");
        cout << endl;
        try {
            switch (choice) {
                case ADD:{
                    bool addMore = true;
                    while(addMore){
                        int id;
                        string titleName;
                        string authorName;
                        int year;
                        int type;

                        cout << "********** ADD BOOK **********\n\n";

                        // Get and validate book id
                        while(true){
                            id = DataValidInput::getIntInput("Enter book id: ");
                            if (DataValidInput::validateNumber(id)) break;
                        }

                        // Get and validate book title name
                        while(true){
                            titleName = DataValidInput::getStringInput("Enter book title name: ");
                            if (DataValidInput::validateName(titleName)) break;
                        }

                        // Get and validate book author name
                        while(true){
                            authorName = DataValidInput::getStringInput("Enter book author name: ");
                            if (DataValidInput::validateName(authorName)) break;
                        }
                        
                        // Get and validate book year
                        while(true){
                            year = DataValidInput::getIntInput("Enter book year: ");
                            if (DataValidInput::validateNumber(year)) break;
                        }

                        // Get and validate book type
                        type = DataValidInput::getIntInput("Enter 1 for Old book, 2 for New book: ");
                        manager.addBook(id, titleName, authorName, year, type);

                        int more;
                        while (true) {
                            try {
                                more = DataValidInput::getIntInput("Do you want to add more book? (1 for yes, 2 for no): ");
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
                        cout << "********** VIEW BOOk *********\n";

                        manager.viewBooks();
                    break;
                }

                case UPDATE:{
                        int id;
                        cout << "********* UPDATE BOOK ********\n";
                        id = DataValidInput::getIntInput("Enter book id: ");
                        DataValidInput::validateNumber(id);

                        manager.updateBook(id);
                    break;
                }

                case DELETE:{
                        int id;
                        cout << "********* DELETE BOOK ********\n";
                        id = DataValidInput::getIntInput("Enter book id: ");
                        DataValidInput::validateNumber(id);

                        manager.deleteBook(id);
                    break;
                }

                case SEARCH:{
                        int id;
                        cout << "********* Search Book *********\n";

                        manager.searchBook(id);
                    break;
                }

                case SORT:{
                        int sortOption;
                        cout << "********** Sort Book **********\n";

                        manager.sortBook();
                    break;
                }

                case SAVE:{
                        cout << "************ SAVE BOOK ***********\n";

                        manager.saveToFile("Books.txt");
                        cout << "Data have saved successfully." << endl;
                    break;
                }

                case LOAD:{
                        cout << "************ LOAD BOOK ***********\n";

                        manager.loadFromFile("Books.txt");
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
