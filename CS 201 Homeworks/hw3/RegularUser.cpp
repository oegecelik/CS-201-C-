/*
Name: Orhun Ege Çelik
Course Code: CS 201
Section: 3
Student Number: 22202321
*/

#include "RegularUser.h"

RegularUser::RegularUser()
{
}

RegularUser::RegularUser(const int ID, const string &name) : ID(ID), name(name) {}

const int RegularUser::getId() const
{
    return this->ID;
}

const string RegularUser::getName() const
{
    return name;
}
