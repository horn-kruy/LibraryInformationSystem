#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "Member.cpp"

using namespace std;
class OldMember : public Member {
    
public:
    OldMember(int id, const string& name, const string& phoneNumber)
        : Member(id, name, phoneNumber) {}

    string getType() const override {
        return "Old Member";
    }
};