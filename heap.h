#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <iostream>
template <
         typename T,
         typename KComparator = std::equal_to<T>,
         typename PComparator = std::less<T>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const KComparator& kcomp = KComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item
    void push(const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey - Finds key matching old object &
    /// updates its location in the heap based on the new value
    void decreaseKey(const T& old, const T& newVal);

 private:
    /// Add whatever helper functions and data members you need below
    void trickleDown(int idx);
    void trickleUp(int loc);

  // PComparator comp;
  // std::vector<T> store_;
  // int m;
  // std::less<T> c = std::less<T>();

 private:
   /// Data members - These should be sufficient
    std::vector< T > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, KComparator> keyToLocation_;

};

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
Heap<T,KComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const KComparator& kcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, kcomp)

{

}

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
Heap<T,KComparator,PComparator,Hasher>::~Heap()
{

}

// Incomplete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::push( const T& item)
{
    keyToLocation_.insert(std::make_pair(item, store_.size()));
    store_.push_back(item);
    trickleUp(store_.size()-1);
}

// Incomplete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::decreaseKey(const T& old, const T& newVal)
{
    if (c_(newVal, old))
    {

        int loc = keyToLocation_[old];
        keyToLocation_.erase(old);
        //keyToLocation_[newVal] = keyToLocation_[old];
        keyToLocation_.insert(std::make_pair(newVal, loc));
        store_[keyToLocation_[newVal]] = newVal;
        // store_.erase(keyToLocation_[old]);
        
        
        // if (keyToLocation_.find(old)== keyToLocation_.end())
        // {
        //   std::cout << "OLD ERASED PROPERLY" << std::endl;
        // }
        // std::cout << store_[keyToLocation_[newVal]] << std::endl;
        trickleUp(keyToLocation_[newVal]);
        //trickleUp
    }
   

}

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
T const & Heap<T,KComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }
    // If we get here we know the heap has at least 1 item
    // Add code to return the top element
    return store_[0];
}

// Incomplete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::pop()
{
    if(empty()){
        throw std::logic_error("can't pop an empty heap");
    }
    store_[0] = store_.back();
    // store_[store.size()] = store[0]; 
    store_.pop_back();
    trickleDown(0);


}

/// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
bool Heap<T,KComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}


template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::trickleDown(int j)
{
  unsigned int idx = j;
  //if already leaf node, return
  //a leaf node won't have both leftmost and rightmost children
  if( ((idx+1)*m_-(m_-1)) >= store_.size() && ((idx+1)*m_ ) >= store_.size()) return;
  //if not at leaf node, you're at a parent
  //look at all the children
  int betterChild = (idx+1)*m_-(m_-1);
    for(unsigned int i = (idx+1)*m_-(m_-1)+1; i < (idx+1)*m_+1; i++) //all the children
    {
      //if the child exists
      //compare the child with the small
      if (i<store_.size())
      {
        int child = i;

        //if (compare the child with the parent) returns false 
        //(false means parent is worse than child), then swap parent and child
        if(c_(store_[child], store_[betterChild]) )
        {
          betterChild = child;
        }
      }
      
    }

    //if parent is worse than child, swap parent and child
    if(c_(store_[betterChild], store_[idx]) )
    {
        keyToLocation_[store_[betterChild]] = idx;
        keyToLocation_[store_[idx]] = betterChild;
        std::swap(store_[idx], store_[betterChild]);
        // T temp = store_[idx];
        // store_[idx] = store_[betterChild];
        // store_[betterChild] = temp;
        trickleDown(betterChild);
    }  
}

template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::trickleUp(int loc)
{
  // could be implemented recursively
  int parent = (loc-1)/m_;
  while(parent >= 0 &&
    c_(store_[loc], store_[parent]))//parent is worse than child
  //store_[loc] < store_[parent] )
  { 
    keyToLocation_[store_[parent]] = loc;
    keyToLocation_[store_[loc]] = parent;
    std::swap(store_[parent], store_[loc]);
    // T temp = store_[parent];
    // store_[parent] = store_[loc];
    // store_[loc] = temp;
    loc = parent;
    parent = (loc-1)/m_;
  }
}


#endif

