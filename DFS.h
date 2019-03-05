//
// Created by yanra on 2018-10-13.
//

#ifndef INC_472A1_DFS_H
#define INC_472A1_DFS_H
#include <vector>
#include <array>
#include "Node.h"
using namespace std;
#define stateSize 12

class DFS {
public:
    DFS();
    DFS(Node);
    ~DFS();

    void print();
    void zeroPosition();
    void printList();

    bool isEqual(array<int, stateSize>, array<int, stateSize>, int n, int m);
    bool existedInClosed(array<int, stateSize>,vector<Node>);
    bool isGoal(array<int, stateSize>);
    void copyArray(array<int, stateSize>,array<int, stateSize>&);
    void swapElement(array<int, stateSize>&, int n, int m);
    void run(int);
    void generateChild(int, int, int);

    void copyArray(Node, Node&);

    Node initialNode;
    Node currentNode;
    array<int, stateSize> goalState = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0};
    array<char, stateSize> position = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
    int zero;
    bool success;

    vector<Node> openList;
    vector<Node> closeList;

};


#endif //INC_472A1_DFS_H
