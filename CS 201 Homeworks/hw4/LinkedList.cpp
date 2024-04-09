/*
Name: Orhun Ege Çelik
Course Code: CS 201
Section: 3
Student Number: 22202321
*/

#include "LinkedList.h"
#include "GraphEdge.h"
#include <iostream>
#include <cstddef>

using namespace std;

template<class ItemType>
LinkedList<ItemType>::LinkedList() : itemCount(0), headPtr(nullptr){}

template <class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList &aList)
{
    for(Node<ItemType>* curPtr = aList.headPtr; curPtr != nullptr; curPtr = curPtr->getNext()){
        insert(curPtr->getItem().getName(), curPtr->getItem().getProb());
        if(headPtr == nullptr){
            headPtr = curPtr;
        }
    }
    itemCount = aList.itemCount;    
}

template <class ItemType>
LinkedList<ItemType>::~LinkedList()
{
    clear();
}

template <class ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::operator=(const LinkedList<ItemType> &aList)
{
    for(Node<ItemType>* curPtr = aList.headPtr; curPtr != nullptr; curPtr = curPtr->getNext()){
        insert(curPtr->getItem().getName(), curPtr->getItem().getProb());
        if(headPtr == nullptr){
            headPtr = curPtr;
        }
    }
    itemCount = aList.itemCount;   
    return *this; 
}

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeWithName(string name) const{
    Node<ItemType>* curPtr = headPtr;
    for(int i = 1; i<=itemCount; i++){
        if(name==curPtr->getItem().getName()){
            return curPtr;
        }
        curPtr = curPtr->getNext();
    }
    return nullptr;
}

template<class ItemType>
bool LinkedList<ItemType>::insert(const string& name, const double prob){ // For contents, since they only exist within creators

    bool ableToInsert = true;
    Node<ItemType>* prevPtr = nullptr;
    Node<ItemType>* nextPtr = headPtr;
    Node<ItemType>* curPtr = headPtr;

    for(int i = 1; i<=itemCount; i++){
        if(name == curPtr->getItem().getName()){
            ableToInsert = false;
            return false;
        }
        if((nextPtr == nullptr) || (name < nextPtr->getItem().getName())){
            // Since the list is sorted, if the new ID is smaller than next, we will have found the correct index. 
            break;
        }
        prevPtr = nextPtr;
        nextPtr = nextPtr->getNext();
        curPtr = curPtr->getNext();
    }
    ItemType newItem(name, prob);
    Node<ItemType>* newNodePtr = new Node<ItemType>(newItem);
    if(prevPtr == nullptr){
        newNodePtr->setNext(headPtr);
        headPtr = newNodePtr;
    }
    else{
        newNodePtr->setNext(prevPtr->getNext());
        prevPtr->setNext(newNodePtr);
    }
    itemCount++;
    return ableToInsert;
}

template<class ItemType>
bool LinkedList<ItemType>::remove(const string name){
    bool ableToRemove = false;
    Node<ItemType>* prevPtr = nullptr;
    Node<ItemType>* curPtr = headPtr;

    for(int i = 1; i<=itemCount; i++){
        if(name == curPtr->getItem().getName()){
            if(curPtr == headPtr){
                headPtr = headPtr->getNext();
            }
            else{
                prevPtr->setNext(curPtr->getNext());
            }
            curPtr->setNext(nullptr);
            delete curPtr;
            curPtr = nullptr;
            itemCount--;
            ableToRemove = true;
            return ableToRemove;
        }
        prevPtr = curPtr;
        curPtr = curPtr->getNext();
    }
    return ableToRemove;
}

template<class ItemType>
void LinkedList<ItemType>::clear(){
    while(itemCount>0){
        remove(headPtr->getItem().getName());
    }
}

template class LinkedList<GraphEdge>;