/*
Name: Orhun Ege Çelik
Course Code: CS 201
Section: 3
Student Number: 22202321
*/

#include "SocialMediaPlatform.h"

SocialMediaPlatform::SocialMediaPlatform()
{}

SocialMediaPlatform::~SocialMediaPlatform()
{
    contentCreators.clear();
    regularUsers.clear();
}

void SocialMediaPlatform::addRegularUser(const int regularUserId, const string name)
{
    bool ableToInsert = regularUsers.insert(regularUserId, name);
    if(ableToInsert){
        cout << "Added regular user " << regularUserId << "." << endl;
    }
    else{
        cout << "Cannot add regular user. There is already a regular user with ID " << regularUserId << "." << endl;
    }
}

void SocialMediaPlatform::removeRegularUser(const int regularUserId)
{
    bool ableToRemove = regularUsers.remove(regularUserId);
    if(ableToRemove){
        for(Node<ContentCreator>* curPtr = contentCreators.headPtr; curPtr != nullptr; curPtr = curPtr->getNext()){
            curPtr->getItem().unfollowContentCreator(regularUserId);
        }
        cout << "Removed regular user " << regularUserId << "." << endl;
    }
    else{
        cout << "Cannot remove regular user. There is no regular user with ID " << regularUserId << "." << endl;
    }
}

void SocialMediaPlatform::addContentCreator(const int contentCreatorId, const string name)
{
    bool ableToInsert = contentCreators.insert(contentCreatorId, name);
    if(ableToInsert){
        cout << "Added content creator " << contentCreatorId << "." << endl;
    }
    else{
        cout << "Cannot add content creator. There is already a content creator with ID " << contentCreatorId << "." << endl;
    }
}

void SocialMediaPlatform::removeContentCreator(const int contentCreatorId)
{
    Node<Content>* curPtr = contents.headPtr;
    while(curPtr != nullptr){
        Node<Content>* nextPtr = curPtr->getNext();
        if(curPtr->getItem().getCreatorId() == contentCreatorId){
            contents.remove(curPtr->getItem().getId());
        }
        curPtr = nextPtr;
    }
    bool ableToRemove = contentCreators.remove(contentCreatorId);
    if(ableToRemove){
        cout << "Removed content creator " << contentCreatorId << "." << endl;
    }
    else{
        cout << "Cannot remove content creator. There is no content creator with ID " << contentCreatorId << "." << endl;
    }
}

void SocialMediaPlatform::addContent(const int contentCreatorId, const int contentId, const string title)
{
    Node<Content>* curPtr = contents.headPtr;
    while(curPtr != nullptr){
        Node<Content>* nextPtr = curPtr->getNext();
        if(curPtr->getItem().getId() == contentId){
            cout << "Cannot add content. There is already a content with ID " << contentId << "."<<endl;
            return;
        }
        curPtr = nextPtr;
    }
    Node<ContentCreator>* currentCreator = contentCreators.getNodeWithID(contentCreatorId);
    if(currentCreator == nullptr){
        cout<< "Cannot add content. There is no content creator with ID "<< contentCreatorId <<"."<<endl;
    }
    else{
        bool ableToInsert = contents.insert(contentId, title);
        contents.getNodeWithID(contentId)->getItem().setCreatorId(contentCreatorId);
        if(ableToInsert){
            currentCreator->getItem().addContent(contentId, title);
            cout<<"Added content " << contentId << "." << endl;
        }
        else{
            cout << "Cannot add content. There is already a content with ID " << contentId << "."<<endl;
        }
    }
}

void SocialMediaPlatform::removeContent(const int contentCreatorId, const int contentId)
{
    
    Node<ContentCreator>* currentCreator = contentCreators.getNodeWithID(contentCreatorId);
    if(currentCreator == nullptr){
        cout<< "Cannot remove content. There is no content creator with ID "<< contentCreatorId <<"."<<endl;
    }
    else{
        bool ableToRemove = contents.remove(contentId);
        if(ableToRemove){
            currentCreator->getItem().removeContent(contentId);
            cout<<"Removed content " << contentId << "." << endl;
        }
        else{
            cout<<"Cannot remove content. There is no content with ID " << 
            contentId <<" shared by content creator with ID "<<contentCreatorId<<"."<<endl;
        }
    }
}

void SocialMediaPlatform::followContentCreator(const int regularUserId, const int contentCreatorId)
{
    Node<ContentCreator>* currentCreator = contentCreators.getNodeWithID(contentCreatorId);
    Node<RegularUser>* currentUser = regularUsers.getNodeWithID(regularUserId);

    if(currentCreator == nullptr || currentUser == nullptr){
        cout<< "Cannot follow. Regular user and/or content creator ID does not exist."<<endl;
    }
    else{
        bool ableToFollow = currentCreator->getItem().followContentCreator(regularUserId, regularUsers);
        if(ableToFollow){
            cout<<"Regular user with ID " <<regularUserId << " followed content creator with ID " << contentCreatorId << "." << endl;
        }
        else{
            cout << "Cannot follow. The user is already following the content creator."<<endl;
        }
    }
}

void SocialMediaPlatform::unfollowContentCreator(const int regularUserId, const int contentCreatorId)
{
    Node<ContentCreator>* currentCreator = contentCreators.getNodeWithID(contentCreatorId);
    Node<RegularUser>* currentUser = regularUsers.getNodeWithID(regularUserId);

    if(currentCreator == nullptr || currentUser == nullptr){
        cout<< "Cannot unfollow. Regular user and/or content creator ID does not exist."<<endl;
    }
    else{
        bool ableToRemove = currentCreator->getItem().unfollowContentCreator(regularUserId);
        if(ableToRemove){
            cout<<"Regular user with ID " <<regularUserId << " unfollowed content creator with ID " << contentCreatorId << "." << endl;
        }
        else{
            cout << "Cannot unfollow. The user is not following the content creator." << endl;
        }
    }
}

void SocialMediaPlatform::showFollowersOf(const int contentCreatorId) const
{
    Node<ContentCreator>* currentCreator = contentCreators.getNodeWithID(contentCreatorId);
    if(currentCreator == nullptr){
        cout<< "Cannot show. There is no content creator with ID "<< contentCreatorId <<"."<<endl;
    }
    else{
        cout<< "Regular users following content creator with ID " << contentCreatorId << ":" << endl;
        if(currentCreator->getItem().getFollowerCount() == 0){
            cout<<"None"<<endl;
        }
        else{
            currentCreator->getItem().showFollowers();
        }
    }
}

void SocialMediaPlatform::showContentsOf(const int contentCreatorId) const
{
    Node<ContentCreator>* currentCreator = contentCreators.getNodeWithID(contentCreatorId);
    if(currentCreator == nullptr){
        cout<< "Cannot show. There is no content creator with ID "<< contentCreatorId <<"."<<endl;
    }
    else{
        cout<< "Contents of content creator with ID " << contentCreatorId << ":" << endl;
        if(currentCreator->getItem().getContentCount() == 0){
            cout<<"None"<<endl;
        }
        else{
            currentCreator->getItem().showContents();
        }
    }
}

void SocialMediaPlatform::showAllRegularUsers() const
{
    int i = 0;
    cout<<"Regular users in the social media platform:"<<endl;
    for(Node<RegularUser>* curPtr = regularUsers.headPtr; curPtr != nullptr; curPtr = curPtr->getNext(), i++){
        cout << curPtr->getItem().getId() << ", " << curPtr->getItem().getName()<<endl;
    }
    if(i == 0){
        cout<<"None"<<endl;
    }
}

void SocialMediaPlatform::showAllContentCreators() const
{
    int i = 0;
    cout<<"Content creators in the social media platform:"<<endl;
    for(Node<ContentCreator>* curPtr = contentCreators.headPtr; curPtr != nullptr; curPtr = curPtr->getNext(), i++){
        cout << curPtr->getItem().getId() << ", " << curPtr->getItem().getName()<<
        ", " <<curPtr->getItem().getFollowerCount() << " follower(s), " << curPtr->getItem().getContentCount() << " content(s)" <<endl;
    }
    if(i == 0){
        cout<<"None"<<endl;
    }
}
const LinkedList<RegularUser>& SocialMediaPlatform::getRegularUsers() const
{
    return regularUsers;
}

