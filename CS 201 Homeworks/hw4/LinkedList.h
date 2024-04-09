/*
Name: Orhun Ege Çelik
Course Code: CS 201
Section: 3
Student Number: 22202321
*/

#ifndef LINKED_LIST
#define LINKED_LIST
#include "Node.h"
#include <iostream>
using namespace std;

template<class ItemType>
class LinkedList{
    private:  
        int itemCount;
    public:
        Node<ItemType>* headPtr;

        LinkedList();
        LinkedList(const LinkedList& aList);
        ~LinkedList();
        LinkedList& operator = (const LinkedList& aList);

        void clear();
        
        Node<ItemType>* getNodeWithName(string name) const;
        bool insert(const string& name, const double prob);
        bool remove(const string oldEntryID);
};
#endif