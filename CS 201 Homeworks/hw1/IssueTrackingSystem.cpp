/*
Name: Orhun Ege Çelik
Section: 3
Student Number: 22202321
*/

#include <iostream>
#include <string>
#include "IssueTrackingSystem.h"
using namespace std;

IssueTrackingSystem::IssueTrackingSystem()
:employees{nullptr}, employeeCount{0}{}

IssueTrackingSystem::~IssueTrackingSystem(){
    if(employees){
        delete[] employees;
    }
}

void IssueTrackingSystem::addEmployee(const string name, const string title){
   for(int i = 0; i < employeeCount; i++){
        if(employees[i].getName() == name){
            cout <<  "Cannot add employee. Employee with name " << name << " already exists." << endl;
            return;
        }
    }
    employeeCount++;

    Employee* temp = employees;
    employees = new Employee[employeeCount];
    for(int i = 0; i < employeeCount-1; i++){
        employees[i] = temp[i];
    }
    employees[employeeCount-1] = Employee(name, title);

    if(temp){
        delete[] temp;
    }
    cout << "Added employee " << name << "." << endl;
    return;
}

void IssueTrackingSystem::removeEmployee(const string name){
    int eIndex = -1;
    for(int i = 0; i < employeeCount && eIndex == -1; i++){
        if(employees[i].getName() == name){
            eIndex = i;
        }
    }
    if(eIndex == -1){ // this is the case either when the employees array is searched and the employee does not exist, or when the employees array is null.
        cout <<  "Cannot remove employee. There is no employee with name " << name << "." << endl;
        return;
    }
    //if the employee to delete exist:
    if(employees[eIndex].getIssueCount()>0){
        cout << "Cannot remove employee. " << name << " has assigned issues." << endl;
        return;
    }
    employeeCount--;
    Employee* temp = employees;
    if(employeeCount > 0){
        employees = new Employee[employeeCount];
        int index = 0;
        for(int i = 0; i<eIndex; i++){
            employees[index++] = temp[i];
        }
        for(int i = eIndex + 1; i < employeeCount + 1; i++){
            employees[index++] = temp[i];
        }
    }
    else{
        employees = nullptr;
    }
    delete[] temp;
    cout << "Removed employee " << name << "." << endl;
    return;

}
void IssueTrackingSystem::addIssue( const int issueId, const string description, const string assigneeName ){
    int eIndex = -1;
    for(int i = 0; i < employeeCount; i++){
        if(employees[i].getName() == assigneeName){
            eIndex = i;
        }
    }
    if(eIndex == -1){
        cout << "Cannot add issue. There is no employee with name " << assigneeName << "." << endl;
        return;
    }

    for(int i = 0; i < employeeCount; i++){
        for(int j = 0; j < employees[i].getIssueCount(); j++){
            if(employees[i].getIssues()[j].getId() == issueId){
               cout << "Cannot add issue. Issue with ID " << issueId << " already exists." << endl;
                return; 
            }
        }
    }

    
    //if the issue is to be added:
    Issue issueToAdd(issueId, description, assigneeName);
    employees[eIndex].addIssue(&issueToAdd);
    cout << "Added issue " << to_string(issueId) << "." << endl;
    
    return;
}
void IssueTrackingSystem::removeIssue( const int issueId ){
    int iIndex = -1;
    int eIndex = -1;
     for(int i = 0; i < employeeCount; i++){
        for(int j = 0; j < employees[i].getIssueCount(); j++){
            if(employees[i].getIssues()[j].getId() == issueId){
               iIndex = j;
               eIndex = i;
            }
        }
    }

    if(iIndex == -1){ // this is the case either when the issues arrays are searched and the issue does not exist, or when the issues arrays are null.
        cout << "Cannot remove issue. There is no issue with ID " << issueId << "." << endl;
        return;
    }

    employees[eIndex].removeIssue(issueId);
    cout << "Removed issue " << to_string(issueId) << "." << endl;
    return;
}
void IssueTrackingSystem::changeAssignee( const string previousAssignee, const string newAssignee){
    int prevIndex = -1;
    int newIndex = -1;

    for(int i = 0; i < employeeCount; i++){
        if(employees[i].getName()==previousAssignee){
            prevIndex = i;
        }
        else if(employees[i].getName()==newAssignee){
            newIndex = i;
        }
    }
    if(prevIndex == -1 || newIndex == -1){
        cout << "Cannot change assignee. Previous or/and new assignee does not exist." << endl;
        return;
    }

    Issue* temp = employees[newIndex].getIssues();
    int tempIssueCount = employees[newIndex].getIssueCount();
    Issue*& prevIssues = employees[prevIndex].getIssues();
    if(employees[prevIndex].getIssueCount() == 0){
        cout<<employees[prevIndex].getName() <<"'s issues are transferred to " << employees[newIndex].getName()<<"."<<endl;
        return;
    }
    for(int i = 0; i<employees[prevIndex].getIssueCount(); i++){
        employees[prevIndex].getIssues()[i].setEmployee(newAssignee);
    }
    employees[newIndex].getIssues() = new Issue[ tempIssueCount + employees[prevIndex].getIssueCount()];
    for(int i = 0; i<employees[newIndex].getIssueCount(); i++ ){
        employees[newIndex].getIssues()[i] = temp[i];
    }
    for(int i = 0; i<employees[prevIndex].getIssueCount(); i++){
        prevIssues[i].setEmployee(newAssignee);
        employees[newIndex].getIssues()[employees[newIndex].getIssueCount()+i] = prevIssues[i];
    }
    employees[newIndex].setIssueCount(employees[newIndex].getIssueCount() + employees[prevIndex].getIssueCount());
    employees[prevIndex].setIssueCount(0); 
    cout<<employees[prevIndex].getName() <<"'s issues are transferred to " << employees[newIndex].getName()<<"."<<endl;
    if(tempIssueCount>0)
    delete[] temp;
    delete[] prevIssues;

}
void IssueTrackingSystem::showAllEmployees() const{
    cout<<"Employees in the system:"<<endl;
    if(employeeCount == 0){
        cout<<"None"<<endl;
        return;
    }
    for (int i = 0; i < employeeCount; i++){
         cout<<employees[i].showEmployee();
    }

}
void IssueTrackingSystem::showAllIssues() const{
    cout<<"Issues in the system:"<<endl;
    int issueCount = 0;
    for(int i = 0; i<employeeCount; i++){
        issueCount+= employees[i].getIssueCount();
    }
    if(issueCount == 0){
        cout<<"None"<<endl;
        return;
    }
    for (int i = 0; i < employeeCount; i++){
        for(int j = 0; j<employees[i].getIssueCount(); j++){
            cout<<employees[i].getIssues()[j].displayIssue();
        }
    }
}
void IssueTrackingSystem::showEmployee(const string name) const{
    int eIndex = -1;
    for(int i = 0; i<employeeCount; i++){
        if(employees[i].getName() == name){
            eIndex = i;
        }
    }
    if(eIndex == -1){
        cout<<"Cannot show employee. There is no employee with name " <<name<< "." <<endl;
        return;
    }
    cout << employees[eIndex].showEmployee();
}
void IssueTrackingSystem::showIssue( const int issueId ) const{
    int iIndex = -1;
    int eIndex = -1;
    bool flag = true;
    for(int i = 0; i < employeeCount && flag; i++){
        for(int j = 0; j<employees[i].getIssueCount() && flag; j++){
            if(employees[i].getIssues()[j].getId() == issueId){
                iIndex = j;
                eIndex = i;
                flag = false;
            }
        }
    }

    if(iIndex == -1 ){
        cout<<"Cannot show issue. There is no issue with ID " <<to_string(issueId)<< "." <<endl;
        return;
    }
    cout << employees[eIndex].getIssues()[iIndex].displayIssue();
}


