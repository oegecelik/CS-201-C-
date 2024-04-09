/*
Name: Orhun Ege Çelik
Section: 3
Student Number: 22202321
*/

#ifndef GRAPH_EDGE_
#define GRAPH_EDGE_
#include "LinkedList.h"

class GraphEdge{
    public:
        GraphEdge();
        ~GraphEdge();
        GraphEdge(const GraphEdge& graphEdge);
        GraphEdge(string name, double prob);
        void addToList(GraphEdge* newAdjacent);
        const string getName();
        const double getProb(); 
        LinkedList<GraphEdge> adjacencyList;
        Node<GraphEdge>* curChild;   

    private:
        string name;
        int adjacentCount;
        double prob;             
};

#endif