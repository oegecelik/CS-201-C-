/*
Name: Orhun Ege Çelik
Section: 3
Student Number: 22202321
*/

#include <iostream>
#include <string>
#include "Employee.h"
using namespace std;

Employee::Employee()
:issues{nullptr},  issueCount{0}, name{"trash"}, title{"trash"} {}

Employee::Employee(const string name, const string title)
    :issues{nullptr}, issueCount{0}, name{name}, title{title}{
    }


Employee::~Employee(){
    if(issueCount>0){
        delete[] issues;
        issues = nullptr;
    }
}

Employee::Employee(const Employee& prevEmployee)
    :issues{nullptr}, issueCount{prevEmployee.issueCount}, name{prevEmployee.name},title{prevEmployee.title}{
        if(issueCount > 0){
            issues = new Issue[issueCount];
            for(int i = 0; i < issueCount; i++){
                issues[i] = prevEmployee.issues[i];
            }
        }
        else{
            issues = nullptr;
        }    
}

Employee& Employee::operator=(const Employee& right){
    if(&right != this){
        if(issueCount != right.issueCount){
            if(issueCount > 0){
                delete[] issues;
            }
            issueCount = right.issueCount;
            if(issueCount > 0){
                issues = new Issue[issueCount];
            }
            else{
                issues = nullptr;
            }
        }
        for(int i = 0; i < issueCount; i++){
            issues[i] = right.issues[i];
        }
        name = right.name;
        title = right.title;
    }

    return *this;

}

bool Employee::addIssue(Issue* newIssue){
    
    Issue* temp = issues;
    issues = new Issue[issueCount + 1];
    for(int i = 0; i<issueCount; i++){
        issues[i] = temp[i];
    }
    issues[issueCount++] = *newIssue;
    if(temp)
    delete[] temp;
    return true;
}

bool Employee::removeIssue(const int issueId){ 
    if(issueCount == 0){
        return false;
    }
    Issue* temp = issues;
    int iIndex;
    issues = nullptr;
    for(int i = 0; i<issueCount; i++){
        if(issueId == temp[i].getId()){
            iIndex = i;
        }
    }
    issueCount--;
    if(issueCount>0){
        int index = 0;
        issues = new Issue[issueCount];
        for(int i = 0; i<iIndex; i++){    
            issues[index++] = temp[i];
        }
        for(int i = iIndex + 1; i < issueCount + 1; i++){
            issues[index++] = temp[i];
        }
    }
    else{
        issues = nullptr;
    }
    if(temp)
    delete[] temp;
    return true;
}
 
string Employee::getName() const{
    return this->name;
}

string Employee::getTitle() const{
    return this->title;
}

Issue*& Employee::getIssues(){
    return issues;
}

int Employee::getIssueCount() const{
    return this->issueCount;
}

void Employee::setIssueCount(int count){
    this->issueCount = count;
}

void Employee::increaseIssueCount(){
    this->issueCount++;
}

void Employee::decreaseIssueCount(){
    this->issueCount--;
}

void Employee::setName(const string name){
    this->name = name;
}

void Employee::setTitle(const string title){
    this->title = title;
}

string Employee::showEmployee() const{
    return name + ", " + title + ", " + to_string(issueCount) + " issue(s).\n";
}