#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <iomanip>

using namespace std;
class Member {
public:
    int id;
    string name;
    string phoneNumber;

    // constructor
    Member(){}
    Member(int id, string name, string phoneNumber):id(id), name(name), phoneNumber(phoneNumber){}

    // destructor
    virtual ~Member() = default;

    // Getter and Setter
    int getId(){
        return id;
    }
    string getName(){
        return name;
    }
    string getPhoneNumber(){
        return phoneNumber;
    }
    void setId(int id){
        this->id=id;
    }
    void setName(string name){
        this->name=name;
    }
    void setPhoneNumber(string phoneNumber){
        this->phoneNumber=phoneNumber;
    }

    virtual string getType() const = 0;

    virtual void displayMember() const {
        cout << left << " " << setw(12) << id 
             << setw(20) << name 
             << setw(30) << phoneNumber 
             << setw(13) << getType() << endl;
    }
};