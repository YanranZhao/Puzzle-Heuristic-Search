//
// Created by yanra on 2018-10-12.
//

#include "BFS.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

BFS::BFS(){}

BFS::BFS(Node node) {
    initialNode=node;
    for(int i=0;i<stateSize;i++)
        currentState[i]=node.state[i];
}

BFS::~BFS() {}

//print the visited state
void BFS::print(Node node, int x) {
    int i;
    zeroPosition();
    //0 then the initial configuration
    if(isEqual(currentState, initialNode.state, currentState.size(), initialNode.state.size()))
        cout<<"0 [";
    else
        cout<<position[zeroIndex]<<" [";

    for(i=0;i<stateSize-1;i++){
        cout<<currentState[i]<<", ";
    }

    if(x==1)
        cout<<currentState[stateSize-1]<<"]"<<" H1:"<<checkHammingDis(node)<<endl;
    if(x==2)
        cout<<currentState[stateSize-1]<<"]"<<" H2:"<<checkManhattanDis(node)<<endl;
}

//find the index of integer 0
void BFS::zeroPosition() {
    for (int i = 0; i < stateSize; i++)
    {
        if (currentState[i]==0){
            zeroIndex = i;
            break;
        }
    }
}

//if two arrays are equal, return true;
bool BFS::isEqual(array<int, stateSize> arr1, array<int, stateSize> arr2, int n, int m) {
    if (n != m)
        return false;
    for(int i=0;i<stateSize;i++){
        if(arr1[i]!=arr2[i])
            return false;
    }
    return true;
}

//if the state is equal to goal state, return true
bool BFS::isGoal(array<int, stateSize> arr) {
    for (int i = 0; i < stateSize; i++)
    {
        if (arr[i]!=goalState[i]){
            return false;
        }
    }
    return true;
}

//help method to copy array
void BFS::copyArray(array<int, stateSize> arr1, array<int, stateSize>& arr2) {
    for(int i=0; i<stateSize; ++i)
        arr2[i] = arr1[i];
}

//help method to swap element of an array
void BFS::swapElement(array<int, stateSize> & arr, int n, int m) {
    int temp = arr[n];
    arr[n] = arr[m];
    arr[m] = temp;
}


//=================================H1 methods===========================================
//return hamming distance of the state
int BFS::checkHammingDis(Node node) {
    int count=0;
    for(int i=0;i<stateSize;i++){
        if(node.state[i]!=0 && node.state[i]!=goalState[i])
            count++;
    }
    return count;
}

//help method: if the state is not existed in close list return true;
bool BFS::existedInClosed(array<int, stateSize> arr, priority_queue<Node, vector<Node>, CompareHammingDis> closeListH1) {
    array<int, stateSize> tempArray;
    while (!closeListH1.empty()) {
        tempArray = closeListH1.top().state;
        if(isEqual(arr, tempArray, arr.size(), tempArray.size()))
            return true;
        //tempQuene.push(closeListH1.top());
        closeListH1.pop();
    }
    /* while (!tempQuene.empty()) {
         closeListH1.push(tempQuene.top());
         tempQuene.pop();
     }*/

    return false;
}

//help method to generate state child
void BFS::generateChild(int zero, int newZero) {
    Node temp;
    copyArray(currentState, temp.state);
    swapElement(temp.state, zero, newZero);
    temp.hammingDis = checkHammingDis(temp);
    //if not in closed
    if (!existedInClosed(temp.state, closeListH1))
        openListH1.push(temp);
}


void BFS::runH1() {
    if(openListH1.empty())
        openListH1.push(initialNode);
    success = false;

    ofstream myfile ("D:\\CLion-workspace\\472a1\\puzzleBFS-h1.txt", ios::trunc);

    while (!openListH1.empty() && !success) {
        copyArray(openListH1.top().state, currentState);
        print(openListH1.top(),1);

        //write current visited state into txt file
        if(myfile.is_open()){
            if(isEqual(currentState, initialNode.state, currentState.size(), initialNode.state.size()))
                myfile << "0 [";
            else
                myfile << position[zeroIndex]<<" [";

            for(int i=0;i<stateSize-1;i++){
                myfile<<currentState[i]<<", ";
            }
            myfile <<currentState[stateSize-1]<<"]"<<endl;
        }

        //remove leftmost state from open list, and add it into close;
        closeListH1.push(openListH1.top());
        openListH1.pop();

        //if current state is goal then return success
        if (isGoal(currentState)) {
            success = true;
            cout << "success" << endl;
        } else {
            //generate child of current state
            zeroPosition(); //finding index of 0
            //up-left
            if (zeroIndex > 4 && zeroIndex != 8)
                generateChild(zeroIndex, zeroIndex-5);
            //left
            if(zeroIndex !=0 && zeroIndex != 4 && zeroIndex !=8)
                generateChild(zeroIndex, zeroIndex-1);
            //down-left
            if(zeroIndex !=0 && zeroIndex !=4 && zeroIndex<8)
                generateChild(zeroIndex, zeroIndex+3);
            //down
            if(zeroIndex<8)
                generateChild(zeroIndex, zeroIndex+4);
            //down-right
            if(zeroIndex !=3 && zeroIndex<7)
                generateChild(zeroIndex, zeroIndex+5);
            //right
            if(zeroIndex!=3 && zeroIndex !=7 && zeroIndex !=11)
                generateChild(zeroIndex, zeroIndex+1);
            //up-right
            if(zeroIndex >3 && zeroIndex != 7 && zeroIndex != 11)
                generateChild(zeroIndex, zeroIndex-3);
            //up
            if(zeroIndex>4)
                generateChild(zeroIndex, zeroIndex-4);
            if(zeroIndex<0 || zeroIndex>11)
                cout<<"ERROR: not a valid child"<<endl;
        }
    }
    //printList();
    myfile.close();
}

//help method to print open list and close lit
void BFS::printList() {
    cout<<"open list are:"<<endl;
    while (!openListH1.empty())
    {
        Node temp;
        copyArray(openListH1.top().state,temp.state);
        temp.hammingDis = checkHammingDis(openListH1.top());

        openListH1.pop();
        for(auto& k : temp.state) {
            cout << k <<" " ;
        }
        cout<<" H1:" << temp.hammingDis<<endl;
    }

    cout<<endl<<"close list are:"<<endl;
    while (!closeListH1.empty())
    {
        Node temp;
        copyArray(closeListH1.top().state,temp.state);
        temp.hammingDis = checkHammingDis(closeListH1.top());
        closeListH1.pop();
        for(auto& k : temp.state) {
            cout << k <<" " ;
        }
        cout<<" H1:" << temp.hammingDis<<endl;
    }
}



//=============================H2 methods============================================
//return manhattan distance of the state
int BFS::checkManhattanDis(Node node) {
    int count =0;
    for (int i = 0; i < node.state.size(); i++) {
        if (node.state[i] != 0 && node.state[i] != i + 1)
            count += abs((node.state[i] - 1) / 4 - i / 4) + // distance of rows
                     abs((node.state[i] - 1) % 4 - i % 4);  // distance of columns
    }
    return count;
}


//help method: if the state is not existed in close list return true;
bool BFS::existedInClosedH2(array<int, stateSize> arr, priority_queue<Node, vector<Node>, CompareManhattanDis> closeListH2) {
    array<int, stateSize> tempArray;
    while (!closeListH2.empty()) {
        tempArray = closeListH2.top().state;
        if(isEqual(arr, tempArray, arr.size(), tempArray.size()))
            return true;
        closeListH2.pop();
    }
    return false;
}

//help method to generate state child
void BFS::generateChildH2(int zero, int newZero) {
    Node temp;
    copyArray(currentState, temp.state);
    swapElement(temp.state, zero, newZero);
    temp.manhattanDis = checkManhattanDis(temp);
    //if not in closed
    if (!existedInClosedH2(temp.state, closeListH2))
        openListH2.push(temp);
}

void BFS::runH2() {
    if(openListH2.empty())
        openListH2.push(initialNode);
    success = false;

    ofstream myfile ("D:\\CLion-workspace\\472a1\\puzzleBFS-h2.txt", ios::trunc);

    while (!openListH2.empty() && !success) {
        copyArray(openListH2.top().state, currentState);
        print(openListH2.top(),2);

        if(myfile.is_open()){
            if(isEqual(currentState, initialNode.state, currentState.size(), initialNode.state.size()))
                myfile << "0 [";
            else
                myfile << position[zeroIndex]<<" [";

            for(int i=0;i<stateSize-1;i++){
                myfile<<currentState[i]<<", ";
            }
            myfile <<currentState[stateSize-1]<<"]"<<endl;
        }

        closeListH2.push(openListH2.top());
        openListH2.pop();

        if (isGoal(currentState)) {
            success = true;
            cout << "success" << endl;
        } else {
            //generate child of Xstate
            zeroPosition(); //finding index of 0
            //up-left
            if (zeroIndex > 4 && zeroIndex != 8)
                generateChildH2(zeroIndex, zeroIndex-5);
            //left
            if(zeroIndex !=0 && zeroIndex != 4 && zeroIndex !=8)
                generateChildH2(zeroIndex, zeroIndex-1);
            //down-left
            if(zeroIndex !=0 && zeroIndex !=4 && zeroIndex<8)
                generateChildH2(zeroIndex, zeroIndex+3);
            //down
            if(zeroIndex<8)
                generateChildH2(zeroIndex, zeroIndex+4);
            //down-right
            if(zeroIndex !=3 && zeroIndex<7)
                generateChildH2(zeroIndex, zeroIndex+5);
            //right
            if(zeroIndex!=3 && zeroIndex !=7 && zeroIndex !=11)
                generateChildH2(zeroIndex, zeroIndex+1);
            //up-right
            if(zeroIndex >3 && zeroIndex != 7 && zeroIndex != 11)
                generateChildH2(zeroIndex, zeroIndex-3);
            //up
            if(zeroIndex>4)
                generateChildH2(zeroIndex, zeroIndex-4);
            //error
            if(zeroIndex<0 || zeroIndex>11)
                cout<<"ERROR: not a valid child"<<endl;
        }
    }
    //printListH2();
    myfile.close();
}

//help method to print open list and close lit
void BFS::printListH2() {
    cout<<"open list are:"<<endl;
    while (!openListH2.empty())
    {
        Node temp;
        copyArray(openListH2.top().state,temp.state);
        temp.manhattanDis = checkManhattanDis(openListH2.top());

        openListH2.pop();
        for(auto& k : temp.state) {
            cout << k <<" " ;
        }
        cout<<" H2:" << temp.manhattanDis<<endl;
    }

    cout<<endl<<"close list are:"<<endl;
    while (!closeListH2.empty())
    {
        Node temp;
        copyArray(closeListH2.top().state,temp.state);
        temp.manhattanDis = checkManhattanDis(closeListH2.top());
        closeListH2.pop();
        for(auto& k : temp.state) {
            cout << k <<" " ;
        }
        cout<<" H2:" << temp.manhattanDis<<endl;
    }
}