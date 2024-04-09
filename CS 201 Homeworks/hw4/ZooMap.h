/*
Name: Orhun Ege Çelik
Section: 3
Student Number: 22202321
*/

#include "Stack.h"

class ZooMap {
public:
ZooMap(const string cageFile, const string zooFile);
~ZooMap();
void displayAllCages() const;
void displayAdjacentCages(const string cageName) const;
void displayZooMap() const;
void findSafestPath(const string startCage, const string endCage);
void findMostDangerousPath(const string startCage, const string endCage);
private:
    LinkedList<GraphEdge> zoo;
};