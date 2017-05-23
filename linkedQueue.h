//
//  linkedQueue.h
//  hw04
//
//  Created by clint goldstein on 9/19/15.
//  Copyright (c) 2015 clint goldstein. All rights reserved.
//

#ifndef hw04_linkedQueue_h
#define hw04_linkedQueue_h
#define SIZE 100
#include <string>
#include <cstdlib>
#include <iostream>


template <class myType>
struct queueNode {
    myType dataSet[SIZE];
    int   front, back;
    queueNode<myType> *link;
};

template <class myType>
class linkedQueue
{
public:
    //consructor
    linkedQueue();
    //destructor
    ~linkedQueue();
    
    //public member functions
    const bool isEmpty();
    int getQueueCount();
    int getLinkCount();
    void add(const myType &newItem);
    const myType front();
    const myType back();
    void deleteItem();
    void printQueue();
    
private:
    //private
    int count;
    int linkCount;
    queueNode<myType> *queueFront;
    queueNode<myType> *queueBack;
    queueNode<myType> *p;        //and extre pointer for utility
};

/////funtion implimentation for linkedQueue
template <class myType>
linkedQueue<myType>::linkedQueue()
{
    count=0;      //initialize all counts to 0
    linkCount=0;
    queueFront=NULL;
    queueBack=NULL;
    p=NULL;
}

template <class myType>
linkedQueue<myType>::~linkedQueue()
{
    delete queueFront;
    queueFront=NULL;
    queueBack=NULL;
    p=NULL;
    
}


template <class myType>
const bool linkedQueue<myType>::isEmpty()
{
    if (count==0) {
        return true;
    }
    else
        return false;
}

template <class myType>
int linkedQueue<myType>::getLinkCount()
{
    return linkCount;
}

template <class myType>
int linkedQueue<myType>::getQueueCount()
{
    return count;
}

template <class myType>
void linkedQueue<myType>::add(const myType &newItem)
//adds a new item to back of the queue
{
    if (count==0)  //if fist element creat the first node
    {
        queueFront=new queueNode<myType>;
        queueBack=queueFront;
        queueFront->front=0;
        queueFront->back=0;
        linkCount++;
    }
    else if ((queueBack->front==0 && queueBack->back==99)||(queueBack->front==queueBack->back+1))
        //if a node is full create a new node
    {
        p=new queueNode<myType>;
        p->link=queueBack;
        queueBack=p;
        queueBack->front=0;
        queueBack->back=0;
        linkCount++;
    }
    else if(queueBack->back==99 && queueBack->front!=0)
        //circle queue fills space in front for efficiency
    {
        queueBack->back=0;
    }
    else
    {
        queueBack->back++;
    }
    
    queueBack->dataSet[queueBack->back]=newItem;
    count++;
}

template <class myType>
void linkedQueue<myType>::deleteItem()
{
    if (count!=0)
    {
        if (queueFront->front==queueFront->back) //if the remove empties the node delete the node
        {
            p=queueFront;
            queueFront=queueBack;
            //delete p;
            for (int i=1; i<linkCount-1; i++) {
                queueFront=queueFront->link;
            }
            queueFront->link=NULL;
            linkCount--;
            count--;
        }
        else if (queueFront->back!=99 && queueFront->front==99)
            //its circular so check if back is in the middle
        {
            queueFront->front=0;
            count--;
        }
        else                //otherwise readjust the front of the queue and count
        {
            queueFront->front++;
            count--;
        }
    }
}

template <class myType>
const myType linkedQueue<myType>::back()
//returns the back of the queue
{
    return queueBack->dataSet[queueBack->back];
}

template <class myType>
//returns the front of the queue
const myType linkedQueue<myType>::front()
{
    return queueFront->dataSet[queueFront->front];
}

template <class myType>
void linkedQueue<myType>::printQueue()
//prints the queue
{
    p=queueFront; //p is used as a cursor here
    for (int i=linkCount; i>0; i--)
    {
        for (int j=p->front; j<=p->back; j++) {
            std::cout<<p->dataSet[j]<<std::endl;
        }
        p=queueBack;
        for (int k=1; k<i; k++) {
            p=p->link;
        }
    }
}
#endif