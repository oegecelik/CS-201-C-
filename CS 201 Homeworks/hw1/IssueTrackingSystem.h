/*
Name: Orhun Ege Çelik
Section: 3
Student Number: 22202321
*/

#ifndef ISSUETRACKINGSYSTEM_H
#define ISSUETRACKINGSYSTEM_H

#include <iostream>
#include <string>
#include "Employee.h"
using namespace std;

class IssueTrackingSystem {
public:
IssueTrackingSystem();
~IssueTrackingSystem();
void addEmployee( const string name, const string title );
void removeEmployee( const string name );
void addIssue( const int issueId, const string description, const string
assigneeName );
void removeIssue( const int issueId );
void changeAssignee( const string previousAssignee, const string newAssignee );
void showAllEmployees() const;
void showAllIssues() const;
void showEmployee( const string name ) const;
void showIssue( const int issueId ) const;

private:
Employee* employees;
int employeeCount;
};

#endif