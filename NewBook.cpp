#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "Book.cpp"

using namespace std;
class NewBook : public Book {
    
public:
    NewBook(int id, const string& titleName, const string& authorName, int year)
        : Book(id, titleName, authorName, year) {}

    string getType() const override {
        return "New book";
    }
};