/*
Name: Orhun Ege Çelik
Course Code: CS 201
Section: 3
Student Number: 22202321
*/

#include "Node.h"
#include "GraphEdge.h"
#include <cstddef>

template<class ItemType>
Node<ItemType>::Node() : next(nullptr){}

template <class ItemType>
Node<ItemType>::~Node()
{
    
}

template<class ItemType> 
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr){}

template <class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr):
    item(anItem), next(nextNodePtr){}

template <class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem){
    item = anItem;
}

template <class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr){
    next = nextNodePtr;
}

template <class ItemType>
ItemType& Node<ItemType>::getItem(){
    return item;
}

template <class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const{
    return next;
}

template class Node<GraphEdge>;
template class Node<GraphEdge*>;