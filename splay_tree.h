#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include "bst.h"

template<typename Key, typename Value>
class SplayTree : public BinarySearchTree<Key, Value>
{
 public:
	SplayTree();
	~SplayTree();

	// All of the basic operations that one would perform on a map. 
	// Do not change these function definitions, but you may add others
	void insert(const std::pair<Key, Value>& keyValuePair);
	void clear();
	// Prints the contents of the tree in a nice format. 
	//Useful for debugging.
	void print() const;

 public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    * TODO: You must implement this!
    */
    class iterator
    {
    public:
        // Constructors - must be implemented below!
        iterator();
        iterator(Node<Key,Value>* ptr);

        // Various operators - some must be implemented below!
        std::pair<Key,Value>& operator*(); // Already implemented for you.
        std::pair<Key,Value>* operator->(); // Already implemented for you.
        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;
        iterator& operator=(const iterator& rhs);
        iterator& operator++();

    protected:
        // A pointer to the current node.
        Node<Key, Value>* mCurrent;


        /* Feel free to add additional data members / helper functions! */
        
    };
    // Access to data through iterators, just like you are used to 
    // with std::map, std::set,
    // std::vector, etc.
    iterator begin();
    iterator end();
    iterator find(const Key& key); // remember a find
                               // also requires splaying
 
protected:
	void deleteAll (Node<Key, Value>* root);
	void splay (Node<Key, Value>* n);
	void printRoot (Node<Key, Value>* root) const;
	Node<Key, Value>* internalFind(const Key& key) const
 private:
  // Add any private data members and member functions as needed. 
 	void rotateLeft (Node<Key, Value> *n);
    void rotateRight (Node<Key, Value> *n);

};

#endif

// ---------------------------------------------------------------
// Begin implementations for the SplayTree::iterator class.
// ---------------------------------------------------------------
// */

/**
* Initialize the internal members of the iterator.
* You can choose what kind of iterator the default constructor should create.
*/
template<typename Key, typename Value>
SplayTree<Key, Value>::iterator::iterator()
: mCurrent(NULL)
{
    // TODO
}

/**
* Initialize the internal members of the iterator.
*/
template<typename Key, typename Value>
SplayTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
: mCurrent(ptr)
{
    // TODO -- did it, see above
}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& SplayTree<Key, Value>::iterator::operator*()
{
    return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>* SplayTree<Key, Value>::iterator::operator->()
{
    return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool SplayTree<Key, Value>::iterator::operator==
(const SplayTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if (mCurrent == rhs->mCurrent) return true;
    return false; // A dummy return value until you provide your 
    //implementation.
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool SplayTree<Key, Value>::iterator::operator!=
(const SplayTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if (mCurrent != rhs->mCurrent) return true;
    return false; // A dummy return value until you provide your 
    //implementation.
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator& SplayTree<Key, 
Value>::iterator::operator=(const SplayTree<Key, Value>::iterator& rhs)
{
    // TODO -- lhs should be set to rhs
    mCurrent = rhs->mCurrent; 
    return *this; // A dummy return value until you provide your 
    //implementation.
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator& 
SplayTree<Key, Value>::iterator::operator++()
{
    // TODO

    mCurrent = successor(mCurrent);
    return *this; // A dummy return value until you 
    //provide your implementation.
}


/*
-------------------------------------------------------------
End implementations for the SplayTree::iterator class.
-------------------------------------------------------------
*/


template<typename Key, typename Value>
SplayTree<Key, Value>::SplayTree() //: BinarySearchTree()
{
	
}
template<typename Key, typename Value>
SplayTree<Key, Value>::~SplayTree()
{

}

// All of the basic operations that one would perform on a map. 
// Do not change these function definitions, but you may add others

template<typename Key, typename Value>
void SplayTree<Key, Value>::splay (Node<Key, Value>* n)
{
	Node<Key, Value> p = parent(n);
	if (p==NULL)
	{
		return;
	}
	else 
	{
		Node<Key, Value> g = parent(p);
		if (g==NULL)
		{
			if(g->getLeft()==p)
			{
				rotateRight(p);
			}
			else if (g->getRight()==p)
			{
				rotateLeft(p);
			}
		}
		else //g!=NULL
		{
			if(g->getLeft()== p && p->getLeft() == n)
			{
				rotateRight(g);
				rotateRight(p);
				//what about children?
			}
			else if (g->getLeft() == p && p->getRight() == n)
			{
				rotateLeft(p);
				rotateRight(g);
			}
			else if (g->getRight() == p && p->getLeft() == n)
			{
				rotateRight(p);
				rotateLeft(g);
			}
			else if (g->getRight() == p && p->getRight() == n)
			{
				rotateLeft(g);
				rotateLeft(p);
			}
			splay(n);
		}
	}
}

/**
* Rotates n down and to the left
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::rotateLeft (Node<Key, Value> *n)
{
    // TODO
    Node<Key, Value>* p = n->getParent();
    Node<Key, Value>* pullUp = n->getRight();
    Node<Key, Value>* lsub = pullUp->getLeft();

    if (p!=NULL)
    {
       
        if (p->getLeft() == n)
        {
            p->setLeft(pullUp);
            n->setParent(pullUp);
            n->setRight(lsub);
            if (lsub != NULL)
            {
                lsub->setParent(n);
            }
            pullUp->setParent(p);
            pullUp->setLeft(n);
        }
        else if (p->getRight() == n)
        {
            p->setRight(pullUp);
            n->setParent(pullUp);
            n->setRight(lsub);
            if (lsub != NULL)
            {
                lsub->setParent(n);
            }
            pullUp->setParent(p);
            pullUp->setLeft(n);
        } 
    }

    else
    {
        n->setParent(pullUp);
        n->setRight(lsub);
        if (lsub != NULL)
        {
            lsub->setParent(n);
        }
        pullUp->setParent(NULL);
        pullUp->setLeft(n);
        this->mRoot = pullUp;
    }
}

/**
* Rotates n down and to the right
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::rotateRight (Node<Key, Value> *n)
{
    // TODO
    Node<Key, Value>* p = n->getParent();
    Node<Key, Value>* pullUp = n->getLeft();
    Node<Key, Value>* rsub = pullUp->getRight();
    if (p!=NULL)
    {
       
        if (p->getLeft() == n)
        {
            p->setLeft(pullUp);
            n->setParent(pullUp);
            n->setLeft(rsub);
            if (rsub != NULL)
            {
                rsub->setParent(n);
            }
            pullUp->setParent(p);
            pullUp->setRight(n);
        }
        else if (p->getRight() == n)
        {
            p->setRight(pullUp);
            n->setParent(pullUp);
            n->setLeft(rsub);
            if (rsub != NULL)
            {
                rsub->setParent(n);
            }
            pullUp->setParent(p);
            pullUp->setRight(n);
        } 
    }

    else
    {
        n->setParent(pullUp);
        n->setLeft(rsub);
        if (rsub != NULL)
        {
            rsub->setParent(n);
        }
        pullUp->setParent(NULL);
        pullUp->setRight(n);
        this->mRoot = pullUp;
    }
}
/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
* remember a find also requires splaying
*/

template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator 
SplayTree<Key, Value>::find(const Key& k) 
{
    // TODO
    iterator it(internalFind(k)); //Katie make your own new internalFind
    return it; // A dummy return value until you provide your implementation.
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::internalFind(
    const Key& key) const
{
    Node<Key, Value>* curr = mRoot;
    while (curr)
    {
        if (curr->getKey() == key)
        {
            return curr;
        }
        else if (key < curr->getKey())
        {
            curr = curr->getLeft();
            //splay
        }
        else
        {
            curr = curr->getRight();
            //splay
        }
    }
    return NULL;
}


/**
* Insert function for a key value pair. Finds location to insert 
* the node.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    // TODO
    Node<Key, Value>* newNode = new Node<Key, Value> 
    (keyValuePair.first, keyValuePair.second, NULL);

    if (this->mRoot == NULL) 
    {
        this->mRoot = newNode;
        return;
    }

    else
    {
        Node<Key, Value>* currentNode = static_cast
        <Node<Key, Value>*>(this->mRoot);
        while(1)
        {
            if (newNode->getKey() < currentNode->getKey()) 
            //trace down or add node to LEFT path (-1)
            {
                if (currentNode->getLeft() == NULL)
                {
                    
                    currentNode->setLeft(newNode);
                    newNode->setParent(currentNode);
         			//splay
                    return;
                }
                currentNode = currentNode->getLeft();
            }
            else if (newNode->getKey() > currentNode->getKey()) 
            //trace down or add node to RIGHT path (+1)
            {
                if (currentNode->getRight() == NULL)
                {
                    currentNode->setRight(newNode);
                    newNode->setParent(currentNode);  
                    //splay      
                    return;
                }
                currentNode = currentNode->getRight();
            }
            else 
            {
                currentNode->setValue(newNode->getValue());
                //splay
                return;
            }
        }
    }
}





// /**
// * Helper function to delete all the items
// */
// template<typename Key, typename Value>
// void SplayTree<Key, Value>::deleteAll (Node<Key, Value>* root)
// {
//     if (root != NULL)
//     {
//         deleteAll (root->getLeft());
//         deleteAll (root->getRight());
//         delete root;
//     }
// }

// /**
// * A method to remove all contents of the tree and reset the values in the tree
// * for use again.
// */
// template<typename Key, typename Value>
// void SplayTree<Key, Value>::clear()
// {
//     deleteAll(mRoot);
//     mRoot = NULL;
// }
template<typename Key, typename Value>
void SplayTree<Key, Value>::print() const
{
    printRoot(this->mRoot);
    std::cout << "\n";
}

/**
* Helper function to print the tree's contents
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{
    if (root != NULL)
    {
        std::cout << "[";
        printRoot (root->getLeft());
        std::cout << " (" << root->getKey() << ", " << root->getValue() 
        << ") ";
        printRoot (root->getRight());
        std::cout << "]";
    }
}
