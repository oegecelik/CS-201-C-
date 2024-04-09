/*
Name: Orhun Ege Çelik
Section: 3
Student Number: 22202321
*/

#include "Stack.h"
#include <cassert>
Stack::Stack() : topPtr(nullptr)
{
}

Stack::Stack(const Stack &aStack)
{
    Node<GraphEdge>* origChainPtr = aStack.topPtr;
    if(origChainPtr == nullptr)
        topPtr = nullptr;
    else{
        topPtr = new Node <GraphEdge>();
        topPtr->setItem(origChainPtr->getItem());
        Node<GraphEdge>* newChainPtr = topPtr;
        origChainPtr = origChainPtr->getNext();

        while(origChainPtr != nullptr){

            GraphEdge nextItem = origChainPtr->getItem();
            Node<GraphEdge>* newNodePtr = new Node<GraphEdge>(nextItem);
            newChainPtr->setNext(newNodePtr);
            newChainPtr = newChainPtr->getNext();
            origChainPtr = origChainPtr->getNext();

        }
        newChainPtr->setNext(nullptr);
    }
}

Stack::~Stack()
{
    while(!isEmpty()){
        pop();
    }
}

Stack& Stack::operator=(const Stack &aStack)
{
    Node<GraphEdge>* origChainPtr = aStack.topPtr;
    if(origChainPtr == nullptr)
        topPtr = nullptr;
    else{
        topPtr = new Node <GraphEdge>();
        topPtr->setItem(origChainPtr->getItem());
        Node<GraphEdge>* newChainPtr = topPtr;
        origChainPtr = origChainPtr->getNext();

        while(origChainPtr != nullptr){

            //GraphEdge nextItem = origChainPtr->getItem();
            Node<GraphEdge>* newNodePtr = new Node<GraphEdge>(origChainPtr->getItem());
            newChainPtr->setNext(newNodePtr);
            newChainPtr = newChainPtr->getNext();
            origChainPtr = origChainPtr->getNext();
        }
        newChainPtr->setNext(nullptr);
    }
    return *this;
}

bool Stack::isEmpty() const
{
    return topPtr == nullptr;
}

bool Stack::push(const GraphEdge &newItem)
{
    Node<GraphEdge>* newNodePtr = new Node<GraphEdge>(newItem, topPtr);
    topPtr = newNodePtr;
    newNodePtr = nullptr;
    return true;
}

bool Stack::pop()
{
    bool result = false;
    if(!isEmpty()){
        Node<GraphEdge>* nodeToDeletePtr = topPtr;
        topPtr = topPtr->getNext();

        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;
        result = true;
    }
    return result;
}

void Stack::clear()
{
      while(!isEmpty()){
        pop();
    }
}

GraphEdge& Stack::peek() const
{
    assert(!isEmpty());

    return topPtr->getItem();
}
