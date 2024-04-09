/*
Name: Orhun Ege Çelik
Section: 3
Student Number: 22202321
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "ZooMap.h"
using namespace std;
ZooMap::ZooMap(const string cageFile, const string zooFile)
{
    ifstream myCageFile (cageFile);
    ifstream myZooFile (zooFile);
    string curLine;
    int cageCount = 0;
    int connectionCount = 0;
    if(myCageFile.is_open()){
        while(getline(myCageFile,curLine)){
           //getline(myCageFile,curLine);
           string name = curLine.substr(0,1);
           string probString = curLine.substr(2);
           double prob = stod(probString);
           zoo.insert(name, prob);
           cageCount++;
        }
    }

    if(myZooFile.is_open()){
        while(getline(myZooFile,curLine)){
           //getline(myZooFile,curLine);
           string startCage = curLine.substr(0,1);
           string endCage = curLine.substr(2,1);
           zoo.getNodeWithName(startCage)->getItem().addToList(
            &(zoo.getNodeWithName(endCage)->getItem()));
            connectionCount++;
        }
    }
    cout<< cageCount << " cages and " << connectionCount << " connections have been loaded."<<endl;
    
}

ZooMap::~ZooMap()
{
}

void ZooMap::displayAllCages() const
{
    cout<<"The cages in the zoo are:"<<endl;
    for(Node<GraphEdge>* curPtr = zoo.headPtr; curPtr != nullptr; curPtr = curPtr->getNext()){
        cout<<curPtr->getItem().getName()<<",";
        if(curPtr->getNext() != nullptr)
            cout << " ";
    }
    cout<<endl;
}

void ZooMap::displayAdjacentCages(const string cageName) const
{
    cout<<"The cages adjacent to " << cageName << " are:"<<endl;
    cout<<cageName<<" ->";
    Node<GraphEdge>* curPtr = zoo.getNodeWithName(cageName)->getItem().adjacencyList.headPtr;
    if(curPtr != nullptr)
        cout<<" ";
    for(; curPtr != nullptr; curPtr = curPtr->getNext()){
        cout<<curPtr->getItem().getName()<<",";
        if(curPtr->getNext() != nullptr)
            cout << " ";
    }
    cout<<endl;
}

void ZooMap::displayZooMap() const
{
    cout<<"The whole zoo map is:"<<endl;
    for(Node<GraphEdge>* curPtr = zoo.headPtr; curPtr != nullptr; curPtr = curPtr->getNext()){
        string cageName = curPtr->getItem().getName();
        cout<< cageName <<" ->";
        Node<GraphEdge>* adjacencyCurPtr = zoo.getNodeWithName(cageName)->getItem().adjacencyList.headPtr;
        if(adjacencyCurPtr != nullptr)
            cout<<" ";
        for(; adjacencyCurPtr != nullptr; adjacencyCurPtr = adjacencyCurPtr->getNext()){
            cout<<adjacencyCurPtr->getItem().getName()<<",";
            if(adjacencyCurPtr->getNext() != nullptr)
            cout << " ";
        }
        cout<<endl;
    }
}

void ZooMap::findSafestPath(const string startCage, const string endCage)
{
    bool isInStack[26];
    for(int i = 0; i<26; i++){
        isInStack[i] = false;
    }
    Stack stack;
    Stack bestStack;
    double curProb;
    double bestProb = 0;
    stack.push(zoo.getNodeWithName(startCage)->getItem());
    curProb = stack.peek().getProb();

    int currentCharAscii = (int)startCage[0];
    const int a = (int)'A';
    isInStack[currentCharAscii - a] = true;

    bool flag = false;

    //Main loop that iterates all paths by pushing them into the stack:

    while(!stack.isEmpty()){
        if(stack.peek().getName()==endCage){
            flag = true;
            if(curProb>bestProb){
                bestStack.clear();
                bestStack = stack;
                bestProb = curProb;
            }
            currentCharAscii = (int) stack.peek().getName()[0];
            isInStack[currentCharAscii - a] = false;
            curProb /= stack.peek().getProb();
            stack.pop();
        }
        else if(stack.peek().curChild == nullptr){
            currentCharAscii = (int) stack.peek().getName()[0];
            isInStack[currentCharAscii - a] = false;
            curProb /= stack.peek().getProb();
            stack.pop();
        }
        else{ //That is, if the top of stack is not the goal and has some children
            int nextCharAscii = (int) stack.peek().curChild->getItem().getName()[0];
            if(isInStack[nextCharAscii - a] == true){
                stack.peek().curChild = stack.peek().curChild->getNext();
            }
            else{
                isInStack[nextCharAscii - a] = true;
                Node<GraphEdge>* prevNode = stack.peek().curChild;
                stack.peek().curChild = stack.peek().curChild->getNext();
                stack.push(zoo.getNodeWithName(prevNode->getItem().getName())->getItem());
                curProb *= stack.peek().getProb();
            }
        }
    }

    if(flag == false){
        cout << "No path exists from " << startCage << " to " << endCage << "." << endl;
    }
    else{
        cout << "Safest path from " << startCage << " to " << endCage << " is:" << endl;
        string output = bestStack.peek().getName();
        bestStack.pop();
        while(!bestStack.isEmpty()){
            output.insert(0, " -> ");
            output.insert(0,bestStack.peek().getName());
            bestStack.pop();
        }
        cout<<output<<endl;    
        cout<<"Probability: ";
        cout<<setprecision(6)<<fixed<<bestProb<<endl;
    }
}

void ZooMap::findMostDangerousPath(const string startCage, const string endCage)
{
     bool isInStack[26];
    for(int i = 0; i<26; i++){
        isInStack[i] = false;
    }
    Stack stack;
    Stack bestStack;
    double curProb;
    double bestProb = 1;
    stack.push(zoo.getNodeWithName(startCage)->getItem());
    curProb = stack.peek().getProb();

    int currentCharAscii = (int)startCage[0];
    const int a = (int)'A';
    isInStack[currentCharAscii - a] = true;

    bool flag = false;

    //Main loop that iterates all paths by pushing them into the stack:

    while(!stack.isEmpty()){
        if(stack.peek().getName()==endCage){
            flag = true;
            if(curProb<bestProb){
                bestStack.clear();
                bestStack = stack;
                bestProb = curProb;
            }
            currentCharAscii = (int) stack.peek().getName()[0];
            isInStack[currentCharAscii - a] = false;
            curProb /= stack.peek().getProb();
            stack.pop();
        }
        else if(stack.peek().curChild == nullptr){
            currentCharAscii = (int) stack.peek().getName()[0];
            isInStack[currentCharAscii - a] = false;
            curProb /= stack.peek().getProb();
            stack.pop();
        }
        else{ //That is, if the top of stack is not the goal and has some children
            int nextCharAscii = (int) stack.peek().curChild->getItem().getName()[0];
            if(isInStack[nextCharAscii - a] == true){
                stack.peek().curChild = stack.peek().curChild->getNext();
            }
            else{
                isInStack[nextCharAscii - a] = true;
                Node<GraphEdge>* prevNode = stack.peek().curChild;
                stack.peek().curChild = stack.peek().curChild->getNext();
                stack.push(zoo.getNodeWithName(prevNode->getItem().getName())->getItem());
                curProb *= stack.peek().getProb();
            }
        }
    }

    if(flag == false){
        cout << "No path exists from " << startCage << " to " << endCage << "." << endl;
    }
    else{
        cout << "Most dangerous path from " << startCage << " to " << endCage << " is:" << endl;
        string output = bestStack.peek().getName();
        bestStack.pop();
        while(!bestStack.isEmpty()){
            output.insert(0, " -> ");
            output.insert(0,bestStack.peek().getName());
            bestStack.pop();
        }
        
        cout<<output<<endl;    
        cout<<"Probability: ";
        cout<<setprecision(6)<<fixed<<bestProb<<endl;
    }
}
