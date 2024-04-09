/*
Name: Orhun Ege Çelik
Course Code: CS 201
Section: 3
Student Number: 22202321
*/

#ifndef NODE_
#define NODE_

template <class ItemType>
class Node
{
    private:
        ItemType item;
        Node<ItemType>* next;
    public:
        Node();
        ~Node();
        Node(const ItemType& anItem);
        Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
        void setItem(const ItemType& anItem);
        void setNext(Node<ItemType>* nextNodePtr);
        ItemType& getItem();
        Node<ItemType>* getNext() const;
};

#endif

