// Header file bTree.h

#ifndef H_BTREE
#define H_BTREE

#include <iostream>
#include <string>

#include "linkedQueue.h"

using namespace std;

// *********************************************************************
//  CS 302 B-Tree implementation

// ----------
//  Definition of the node


template <class myType>
struct bTreeNode
{
    myType			*keys;		// array of keys
    bTreeNode<myType>	**child;		// array of child pointers
    int			n;		// current number of keys
    bool			leaf;		// true when node is leaf. Otherwise false
};

template <class myType>
class bTree
{
public:
    // constructor, destructor
    bTree(int=6);
    ~bTree();
    
    // destroy tree (delete all dynamic memory)
    void	destroyTree(bTreeNode<myType> *);
    
    // print tree
    void	printTree() const;
    
    // function to search a key in this tree
    bTreeNode<myType> * search(myType) const;
    
    void fuzzySearch(myType, linkedQueue<myType> &) const;
    
    // function that inserts a new key in this B-Tree
    void	insert(myType);
    
    // simple testing fucntion to count nodes in bTree
    int	nodeCount() const;
    int	bTreeHeight() const;
    
private:
    int		degree;			// maximum degree
    int		ndCnt;			// node count
    bTreeNode<myType>	*root;		// root node
    
    // utility function to make new node
    bTreeNode<myType> * makeNewNode(bool);
    
    // print support funciton
    void	printTree(bTreeNode<myType> *) const;
    
    // search helper function
    bTreeNode<myType> * search(bTreeNode<myType> *, myType) const;
    
    // fuzzy search helper
    void fuzzySearch(bTreeNode<myType> *,
                     myType, linkedQueue<myType> &) const;
    
    // insert a new key in the subtree rooted with this node
    void insertNonFull(bTreeNode<myType> *, myType);
    
    // split the child of this node.
    void splitChild(bTreeNode<myType> *, int, bTreeNode<myType> *);
    
};

// *********************************************************************

template <class myType>
bTree<myType>::bTree(int inDegree)
{
    root = NULL;
    degree = inDegree;
    ndCnt = 0;
}

template <class myType>
bTree<myType>::~bTree()
{
    if (root != NULL)
        destroyTree(root);
    
    root = NULL;
}

template <class myType>
void bTree<myType>::destroyTree(bTreeNode<myType> *nd)
{
    if (nd != NULL) {
        delete [] nd->keys;
        for (int i=0; i < degree; i++)
            destroyTree(nd->child[i]);
    }
    
    delete	nd;
}

// ---------------------------------------------------------------------
//  Basic utility/testing functions

template <class myType>
int bTree<myType>::nodeCount() const
{
    return	ndCnt;
}

template <class myType>
int bTree<myType>::bTreeHeight() const
{
    int	cnt=0;
    bTreeNode<myType> *curr;
    
    curr = root;
    while (curr != NULL) {
        cnt++;
        curr = curr->child[0];
    }
    
    return	cnt;
}

// ---------------------------------------------------------------------
//  Function to traverse and print all nodes in a subtree
//	rooted with this node
//	there are n keys and n+1 children, traverse through
//	n keys and first n children

template <class myType>
void bTree<myType>::printTree() const
{
    printTree(root);
}

template <class myType>
void bTree<myType>::printTree(bTreeNode<myType> *nd) const
{
    int	i;
    
    for (i=0; i < nd->n; i++) {
        if (!nd->leaf)
            printTree(nd->child[i]);
        cout << " " << nd->keys[i];
    }
    
    if (!nd->leaf)
        printTree(nd->child[i]);
}

// ---------------------------------------------------------------------
//  Function to search key k in subtree rooted with this node

template <class myType>
bTreeNode<myType>* bTree<myType>::search(myType k) const
{
    if (root == NULL)
        return NULL;
    else
        return search(root, k);
}

template <class myType>
bTreeNode<myType>* bTree<myType>::search(bTreeNode<myType> *nd, myType k) const
{
    // find the first key greater than or equal to k
    int	i = 0;
    
    while ((i < nd->n) && (k > nd->keys[i]))
        i++;
    
    // if the found key is equal to k, return this node
    if (nd->keys[i] == k)
        return	nd;
    
    // if key is not found here and this is a leaf node
    if (nd->leaf == true)
        return	NULL;
    
    // go to the appropriate child
    return	search(nd->child[i], k);
}

// ---------------------------------------------------------------------
//  Function to search substring key k

template <class myType>
void bTree<myType>::fuzzySearch(myType k, linkedQueue<myType> &resultQ) const
{
    if (root != NULL)
        fuzzySearch(root, k, resultQ);
}


template <class myType>
void bTree<myType>::fuzzySearch(bTreeNode<myType> *nd, myType k,
                                linkedQueue<myType> &ansQ) const
{
    int	i = 0;
    int	len = k.length();
    
    // find the first key greater than or equal to k
    while ((i < nd->n) && (k > nd->keys[i]))
        i++;
    
    // if the found key is equal to k, return this node
    
    for (; i < nd->n; i++) {
        if (!nd->leaf)
            fuzzySearch(nd->child[i], k, ansQ);
        if (nd->keys[i].substr(0,len) == k)
            ansQ.add(nd->keys[i]);
    }
    
    // if key is not found here and this is a leaf node
    if (!nd->leaf)
        fuzzySearch(nd->child[i], k, ansQ);
}

// ---------------------------------------------------------------------
//  Utility function to make a new node with the dynamic allocations
//	for keys and children.  Chldren initialized to NULLs.

template <class myType>
bTreeNode<myType> * bTree<myType>::makeNewNode(bool leaf1)
{
    bTreeNode<myType>	*tmp;
    tmp = new bTreeNode<myType>;
    
    // set leaf property
    tmp->leaf = leaf1;
    
    // allocate keys and child pointers
    tmp->keys = new myType[degree-1];
    tmp->child = new bTreeNode<myType> *[degree];
    
    // init all children ptrs to NULL
    for (int i=0; i<(degree); i++)
        tmp->child[i] = NULL;
    
    // init key count to 0
    tmp->n = 0;
    
    ndCnt++;
    
    return	tmp;
}

// ---------------------------------------------------------------------
//  Main B-Tree insertion function.

template <class myType>
void bTree<myType>::insert(myType k)
{
    // if tree is empty
    if (root == NULL) {
        // allocate new root
        root = makeNewNode(true);
        root->keys[0] = k;		// insert key
        root->n = 1;			// set keys
    } else {
        // if root is full, then tree grows in height
        if (root->n == degree-1) {
            // allocate new root
            bTreeNode<myType> *s = makeNewNode(false);
            
            // make old root as child of new root
            s->child[0] = root;
            
            // split the old root and move 1 key to the new root
            splitChild(s, 0, root);
            
            // new root has two children now, so decide which of
            // the children is going to have new key
            int i = 0;
            if (s->keys[0] < k)
                i++;
            insertNonFull(s->child[i], k);
            
            // set root
            root = s;
        }
        else {
            // if root is not full, call insertNonFull for root
            insertNonFull(root, k);
        }
    }
}

// ---------------------------------------------------------------------
//  A utility function to insert a new key in this node
//  Note, the node must be non-full when this function is called

template <class myType>
void bTree<myType>::insertNonFull(bTreeNode<myType> *nd, myType k)
{
    // init i as index of rightmost element
    int	i = nd->n-1;
    
    // if this is a leaf node
    if (nd->leaf) {
        // loop does
        // - find location of new key to be inserted
        // - move greater keys to one place ahead
        while (i >= 0 && nd->keys[i] > k) {
            nd->keys[i+1] = nd->keys[i];
            i--;
        }
        
        // insert the new key at found location
        nd->keys[i+1] = k;
        nd->n += 1;
    }
    else {
        // node is NOT leaf
        // find the child which is going to have the new key
        while ((i >= 0) && (nd->keys[i] > k))
            i--;
        
        // see if the found child is full
        if (nd->child[i+1]->n == degree-1) {
            // if the child is full, then split it
            splitChild(nd, i+1, nd->child[i+1]);
            
            // after split, the middle key of child[i] goes up and
            // child[i] is split into two. Pick which gets new key
            if (nd->keys[i+1] < k)
                i++;
        }
        insertNonFull(nd->child[i+1], k);
    }
}

// ---------------------------------------------------------------------
//  A utility function to split the child y of this node
//  Note that y must be full when this function is called

template <class myType>
void bTree<myType>::splitChild(bTreeNode<myType> *nd, int i, bTreeNode<myType> *y)
{
    // create a new node to store (t-1) keys of y
    bTreeNode<myType> *z = makeNewNode(y->leaf);
    z->n = degree/2 - 1;
    
    // copy the last (t-1) keys of y to z
    for (int j = 0; j < degree/2-1; j++)
        z->keys[j] = y->keys[j+degree/2];
    
    // copy the last t children of y to z
    if (!y->leaf) {
        for (int j=0; j < degree/2; j++) {
            z->child[j] = y->child[j+degree/2];
            y->child[j+degree/2] = NULL;
        }
    }
    
    // reduce the number of keys in y
    y->n = degree/2 - 1;
    
    // node is going to have a new child, create space of new child
    for (int j = nd->n; j >= i+1; j--)
        nd->child[j+1] = nd->child[j];
    
    // link the new child to this node
    nd->child[i+1] = z;
    
    // a key of y will move to this node. Find location of
    // new key and move all greater keys one space ahead
    for (int j = nd->n-1; j >= i; j--)
        nd->keys[j+1] = nd->keys[j];
    
    // copy the middle key of y to this node
    nd->keys[i] = y->keys[degree/2-1];
    
    // increment count of keys in this node
    nd->n += 1;
}

#endif

