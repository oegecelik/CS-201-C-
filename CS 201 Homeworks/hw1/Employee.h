/*
Name: Orhun Ege Çelik
Section: 3
Student Number: 22202321
*/

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
#include "Issue.h"
using namespace std;

class Employee{

public:
Employee();
Employee(const string name, const string title);
Employee(const Employee& prevEmployee);
Employee& operator=(const Employee& rightEmployee);
~Employee();
bool addIssue(Issue* newIssue);
bool removeIssue(const int issueId);
string getName() const;
string getTitle() const;
int getIssueCount() const;
void setIssueCount(int count);
void setName(const string name);
void setTitle(const string title);
void increaseIssueCount();
void decreaseIssueCount();
Issue*& getIssues();
string showEmployee() const;

private:
Issue* issues;
int issueCount;
string name;
string title;
};

#endif