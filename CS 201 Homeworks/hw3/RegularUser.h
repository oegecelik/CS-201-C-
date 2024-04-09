/*
Name: Orhun Ege Çelik
Course Code: CS 201
Section: 3
Student Number: 22202321
*/

#ifndef REGULAR_USER
#define REGULAR_USER

#include <iostream>
using namespace std;

class RegularUser{
    public:
        RegularUser();
        RegularUser(const int ID, const string& name);
        const int getId() const;
        const string getName() const;

    private:
        int ID;
        string name;
};

#endif