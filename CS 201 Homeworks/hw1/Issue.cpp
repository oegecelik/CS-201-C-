/*
Name: Orhun Ege Çelik
Section: 3
Student Number: 22202321
*/

#include "Employee.h"
#include <iostream>
using namespace std;

Issue::Issue()
:description{"trash"}, issueId{-1}, employee{"trash"}{}

Issue::Issue(const int issueId, const string description, const string employee)
:description{description}, issueId{issueId}, employee{employee}
{}

Issue::~Issue(){}

int Issue::getId() const{
return issueId;
}

const string Issue::getEmployee() const{
    return this->employee;
}

void Issue::setDescription(const string description){
    this->description = description;
}

void Issue::setIssueId(const int issueId){
    this->issueId = issueId;
}

void Issue::setEmployee(const string employee){
    this->employee = employee;
}

string Issue::displayIssue() const{
return to_string(issueId) + ", " +  description + ", " + employee + ".\n";
}
