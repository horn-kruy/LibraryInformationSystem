#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <fstream>
#include "DataValidInput.cpp"
#include "BookRepository.cpp"
#include "Book.cpp"
#include "OldBook.cpp"
#include "NewBook.cpp"
#include "Display.cpp"
#include <sstream>

using namespace std;
class BookManager : public BookRepository{
private:
    vector<Book*> books;
    Display display;

    Book* findBookById(int id) {
        auto it = find_if(books.begin(), books.end(), [id](Book* book) {
            return book->getId() == id;
        });
        return (it != books.end()) ? *it : nullptr;
    }

public:  
    ~BookManager() {
        for (auto book : books) {
            delete book;
        }
    }

    void addBook(int id, string titleName, string authorName, int year, int type) {
        if (type == 1) {
            books.push_back(new OldBook(id, titleName, authorName, year));
        } else if (type == 2) {
            books.push_back(new NewBook(id, titleName, authorName, year));
        } else {
            throw invalid_argument("Invalid book type.");
        }

        cout << "Book have added successfully.\n\n";
    }

    void viewBooks() {
        if (books.empty()) {
            throw invalid_argument("No book available.\n");
            return;
        }

        display.displayBookHeader();
        for (const auto& book : books) {
            book->displayBook();
        }
    }

    void updateBook(int id) {
        Book* book = findBookById(id);
        if (book == nullptr) {
            throw invalid_argument("Book have not found.\n");
            return;
        }

        display.displayBookHeader();
        book->displayBook();
        int choice; 
        cout << "What do you want to update?\n";
        cout << "1. Id\n";
        cout << "2. Title Name\n";
        cout << "3. Author Name\n";
        cout << "4. Year\n";
        cout << "5. Type\n";
        cout << "0. Back to Book Menu\n";
        cout << "***************************\n";
        choice = DataValidInput::getIntInput("Enter your choice(0-5): ");

        enum choiceUpdateBook{
            EXIT, ID, TITLENAME, AUTHORNAME, YEAR, TYPE
        };
        switch (choice) {
            case ID:{
                    cout << "\n~~~~~~ UPDATE ID ~~~~~~\n";
                    int newId = DataValidInput::getIntInput("Enter new id: ");
                    book->setId(newId);
                break;
            }

            case TITLENAME:{
                    cout << "\n~~ UPDATE TITLE NAME ~~\n";
                    string newTitleName = DataValidInput::getStringInput("Enter new title name: ");
                    book->setTitleName(newTitleName);
                break;
            }

            case AUTHORNAME:{
                    cout << "\n~~ UPDATE AUTHOR NAME ~~\n";
                    string newAuthorName = DataValidInput::getStringInput("Enter new author name: ");
                    book->setAuthorName(newAuthorName);
                break;
            }

            case YEAR:{
                    cout << "\n~~~~~ UPDATE YEAR ~~~~~\n";
                    int newYear = DataValidInput::getIntInput("Enter new year: ");
                    book->setYear(newYear);
                break;
            }

            case TYPE:{
                    cout << "\n~~~~~ UPDATE TYPE ~~~~~\n";
                    int newType = DataValidInput::getIntInput("Enter 1 for Old Book, 2 for New Book: ");
                    if(newType == 1){
                        book = new OldBook(book->id, book->titleName, book->authorName, book->year);
                    }else if(newType == 2){
                        book = new NewBook(book->id, book->titleName, book->authorName, book->year);
                    }else{
                        throw invalid_argument("Invalid book type.");
                    }
                break;
            }

            case EXIT:{
                    cout << "Exit from update process.\n";
                break;
            }

            default:
                cout << "Invalid choice. Please try again.\n";
                return;
        }

        cout << "Book have updated successfully.\n\n";
    }

    void deleteBook(int id) {
        Book* book = findBookById(id);
        if(book == nullptr){
            throw invalid_argument("Book have not found.\n");
        }

        display.displayBookHeader();
        book->displayBook();
        int comfirm = DataValidInput::getIntInput("Are you sure you want to delete this book? (1 for yes, 2 for no): ");
        if(comfirm == 1){
            auto it = remove_if(books.begin(), books.end(), [id](Book* book) {
                if (book->getId() == id) {
                    delete book;
                    return true;
                }
                return false;
            });

            if (it != books.end()) {
                books.erase(it, books.end());
                cout << "Book have deleted successfully.\n";
            } else {
                throw invalid_argument("Book have not found in the list.");
            }
        }else{
            cout << "Book have canceled delete.\n";
        }
    }

    void searchBook(int id){
        id = DataValidInput::getIntInput("Enter book id: ");
        DataValidInput::validateNumber(id);
        Book* book = findBookById(id);
            if (book == nullptr) {
            cout << "No book available.\n";
        } else {
            cout << "Search results:\n";
            display.displayBookHeader();
            book->displayBook();
        }
        cout << endl;
    }
    void sortBook(){
        cout << "Sort book by: \n";
        cout << "1.Id\n";
        cout << "2.TitleName\n";
        cout << "3.Year\n";
        int choice = DataValidInput::getIntInput("Enter your choice(1-3): ");
        cout << endl;

        enum choiceSortBook{
            ID = 1, TITLENAME, YEAR
        };
        switch(choice){
            case ID:
                    sort(books.begin(), books.end(), [](Book* a, Book* b) {
                        return a->getId() < b->getId();
                    });
                    cout << "Book sorted by id.\n" << endl;
                break;

            case TITLENAME:
                    sort(books.begin(), books.end(), [](Book* a, Book* b) {
                        return a->getTitleName() < b->getTitleName();
                    });
                    cout << "Book sorted by title name.\n" << endl;
                break;

            case YEAR:
                    sort(books.begin(), books.end(), [](Book* a, Book* b) {
                        return a->getYear() < b->getYear();
                    });
                    cout << "Book sorted by year.\n" << endl;
                break;

            default:
                    cout << "Invalid sort option.\n";
                break;      
        }
        
        viewBooks();
    }

    void saveToFile(const string &filename) const{
        ofstream outFile(filename);
        if (!outFile){
            throw std::runtime_error("Cannot open file for writing");
        }
        for (const auto &book : books){
            outFile << book->id << " " << book->titleName << " " << book->authorName << " " << book->year << " " << book->getType() << endl;
        }
    }

    void loadFromFile(const string &filename){
        ifstream inFile(filename);
        if (!inFile){
            throw runtime_error("Cannot open file for reading");
        }

        books.clear();
        int id;
        string titleName;
        string authorName;
        int year;
        string type;
        bool hasBooks = false;

        string line;
        while (getline(inFile, line)){
            istringstream iss(line);
            if (!(iss >> id >> titleName >> authorName >> year >> type)){
                cerr << "Error parsing line: " << line << endl;
                continue;                                       
            }

            if (type == "Old_Book" || type == "Old" || type == "Old book"){
                books.push_back(new OldBook(id, titleName, authorName, year));
                hasBooks = true;
            }else if (type == "New_Book" || type == "New" || type == "New book"){
                books.push_back(new NewBook(id, titleName, authorName, year));
                hasBooks = true;
            }else{
                cerr << "Unknown book type in file: " << type << endl;
                continue;                                              
            }
        }

        if (!hasBooks){
            cout << "No book available!\n";
        }
        else{
            cout << "List of all books:\n";
            cout << endl;
            display.displayBookHeader();
            for (const auto &book : books)
            {
                book->displayBook();
            }
            cout << endl;
            cout << "Data have loaded successfully" << endl;
        }
    }
};