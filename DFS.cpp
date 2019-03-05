//
// Created by yanra on 2018-10-13.
//

#include "DFS.h"
#include <iostream>
#include <fstream>

using namespace std;
#define stateSize 12

DFS::DFS() {}

DFS::~DFS() {}

//initial the father node, set the depth is zero
DFS::DFS(Node node) {
    initialNode = node;
    initialNode.setGValue(0);
    for (int i = 0; i < stateSize; i++) {
        initialNode.state[i] = node.state[i];
    }
}

//print the visited state
void DFS::print() {
    zeroPosition();
    //0 then the initial configuration
    if (isEqual(currentNode.state, initialNode.state, currentNode.state.size(), initialNode.state.size()))
        cout << "0 [";
    else
        cout << position[zero] << " [";

    for (int i = 0; i < stateSize - 1; i++) {
        cout << currentNode.state[i] << ", ";
    }
    cout << currentNode.state[stateSize - 1] << "]" << endl;
}

//find the index of integer 0
void DFS::zeroPosition() {
    for (int i = 0; i < stateSize; i++) {
        if (currentNode.state[i] == 0) {
            zero = i;
            break;
        }
    }
}

//if two arrays are equal, return true;
bool DFS::isEqual(array<int, stateSize> arr1, array<int, stateSize> arr2, int n, int m) {
    if (n != m)
        return false;
    for (int i = 0; i < stateSize; i++) {
        if (arr1[i] != arr2[i])
            return false;
    }
    return true;
}

//help method: if the state is not existed in close list return true;
bool DFS::existedInClosed(array<int, stateSize> arr, vector<Node> closeList) {
    for (int i = 0; i < closeList.size(); i++) {
        if (isEqual(arr, closeList[i].state, arr.size(), closeList[i].state.size()))
            return true;
    }
    return false;
}

//if the state is equal to goal state, return true
bool DFS::isGoal(array<int, stateSize> arr) {
    for (int i = 0; i < stateSize; i++) {
        if (arr[i] != goalState[i]) {
            return false;
        }
    }
    return true;
}

//help method to copy array
void DFS::copyArray(array<int, stateSize> arr1, array<int, stateSize> &arr2) {
    for (int i = 0; i < stateSize; ++i)
        arr2[i] = arr1[i];
}

//help method to copy node
void DFS::copyArray(Node node1, Node &node2) {
    for (int i = 0; i < stateSize; ++i)
        node2.state[i] = node1.state[i];
    node2.setGValue(node1.getGValue());
}

//help method to swap element of an array
void DFS::swapElement(array<int, stateSize> &arr, int n, int m) {
    int temp = arr[n];
    arr[n] = arr[m];
    arr[m] = temp;
}

//help method to generate state child
void DFS::generateChild(int zero, int newZero, int depth) {
    Node temp;
    copyArray(currentNode, temp);
    swapElement(temp.state, zero, newZero);
    temp.setGValue(currentNode.getGValue() + 1);
    //if not in closed
    if (!existedInClosed(temp.state, closeList))
        openList.insert(openList.begin(), temp);
}


void DFS::run(int depth) {
    if (openList.empty()) {
        openList.push_back(initialNode);
    }
    success = false;

    ofstream myfile("D:\\CLion-workspace\\472a1\\puzzleDFS.txt", ios::trunc);

    do {
        copyArray(openList.front(), currentNode);
        print();

        //write current visited state into txt file
        if (myfile.is_open()) {
            if(isEqual(currentNode.state, initialNode.state, currentNode.state.size(), initialNode.state.size()))
                myfile << "0 [";
            else
                myfile << position[zero] << " [";

            for (int i = 0; i < stateSize - 1; i++) {
                myfile << currentNode.state[i] << ", ";
            }
            myfile << currentNode.state[stateSize - 1] << "]" << endl;
        }

        //remove leftmost state from open list, and add it into close;
        closeList.push_back(openList.front());
        openList.erase(openList.begin());

        //if current state is goal then return success
        if (isGoal(currentNode.state)) {
            success = true;
            cout << "success" << endl;
            break;
        }
        //if current state is equal to depth, it won't generate children
        if (currentNode.getGValue() != depth) {
            //generate child of current state
            zeroPosition(); //finding index of 0
            //up-left
            if (zero > 4 && zero != 8)
                generateChild(zero, zero - 5, depth);
            //left
            if (zero != 0 && zero != 4 && zero != 8)
                generateChild(zero, zero - 1, depth);
            //down-left
            if (zero != 0 && zero != 4 && zero < 8)
                generateChild(zero, zero + 3, depth);
            //down
            if (zero < 8)
                generateChild(zero, zero + 4, depth);
            //down-right
            if (zero != 3 && zero < 7)
                generateChild(zero, zero + 5, depth);
            //right
            if (zero != 3 && zero != 7 && zero != 11)
                generateChild(zero, zero + 1, depth);
            //up-right
            if (zero > 3 && zero != 7 && zero != 11)
                generateChild(zero, zero - 3, depth);
            //up
            if (zero > 4)
                generateChild(zero, zero - 4, depth);
            //zero
            if (zero < 0 || zero > 11)
                cout << "ERROR: not a valid child" << endl;
        }
        if (openList.empty()) {
            cout << "fail" << endl;
        }
    } while (!openList.empty() && !success);
    //printList();
    myfile.close();
}

//help method to print open list and close lit
void DFS::printList() {
    cout << "open list are:" << endl;
    for (auto &i : openList) {
        for (auto &k : i.state) {
            cout << k << " ";
        }
        cout << "depth:" << i.getGValue() << endl;
    }

    cout << endl << "close list are:" << endl;
    for (auto &i : closeList) {
        for (auto &k : i.state) {
            cout << k << " ";
        }
        cout << "depth:" << i.getGValue() << endl;
    }
}

