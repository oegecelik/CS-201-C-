/*
Name: Orhun Ege Çelik
Section: 3
Student Number: 22202321
*/

#include "GraphEdge.h"

GraphEdge::GraphEdge()
{
}

GraphEdge::~GraphEdge()
{
}

GraphEdge::GraphEdge(const GraphEdge &graphEdge)
{
    name = graphEdge.name;
    adjacentCount = graphEdge.adjacentCount;
    prob = graphEdge.prob;
    curChild = graphEdge.adjacencyList.headPtr;
    adjacencyList = graphEdge.adjacencyList;
}

GraphEdge::GraphEdge(string name, double prob) : curChild(nullptr), name(name),  adjacentCount(0), prob(prob) {}

void GraphEdge::addToList(GraphEdge* address)
{
    adjacencyList.insert(address->getName(), address->getProb());
    adjacentCount++;
    if(adjacentCount == 1){
        curChild = adjacencyList.headPtr;
    }
}

const string GraphEdge::getName()
{
    return name;
}

const double GraphEdge::getProb()
{
    return prob;
}
