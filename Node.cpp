//
// Created by yanra on 2018-10-11.
//

#include <iostream>
#include "Node.h"

Node::Node() {}

Node::Node(array<int, stateSize> arr){
    for(int i=0;i<stateSize;i++){
        state[i]=arr[i];
    }
    for(int i=0;i<stateSize;i++){
        if(state[i]!=goalState[i])
            hammingDis++;
    }
}

Node::Node(array<int, stateSize> arr, bool astar) {
    //Astar = astar;
    for (int i = 0; i<stateSize; i++) {
        state[i] = arr[i];
    }
    if (Astar = true) {
        g_value = 0;
        hammingDis = 0;
        manhattanDis = 0;
    }
};

Node::~Node() {}