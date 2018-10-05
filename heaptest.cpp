#include <iostream>
#include <vector>
#include <ctime>
#include "stdlib.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include "heap.h"

using namespace std;

int main(int argc, char* argv[]){

    Heap<int> myHeap(2); //= Heap<int>Heap(2);

    if(myHeap.empty() == true){
        cout << "heap is initially empty" << endl;
    }
    myHeap.push(11);
    //3 should be the top
    myHeap.push(6);
    myHeap.push(5);
    myHeap.push(4);
    myHeap.push(3);
    myHeap.push(2);

    //MIN HEAP (LESS THAN)
    // cout << "expect 3,7,5,15,20,10 " << endl;
    // cout << "pop " << myHeap.top() << endl;
    // myHeap.pop();
    // cout << "pop " << myHeap.top() << endl;
    // myHeap.pop();
    // cout << "pop " << myHeap.top() << endl;
    // myHeap.pop();
    // cout << "pop " << myHeap.top() << endl;
    // myHeap.pop();
    // cout << "pop " << myHeap.top() << endl;
    // myHeap.pop();
    // cout << "pop " << myHeap.top() << endl;
    // myHeap.pop();

    myHeap.decreaseKey(11,1);
    cout << myHeap.top() << endl;
    myHeap.pop();
    cout << myHeap.top() << endl;
    myHeap.pop();
    cout << myHeap.top() << endl;
    myHeap.pop();
    cout << myHeap.top() << endl;
    myHeap.pop();
    cout << myHeap.top() << endl;
    myHeap.pop();
    cout << myHeap.top() << endl;
    myHeap.pop();
    

 

    if(myHeap.empty() == true){
        cout << "heap empty" << endl;
    }



   
    return 0;
}