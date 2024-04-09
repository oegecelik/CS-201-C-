/*
Name: Orhun Ege Çelik
Course Code: CS 201
Section: 3
Student Number: 22202321
*/

#ifndef CONTENT_CREATOR
#define CONTENT_CREATOR
#include "LinkedList.h"
#include "Content.h"
#include "RegularUser.h"

class ContentCreator{
    public:
        ContentCreator();
        ContentCreator(const int& id, const string& name);
        const int getId() const;
        const string getName() const;
        const int getFollowerCount() const;
        const int getContentCount() const;
        bool addContent(const int contentId, const string title);
        bool removeContent(const int contentId);
        bool followContentCreator(const int regularUserId, const LinkedList<RegularUser>& regularUsers);
        bool unfollowContentCreator(const int regularUserId);
        void showFollowers();
        void showContents();
    private: 
        LinkedList<Content> contents;
        LinkedList<RegularUser> followers;
        int id;
        string name;
        int followerCount;
        int contentCount;      
        
};

#endif