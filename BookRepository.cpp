#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "DataValidInput.cpp"
#include "Book.cpp"
#include "OldBook.cpp"
#include "NewBook.cpp"

using namespace std;
class BookRepository {
public:
    virtual void addBook(int id, string titleName, string authorName, int year, int type) = 0;
    virtual void viewBooks() = 0;
    virtual void updateBook(int id) = 0;
    virtual void deleteBook(int id) = 0;
    virtual void searchBook(int id) = 0;
    virtual void sortBook() = 0;
    virtual void saveToFile(const string &filename) const = 0;
    virtual void loadFromFile(const string &filename) = 0;
};
