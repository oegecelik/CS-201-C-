/*
Name: Orhun Ege Çelik
Course Code: CS 201
Section: 3
Student Number: 22202321
*/

#ifndef CONTENT
#define CONTENT

#include <iostream>
using namespace std;

class Content{
    public:
        Content();
        Content(const int id, const string& name);
        const int getId() const;
        const int getCreatorId() const;
        void setCreatorId(const int creatorId);

    private:
        int id;
        int creatorId;
        string name;
};

#endif