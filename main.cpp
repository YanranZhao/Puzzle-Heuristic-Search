
#include <iostream>
#include "Node.h"
#include "BFS.h"
#include "DFS.h"
#include "A_Star.h"

using namespace std;


int main() {
    array<int, stateSize> arr={0, 1, 2, 3, 5, 6, 7, 4, 9, 10, 11, 8};
    //array<int, stateSize> arr={1,2,3,5,0,6,7,4,9,10,11,8};

    int count;
    for(int i=0;i<stateSize;i++){
        if(arr[i]==0)
            count++;
    }
    if(count!=1)
        cout<<"Wrong puzzle: more than one 0 inside, please set array again"<<endl;
    else{
/*        Node node(arr);
        BFS bfs (node);
        //bfs.runH1();
        bfs.runH2();*/

/*        DFS dfs (node);
        dfs.run(5);*/

        Node node1(arr, true);
        Astar ast(node1);
        //ast.runH1();
        ast.runH2();
    }


    return 0;
}