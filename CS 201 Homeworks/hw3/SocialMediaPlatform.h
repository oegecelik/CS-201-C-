/*
Name: Orhun Ege Çelik
Course Code: CS 201
Section: 3
Student Number: 22202321
*/

#ifndef SOCIAL_MEDIA_PLATFORM
#define SOCIAL_MEDIA_PLATFORM

#include <iostream>
#include "ContentCreator.h"
using namespace std;

class SocialMediaPlatform {
    public:
        SocialMediaPlatform();
        ~SocialMediaPlatform();
        void addRegularUser( const int regularUserId, const string name );
        void removeRegularUser( const int regularUserId );
        void addContentCreator( const int contentCreatorId, const string name );
        void removeContentCreator( const int contentCreatorId );
        void addContent( const int contentCreatorId, const int contentId, const string
        title );
        void removeContent( const int contentCreatorId, const int contentId );
        void followContentCreator( const int regularUserId, const int contentCreatorId );
        void unfollowContentCreator( const int regularUserId, const int contentCreatorId);
        void showFollowersOf( const int contentCreatorId ) const;
        void showContentsOf( const int contentCreatorId ) const;
        void showAllRegularUsers( ) const;
        void showAllContentCreators( ) const;

        const LinkedList<RegularUser>& getRegularUsers() const;

    private:
        LinkedList<RegularUser> regularUsers;
        LinkedList<ContentCreator> contentCreators;
        LinkedList<Content> contents;
};

#endif