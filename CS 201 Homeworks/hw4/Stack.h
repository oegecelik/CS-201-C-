/*
Name: Orhun Ege Çelik
Section: 3
Student Number: 22202321
*/


//ADT stack: Link based implementation, mostly from the slides.

#ifndef STACK
#define STACK

#include "Node.h"
#include "GraphEdge.h"
class Stack{
    private:
        Node<GraphEdge>* topPtr;
    public:
        Stack();
        Stack(const Stack& aStack);
        ~Stack();
        Stack& operator = (const Stack& aStack);

        bool isEmpty() const;
        bool push(const GraphEdge& newItem);
        bool pop();
        void clear();
        GraphEdge& peek() const;
};

#endif