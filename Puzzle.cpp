//
// Created by yanran on 2018-10-08.
//

#include "Puzzle.h"
#include <iostream>

using namespace std;
#define stateSize 12


Puzzle::Puzzle() {}
Puzzle::~Puzzle() {}

Puzzle::Puzzle(array<int, stateSize> arr) {
    int i;
    for(i=0;i<stateSize;i++){
        state[i]=arr[i];
    }
}

void Puzzle::print() {
    int i;
    zeroPosition();
    //cout<<"current visited state is:" <<endl;
    cout<<position[zero]<<" [";
    for(i=0;i<stateSize-1;i++){
        cout<<state[i]<<", ";
    }
    cout<<state[stateSize-1]<<"]"<<endl;
}

void Puzzle::zeroPosition() {
    for (int i = 0; i < stateSize; i++)
    {
        if (state[i]==0){
            zero = i;
            break;
        }
    }
}

bool Puzzle::isEqual(array<int, stateSize> arr1, array<int, stateSize> arr2, int n, int m) {
    if (n != m)
        return false;
    for(int i=0;i<stateSize;i++){
        if(arr1[i]!=arr2[i])
           return false;
    }
    return true;
}

bool Puzzle::existedInClosed(array<int, stateSize> arr, vector<array<int, stateSize>> closeList) {

    for(int i=0;i<closeList.size();i++){
        if(isEqual(arr, closeList[i], arr.size(),closeList[i].size()))
            return true;
    }
    return false;
}

bool Puzzle::isGoal(array<int, stateSize> arr) {
    for (int i = 0; i < stateSize; i++)
    {
        if (arr[i]!=goalState[i]){
            return false;
        }
    }
    return true;
}

void Puzzle::copyArray(array<int, stateSize> arr1, array<int, stateSize>& arr2) {
    for(int i=0; i<stateSize; ++i)
        arr2[i] = arr1[i];
}

void Puzzle::swapElement(array<int, stateSize> & arr, int n, int m) {
    int temp = arr[n];
    arr[n] = arr[m];
    arr[m] = temp;
}

void Puzzle::generateChild(int zero, int newZero) {
    array<int, stateSize> temp;
    copyArray(state, temp);
    swapElement(temp, zero, newZero);
    //if not in closed
    if (!existedInClosed(temp, closeList))
        openList.insert(openList.begin(), temp);
}

void Puzzle::run() {
    if (openList.empty()) {
        openList.push_back(state);
    }
    success = false;
    ofstream myfile ("D:\\CLion-workspace\\472a1\\puzzleDFS.txt");
    //following pesudo code in Slice
    while (!openList.empty() && !success) {
        //remove leftmost state from open, and add it into close;
        copyArray(openList.front(), state);
        print();
        //write current state into txt file
        if(myfile.is_open()){
            myfile << position[zero]<<" [";
            for(int i=0;i<stateSize-1;i++){
                myfile<<state[i]<<", ";
            }
            myfile <<state[stateSize-1]<<"]"<<endl;
        }
        closeList.push_back(openList.front());
        openList.erase(openList.begin());

        //if Xstate is goal then return success
        if (isGoal(state)) {
            success = true;
            cout << "success" << endl;
        } else {
            //generate child of Xstate
            zeroPosition(); //finding index of 0
            //up-left
            if (zero > 4 && zero != 8)
                generateChild(zero, zero-5);
            //left
            if(zero !=0 && zero != 4 && zero !=8)
                generateChild(zero, zero-1);
            //down-left
            if(zero !=0 && zero !=4 && zero<8)
                generateChild(zero, zero+3);
            //down
            if(zero<8)
                generateChild(zero, zero+4);
            //down-right
            if(zero !=3 && zero<7)
                generateChild(zero, zero+5);
            //right
            if(zero!=3 && zero !=7 && zero !=11)
                generateChild(zero, zero+1);
            //up-right
            if(zero >3 && zero != 7 && zero != 11)
                generateChild(zero, zero-3);
            //up
            if(zero>4)
                generateChild(zero, zero-4);
        }
    }
    //printList();
    myfile.close();
}

void Puzzle::printList() {
    cout<<"open list are:"<<endl;
    for(auto& i : openList) {
        for(auto& k : i) {
            cout << k <<" " ;
        }
        cout<<endl;
    }

    cout<<endl<<"close list are:"<<endl;
    for(auto& i : closeList) {
        for(auto& k : i) {
            cout << k <<" " ;
        }
        cout<<endl;
    }
}

