/*
Name: Orhun Ege Çelik
Course Code: CS 201
Section: 3
Student Number: 22202321
*/

#include "ContentCreator.h"

ContentCreator::ContentCreator()
{
}

ContentCreator::ContentCreator(const int &id, const string &name) : id(id), name(name)
{
    followerCount = 0;
    contentCount = 0;
}

const int ContentCreator::getId() const
{
    return id;
}

const string ContentCreator::getName() const
{
    return name;
}

const int ContentCreator::getFollowerCount() const
{
    return followerCount;
}

const int ContentCreator::getContentCount() const
{
    return contentCount;
}

bool ContentCreator::addContent(const int contentId, const string title)
{
    bool ableToInsert = contents.insert(contentId, title);
    if(ableToInsert){
        contentCount++;
    }
    return ableToInsert;
    
}

bool ContentCreator::removeContent(const int contentId)
{
    bool ableToRemove = contents.remove(contentId);
    if(ableToRemove){
        contentCount--;
    }
    return ableToRemove;
}

bool ContentCreator::followContentCreator(const int regularUserId, const LinkedList<RegularUser>& regularUsers)
{
    for(Node<RegularUser>* curPtr = followers.headPtr; curPtr != nullptr; curPtr = curPtr->getNext()){
        if(curPtr->getItem().getId() == regularUserId){
            return false;
        }
    }
    Node<RegularUser>* usersHeadPtr = regularUsers.headPtr;
    for(Node<RegularUser>* curPtr = usersHeadPtr; curPtr != nullptr; curPtr = curPtr->getNext()){
        if(curPtr->getItem().getId() == regularUserId){
            followers.insert(curPtr->getItem().getId(), curPtr->getItem().getName());
            followerCount++;
            return true;
        }
    }
    return false;
}

bool ContentCreator::unfollowContentCreator(const int regularUserId)
{
    for(Node<RegularUser>* curPtr = followers.headPtr; curPtr != nullptr; curPtr = curPtr->getNext()){
        if(curPtr->getItem().getId() == regularUserId){
            followers.remove(regularUserId);
            followerCount--;
            return true;
        }
    }
    return false;
}

void ContentCreator::showFollowers()
{
    for(Node<RegularUser>* curPtr = followers.headPtr; curPtr != nullptr; curPtr = curPtr->getNext()){
        cout << curPtr->getItem().getId() << endl;
    }

}

void ContentCreator::showContents()
{
    for(Node<Content>* curPtr = contents.headPtr; curPtr != nullptr; curPtr = curPtr->getNext()){
        cout << curPtr->getItem().getId() << endl;
    }
}
