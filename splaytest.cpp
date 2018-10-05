#include <iostream>
#include <vector>
#include <ctime>
#include "stdlib.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include "splay_tree.h"

using namespace std;

int main(int argc, char* argv[]){

	SplayTree<int, int> myTree;

	myTree.insert(make_pair(1, 1));
    myTree.print();
    myTree.insert(make_pair(2, 2));
    myTree.print();
    // myTree.insert(make_pair(3, "3"));
    // myTree.print();
    // myTree.insert(make_pair(4, "4"));
    // myTree.print();
    // myTree.insert(make_pair(5, "5"));
    // myTree.print();
    // myTree.insert(make_pair(6, "6"));
    // myTree.print();
    

	return 0;
}