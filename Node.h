//
// Created by yanra on 2018-10-11.
//

#ifndef INC_472A1_STATE_H
#define INC_472A1_STATE_H

#include <array>
#include <iostream>
using namespace std;
#define stateSize 12

class Node {
public:
    Node();
    Node(array<int, stateSize>);
    Node(array<int, stateSize>, bool);
    ~Node();

    array<int, stateSize> state;
    array<int, stateSize> goalState = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0};

    void setGValue(int g) { g_value = g; }
    void setH1Value(int h1) { hammingDis = h1; }
    void setH2Value(int h2) { manhattanDis = h2; }
    int getGValue() { return g_value; }
    int getH1Value() { return hammingDis; }
    int getH2Value() { return manhattanDis; }
    void print() {
        for (int c = 0; c < stateSize; c++) {
            cout << state[c] << " ";
        }
    }

    int hammingDis = 0;
    int manhattanDis = 0;
    int g_value;
    bool Astar = false;
};


#endif //INC_472A1_STATE_H
