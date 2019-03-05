#include "A_star.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

Astar::Astar(Node node) {
    this->currentNode = node;
    //for (int i = 0; i < 12 ; i++) {
    //	currentNode.state[i] = node.state[i];
    //}
    //currentNode.Astar = true;

    //double heig = sqrt(stateSize);
    //puzzleHeight = int(floor(heig));
    //puzzleWeight = abs(stateSize / puzzleHeight);
}

void Astar::ZeroIndex() {
    for (int c = 0; c < currentNode.state.size(); c++) {
        if (currentNode.state[c] == 0) {
            this->zeroIndex = c;
            break;
        }
    }
}

//There are nine different positions in a puzzle
//Each position can do multiple moves
void Astar::FindNextNode(Node &current) {
    ZeroIndex(); //finding index of 0
    //first line ^ on left side
    if(zeroIndex == 0){
        //if (zeroIndex < puzzleWeight && ((zeroIndex + 1) % puzzleWeight == 1)) {
        movementRIGHT(current, zeroIndex);
        movementDOWN_RIGHT(current, zeroIndex);
        movementDOWN(current, zeroIndex);
    }
        //first line ^ not on right side ^ not on left side
    else if (zeroIndex == 1 || zeroIndex == 2) {
        //else if ((zeroIndex < puzzleWeight)
        //	&& (zeroIndex + 1) % puzzleWeight != 0
        //	&& (zeroIndex + 1) % puzzleWeight != 1) {
        movementRIGHT(current, zeroIndex);
        movementDOWN_RIGHT(current, zeroIndex);
        movementDOWN(current, zeroIndex);
        movementDOWN_LEFT(current, zeroIndex);
        movementLEFT(current, zeroIndex);
    }
        //first line ^ on right side
    else if (zeroIndex == 3) {
        //else if ((zeroIndex < puzzleWeight) && (zeroIndex + 1) % puzzleWeight == 0) {
        movementDOWN(current, zeroIndex);
        movementDOWN_LEFT(current, zeroIndex);
        movementLEFT(current, zeroIndex);
    }
        //middle line ^ on left side
    else if (zeroIndex == 4) {
        //else if ((zeroIndex >= puzzleWeight)
        //&& zeroIndex < (stateSize - puzzleWeight)
        //&& (zeroIndex + 1) % puzzleWeight == 1) {
        movementUP(current, zeroIndex);
        movementUP_RIGHT(current, zeroIndex);
        movementRIGHT(current, zeroIndex);
        movementDOWN_RIGHT(current, zeroIndex);
        movementDOWN(current, zeroIndex);
    }
        //center position
    else if(zeroIndex == 5 || zeroIndex == 6){
        //else if ((zeroIndex >= puzzleWeight) && zeroIndex < (stateSize - puzzleWeight)
        //&& (zeroIndex + 1) % puzzleWeight != 0 && (zeroIndex + 1) % puzzleWeight != 1) {
        movementUP(current, zeroIndex);
        movementUP_RIGHT(current, zeroIndex);
        movementRIGHT(current, zeroIndex);
        movementDOWN_RIGHT(current, zeroIndex);
        movementDOWN(current, zeroIndex);
        movementDOWN_LEFT(current, zeroIndex);
        movementLEFT(current, zeroIndex);
        movementUP_LEFT(current, zeroIndex);
    }
        //middle line ^ on right side
    else if (zeroIndex == 7) {
        //else if ((zeroIndex >= puzzleWeight)
        //&& zeroIndex < (stateSize - puzzleWeight)
        //&& (zeroIndex + 1) % puzzleWeight == 0) {
        movementUP(current, zeroIndex);
        movementDOWN(current, zeroIndex);
        movementDOWN_LEFT(current, zeroIndex);
        movementLEFT(current, zeroIndex);
        movementUP_LEFT(current, zeroIndex);
    }
        //last line ^ on left side
    else if (zeroIndex == 8) {
        //else if (zeroIndex >= (stateSize - puzzleWeight) && (zeroIndex + 1) % puzzleWeight == 1) {
        movementUP(current, zeroIndex);
        movementUP_RIGHT(current, zeroIndex);
        movementRIGHT(current, zeroIndex);
    }
        //last line ^ not on right side ^ not on left side
    else if (zeroIndex == 9 || zeroIndex == 10) {
        //else if (zeroIndex >= (stateSize - puzzleWeight)
        //&& (zeroIndex + 1) % puzzleWeight != 0
        //&& (zeroIndex + 1) % puzzleWeight != 1) {
        movementUP(current, zeroIndex);
        movementUP_RIGHT(current, zeroIndex);
        movementRIGHT(current, zeroIndex);
        movementLEFT(current, zeroIndex);
        movementUP_LEFT(current, zeroIndex);
    }
        //last line ^ on right side
    else if (zeroIndex == 11) {
        //else if (zeroIndex >= (stateSize - puzzleWeight) && (zeroIndex + 1) % puzzleWeight == 0) {
        movementUP(current, zeroIndex);
        movementLEFT(current, zeroIndex);
        movementUP_LEFT(current, zeroIndex);
    }

}

//========= CHECK MOVEMENT =========================

void Astar::movementUP(Node curr, int zeroIndex) {
    this->furtherNode = swapNodeElement(curr, zeroIndex, zeroIndex - puzzleWeight);
    this->furtherNode.setGValue(curr.getGValue() + 1);
    // check which method is using
    if (heuristic_one == true) {
        this->furtherNode.setH1Value(CountingHamming(furtherNode, goalState));
        openCaseH1.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
        //closeCaseH1.push(curr);
    }
    else {
        this->furtherNode.setH2Value(CountingManhattan(furtherNode));
        openCaseH2.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
        //closeCaseH2.push(curr);
    }
    //curr.setParentNode(curr*);
}

void Astar::movementUP_RIGHT(Node curr, int zeroIndex) {
    this->furtherNode = swapNodeElement(curr, zeroIndex, (zeroIndex - puzzleWeight + 1));
    this->furtherNode.setGValue(curr.getGValue() + 1);
    // check which method is using
    if (heuristic_one == true) {
        this->furtherNode.setH1Value(CountingHamming(furtherNode, goalState));
        openCaseH1.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
    }
    else {
        this->furtherNode.setH2Value(CountingManhattan(furtherNode));
        openCaseH2.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
    }
}

void Astar::movementRIGHT(Node curr, int zeroIndex) {
    this->furtherNode = swapNodeElement(curr, zeroIndex, (zeroIndex + 1));
    this->furtherNode.setGValue(curr.getGValue() + 1);
    // check which method is using
    if (heuristic_one == true) {
        this->furtherNode.setH1Value(CountingHamming(furtherNode, goalState));
        openCaseH1.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
    }
    else {
        this->furtherNode.setH2Value(CountingManhattan(furtherNode));
        openCaseH2.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
    }
}

void Astar::movementDOWN_RIGHT(Node curr, int zeroIndex) {
    this->furtherNode = swapNodeElement(curr, zeroIndex, (zeroIndex + puzzleWeight + 1));
    this->furtherNode.setGValue(curr.getGValue() + 1);
    // check which method is using
    if (heuristic_one == true) {
        this->furtherNode.setH1Value(CountingHamming(furtherNode, goalState));
        openCaseH1.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
    }
    else {
        this->furtherNode.setH2Value(CountingManhattan(furtherNode));
        openCaseH2.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
    }
}

void Astar::movementDOWN(Node curr, int zeroIndex) {
    this->furtherNode = swapNodeElement(curr, zeroIndex, (zeroIndex + puzzleWeight));
    this->furtherNode.setGValue(curr.getGValue() + 1);
    // check which method is using
    if (heuristic_one == true) {
        this->furtherNode.setH1Value(CountingHamming(furtherNode, goalState));
        openCaseH1.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
    }
    else {
        this->furtherNode.setH2Value(CountingManhattan(furtherNode));
        openCaseH2.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
    }
}

void Astar::movementDOWN_LEFT(Node curr, int zeroIndex) {
    this->furtherNode = swapNodeElement(curr, zeroIndex, (zeroIndex + puzzleWeight - 1));
    this->furtherNode.setGValue(curr.getGValue() + 1);
    // check which method is using
    if (heuristic_one == true) {
        this->furtherNode.setH1Value(CountingHamming(furtherNode, goalState));
        openCaseH1.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
    }
    else {
        this->furtherNode.setH2Value(CountingManhattan(furtherNode));
        openCaseH2.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
    }
}

void Astar::movementLEFT(Node curr, int zeroIndex) {
    this->furtherNode = swapNodeElement(curr, zeroIndex, (zeroIndex - 1));
    this->furtherNode.setGValue(curr.getGValue() + 1);
    // check which method is using
    if (heuristic_one == true) {
        this->furtherNode.setH1Value(CountingHamming(furtherNode, goalState));
        openCaseH1.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
    }
    else {
        this->furtherNode.setH2Value(CountingManhattan(furtherNode));
        openCaseH2.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
    }
}

void Astar::movementUP_LEFT(Node curr, int zeroIndex) {
    this->furtherNode = swapNodeElement(curr, zeroIndex, (zeroIndex - puzzleWeight - 1));
    this->furtherNode.setGValue(curr.getGValue() + 1);
    // check which method is using
    if (heuristic_one == true) {
        this->furtherNode.setH1Value(CountingHamming(furtherNode, goalState));
        openCaseH1.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
    }
    else {
        this->furtherNode.setH2Value(CountingManhattan(furtherNode));
        openCaseH2.push(furtherNode);
        //currentNode.addChildrenNode(this->furtherNode);
    }
}

//========= Algorithm For Hamming Method ==============
int Astar::CountingHamming(Node curr, array<int, stateSize> goal) {
    hamming_value = 0;

    for (int k = 0; k < curr.state.size(); k++) {
        if (curr.state[k] != goal[k] && curr.state[k] != 0) {
            hamming_value++;
        }
    }
    return hamming_value;
}

//========= Algorithm For Manhattan Method ==============
int Astar::CountingManhattan(Node curr) {
    manhattan_value = 0;
    for (int i = 0; i < curr.state.size(); ++i) {// ignore the blank square
        if (curr.state[i] != 0 && curr.state[i] != i + 1) {
            manhattan_value += abs((curr.state[i] - 1) / 3 - i / 3) + // distance of rows
                               abs((curr.state[i] - 1) % 3 - i % 3);  // distance of columns
        }
    }
    return 0;
}

//======================================================

bool Astar::isGoal(Node curr) {
    for (int i = 0; i < stateSize; i++)
    {
        if (curr.state[i] != goalState[i]) {
            return false;
        }
    }
    return true;
}

void Astar::printNodePosition(Node node) {
    ZeroIndex();
    if (node.getGValue() == 0) {
        cout << "0, [";
    }
    else {
        cout << position[zeroIndex] << ", [";
    }
    node.print();
    cout << "]" << endl;
}

Node Astar::swapNodeElement(Node& node, int n, int m) {
    int temp = node.state[n];
    node.state[n] = node.state[m];
    node.state[m] = temp;
    return node;
}

/////////////////RUN FIRST HEURISTIC///////////////////////////
void Astar::runH1() {
    Node* npt;
    heuristic_one = true;

    if (openCaseH1.empty()) {
        currentNode.setH1Value(CountingHamming(currentNode, goalState));
        currentNode.setGValue(0);
        openCaseH1.push(currentNode);
        ZeroIndex();
        //cout << "0, [";
        //this->currentNode.print();
        //cout << "]" << endl;
        npt = &currentNode;
        //currentNode.setParentNode(npt);

        success = false;
    }

    ofstream myfile("D:\\CLion-workspace\\472a1\\puzzleAStar-h1.txt", ios::trunc);

    if (myfile.is_open()) {

        while (!openCaseH1.empty() && !success) {

            //if current state is goal then return success
            if (isGoal(currentNode)) {
                success = true;
                cout << "success" << endl;
                myfile.close();
            }
            else {
                currentNode = openCaseH1.top();
                //remove leftmost state from open list, and add it into close;
                closeCaseH2.push(openCaseH1.top());
                ZeroIndex();
                if (openCaseH1.top().g_value == 0) {
                    myfile << "0, [";
                    cout << "0, [";
                }
                else {
                    myfile << position[zeroIndex] << ", [";
                    cout << position[zeroIndex] << ", [";
                }
                for (int i = 0; i < 12; i++) {
                    myfile << currentNode.state[i] << ", ";
                    cout << currentNode.state[i] << ", ";
                }
                myfile << "]" << endl;
                cout << "]" << endl;
                openCaseH1.pop();
                FindNextNode(currentNode);
            }

            //write current visited state into txt file

        }
    }
}

/////////////////RUN SECOND HEURISTIC///////////////////////////
void Astar::runH2() {
    Node* npt;
    this->heuristic_one = false;

    if (openCaseH2.empty()) {
        currentNode.setH2Value(CountingManhattan(currentNode));
        currentNode.setGValue(0);
        openCaseH2.push(currentNode);
        /*cout << "0, [";
        this->currentNode.print();
        cout << "]" << endl;*/
        npt = &currentNode;
        //currentNode.setParentNode(npt);
        ZeroIndex();
        success = false;
    }

    ofstream myfile("D:\\CLion-workspace\\472a1\\puzzleAStar-h2.txt", ios::trunc);

    if (myfile.is_open()) {

        while (!openCaseH2.empty() && !success) {
            //printNodePosition();

            //if current state is goal then return success
            if (isGoal(currentNode)) {
                success = true;
                cout << "success" << endl;
                myfile.close();
            }
            else {
                currentNode = openCaseH2.top();
                //remove leftmost state from open list, and add it into close;
                closeCaseH2.push(openCaseH2.top());
                ZeroIndex();
                if (openCaseH2.top().g_value == 0) {
                    myfile << "0, [";
                    cout << "0, [";
                }
                else {
                    myfile << position[zeroIndex] << ", [";
                    cout << position[zeroIndex] << ", [";
                }
                for (int i = 0; i < 12; i++) {
                    myfile << currentNode.state[i] << ", ";
                    cout << currentNode.state[i] << ", ";
                }
                myfile << "]" << endl;
                cout << "]" << endl;
                openCaseH2.pop();
                FindNextNode(currentNode);

                //printNodePosition(openCaseH2.top());
            }

            //write current visited state into txt file

        }

    }

}


