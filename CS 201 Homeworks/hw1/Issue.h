/*
Name: Orhun Ege Çelik
Section: 3
Student Number: 22202321
*/

#ifndef ISSUE_H
#define ISSUE_H

#include <iostream>
#include <string>
class Employee; //to prevent circular dependency, otherwise I would include "Employee.h"
using namespace std;

class Issue{

public:
Issue();
~Issue();
Issue(const int issueId, const string description, const string employee);
string displayIssue() const;
int getId() const;
const string getEmployee() const;
void setIssueId(const int issueId);
void setDescription(const string description);
void setEmployee(const string employee);
private:
string description;
int issueId;
string employee;
};

#endif