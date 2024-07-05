#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "Book.cpp"

using namespace std;
class OldBook : public Book {
    
public:
    OldBook(int id, const string& titleName, const string& authorName, int year)
        : Book(id, titleName, authorName, year) {}

    string getType() const override {
        return "Old book";
    }
};