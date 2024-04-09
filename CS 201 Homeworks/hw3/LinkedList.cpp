#include "LinkedList.h"
#include "Content.h"
#include "ContentCreator.h"
#include "RegularUser.h"
#include <iostream>
#include <cstddef>

using namespace std;

template<class ItemType>
LinkedList<ItemType>::LinkedList() : itemCount(0), headPtr(nullptr){}

template <class ItemType>
LinkedList<ItemType>::~LinkedList()
{
    clear();
}

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeWithID(int ID) const{
    Node<ItemType>* curPtr = headPtr;
    for(int i = 1; i<=itemCount; i++){
        if(ID==curPtr->getItem().getId()){
            return curPtr;
        }
        curPtr = curPtr->getNext();
    }
    return nullptr;
}

template<class ItemType>
bool LinkedList<ItemType>::insert(const int newEntryID, const string& newEntryTitle){ // For contents, since they only exist within creators

    bool ableToInsert = true;
    Node<ItemType>* prevPtr = nullptr;
    Node<ItemType>* nextPtr = headPtr;
    Node<ItemType>* curPtr = headPtr;

    for(int i = 1; i<=itemCount; i++){
        if(newEntryID == curPtr->getItem().getId()){
            ableToInsert = false;
            return false;
        }
        if((nextPtr == nullptr) || (newEntryID < nextPtr->getItem().getId())){
            // Since the list is sorted, if the new ID is smaller than next, we will have found the correct index. 
            break;
        }
        prevPtr = nextPtr;
        nextPtr = nextPtr->getNext();
        curPtr = curPtr->getNext();
    }
    ItemType newItem(newEntryID, newEntryTitle);
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
bool LinkedList<ItemType>::remove(const int oldEntryID){
    bool ableToRemove = false;
    Node<ItemType>* prevPtr = nullptr;
    Node<ItemType>* curPtr = headPtr;

    for(int i = 1; i<=itemCount; i++){
        if(oldEntryID == curPtr->getItem().getId()){
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
        remove(headPtr->getItem().getId());
    }
}

template class LinkedList<Content>;
template class LinkedList<RegularUser>;
template class LinkedList<ContentCreator>;