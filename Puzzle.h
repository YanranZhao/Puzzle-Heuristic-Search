//
// Created by yanra on 2018-10-08.
//

#ifndef INC_472A1_PUZZLE_H
#define INC_472A1_PUZZLE_H


#include <string>
#include <vector>
#include <array>
#include <fstream>
using namespace std;
#define stateSize 12

class Puzzle {
public:
    Puzzle();
    Puzzle(array<int, stateSize>);
    ~Puzzle();

    void print();
    void zeroPosition();
    void printList();

    bool isEqual(array<int, stateSize>, array<int, stateSize>, int n, int m);
    bool existedInClosed(array<int, stateSize>,vector<array<int, stateSize>>);
    bool isGoal(array<int, stateSize>);
    void copyArray(array<int, stateSize>,array<int, stateSize>&);
    void swapElement(array<int, stateSize>&, int n, int m);
    void run();
    void generateChild(int, int);


    array<int, stateSize> state;
    array<int, stateSize> goalState = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0};
    array<char, stateSize> position = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
    int zero;
    bool success;

    vector<array<int, stateSize>> openList;
    vector<array<int, stateSize>> closeList;



};


#endif //INC_472A1_PUZZLE_H
