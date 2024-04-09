/*
Name: Orhun Ege Çelik
Course Code: CS 201
Section: 3
Student Number: 22202321
*/

#include "Content.h"

Content::Content()
{
}

Content::Content(const int id, const string &name) : id(id), name(name) {}

const int Content::getId() const
{
    return this->id;
}

const int Content::getCreatorId() const
{
    return creatorId;
}

void Content::setCreatorId(const int creatorId)
{
    this->creatorId = creatorId;
}
