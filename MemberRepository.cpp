#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "DataValidInput.cpp"
#include "Member.cpp"
#include "OldMember.cpp"
#include "NewMember.cpp"

using namespace std;
class MemberRepository {
public:
    virtual void addMember(int id, string name, string phoneNumber, int type) = 0;
    virtual void viewMembers() = 0;
    virtual void updateMember(int id) = 0;
    virtual void deleteMember(int id) = 0;
    virtual void searchMember(int id) = 0;
    virtual void sortMember() = 0;
    virtual void saveToFile(const string &filename) const = 0;
    virtual void loadFromFile(const string &filename) = 0;
};
