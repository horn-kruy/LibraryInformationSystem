#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <iomanip>

using namespace std;
class Book {
public:
    int id;
    string titleName;
    string authorName;
    int year;
    
    // constructor
    Book(){}
    Book(int id, string titleName, string authorName, int year):id(id), titleName(titleName), authorName(authorName), year(year){}

    // destructor
    virtual ~Book() = default;

    // Getter
    int getId(){
        return id;
    }
    string getTitleName(){
        return titleName;
    }
    string getAuthorName(){
        return authorName;
    }
    int getYear(){
        return year;
    }

    // Setter
    void setId(int id){
        this->id=id;
    }
    void setTitleName(string titleName){
        this->titleName=titleName;
    }
    void setAuthorName(string authorName){
        this->authorName=authorName;
    }
    void setYear(int year){
        this->year=year;
    }

    virtual string getType() const = 0;

    // display book when user want to view books
    virtual void displayBook() const {
        cout << left << " " << setw(12) << id 
             << setw(20) << titleName 
             << setw(20) << authorName 
             << setw(10) << year 
             << setw(13) << getType() << endl;
    }
};