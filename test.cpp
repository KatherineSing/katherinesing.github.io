#include "merge.h"
using namespace std;
/* Function to print an array */

 
/* Driver program to test above functions */
int main()
{
    vector <int> v;
   
    v.push_back(5);
    v.push_back(4);
    v.push_back(3);
     v.push_back(2);
    v.push_back(1);
    
    
 
    std::less<int> comp;
    mergesort(v, comp);
    for(vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        cout << *it << " ";
    }
    
    return 0;
}
