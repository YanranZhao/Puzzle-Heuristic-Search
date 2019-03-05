//
// Created by yanra on 2018-10-24.
//

#ifndef INC_472A1_A_STAR_H
#define INC_472A1_A_STAR_H


#pragma once
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <queue>
#include "Node.h"

using namespace std;

struct CompareHammingDiss {
    bool operator()(Node const & p1, Node const & p2) {
        return (p1.hammingDis + p1.g_value) > (p2.hammingDis + p2.g_value);
    }
};

struct CompareManhattanDiss {
    bool operator()(Node const & p1, Node const & p2) {
        return (p1.manhattanDis + p1.g_value) > (p2.manhattanDis + p2.g_value);
    }
};

class Astar {
private:
    int puzzleWeight = 4;
    int puzzleHeight = 3;

    bool heuristic_one; //true for Hamming & false for Manhattan
    int zeroIndex;
    int hamming_value;
    int manhattan_value;
    int f_value;
    Node currentNode;
    Node furtherNode;
    bool success = false;

    //array<int, stateSize> currentState;
    char position[12] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l' };
    array<int, stateSize> goalState = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0 };

public:
    Astar() {};
    Astar(Node);
    ~Astar() {};

    void runH1();
    void runH2();
    void ZeroIndex();
    void FindNextNode(Node&);
    bool isGoal(Node);
    void printNodePosition(Node);
    Node swapNodeElement(Node&, int, int);
    void movementUP(Node, int);
    void movementUP_RIGHT(Node, int);
    void movementRIGHT(Node, int);
    void movementDOWN_RIGHT(Node, int);
    void movementDOWN(Node, int);
    void movementDOWN_LEFT(Node, int);
    void movementLEFT(Node, int);
    void movementUP_LEFT(Node, int);

    int CountingHamming(Node, array<int, stateSize>);
    int CountingManhattan(Node);

    priority_queue<Node, vector<Node>, CompareHammingDiss> openCaseH1;
    priority_queue<Node, vector<Node>, CompareHammingDiss> closeCaseH1;

    priority_queue<Node, vector<Node>, CompareManhattanDiss> openCaseH2;
    priority_queue<Node, vector<Node>, CompareManhattanDiss> closeCaseH2;

};

#endif //INC_472A1_A_STAR_H
