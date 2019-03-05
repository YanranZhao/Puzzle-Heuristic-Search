//
// Created by yanra on 2018-10-12.
//

#ifndef INC_472A1_BFS_H
#define INC_472A1_BFS_H
#include <array>
#include <queue>
#include "Node.h"
using namespace std;
#define stateSize 12

struct CompareHammingDis {
    bool operator()(Node const & p1, Node const & p2) {
        return p1.hammingDis > p2.hammingDis;
    }
};

struct CompareManhattanDis {
    bool operator()(Node const & p1, Node const & p2) {
        return p1.manhattanDis > p2.manhattanDis;
    }
};

class BFS {
public:
    BFS();
    BFS(Node);
    ~BFS();

    void print(Node, int);
    void printList();
    void printListH2();
    void zeroPosition();

    bool isEqual(array<int, stateSize>, array<int, stateSize>, int, int);
    bool isGoal(array<int, stateSize>);
    void copyArray(array<int, stateSize>,array<int, stateSize>&);
    void swapElement(array<int, stateSize>&, int, int);

    bool existedInClosed(array<int, stateSize>,priority_queue<Node, vector<Node>, CompareHammingDis>);
    bool existedInClosedH2(array<int, stateSize>,priority_queue<Node, vector<Node>, CompareManhattanDis>);
    int checkHammingDis(Node);
    int checkManhattanDis(Node);
    void generateChild(int, int);
    void generateChildH2(int, int);
    void runH1();
    void runH2();


    Node initialNode;
    array<int, stateSize> currentState;
    array<int, stateSize> goalState = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0};
    array<char, stateSize> position = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
    int zeroIndex;
    bool success;

    priority_queue<Node, vector<Node>, CompareHammingDis> openListH1;
    priority_queue<Node, vector<Node>, CompareHammingDis> closeListH1;

    priority_queue<Node, vector<Node>, CompareManhattanDis> openListH2;
    priority_queue<Node, vector<Node>, CompareManhattanDis> closeListH2;

};


#endif //INC_472A1_BFS_H
