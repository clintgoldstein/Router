//
//  routerSim.cpp
//  hw05
//
//  Created by clint goldstein on 9/28/15.
//  Copyright © 2015 clint goldstein. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "routerSim.h"
#include <limits> 
using namespace std;

linkedQueue<string> routerQ;

routerSim::routerSim()
//consructor
{
    totalRoutesCount=0;
    
}

void routerSim::showTotalRoutesCount()const
//outputs a message containing totalroutscount to the screen
{
    cout<<"Total Routes Count: "<<totalRoutesCount<<endl;
}

bool routerSim::readRoutingTable(const string fname)
{
    string data;
    ifstream infile(fname.c_str());
    if (infile.good() == true)
    {
        while(getline(infile, data))
        {
            rTableTree.insert(data);
            totalRoutesCount++;
        }
        infile.close();
        return true;
    }
    else
        return false;
    
}

void routerSim::showBTreeNodesCount() const
{
    cout<<"Tree Node Count: "<<rTableTree.nodeCount()<<endl;
}

void routerSim::showTreeHeight() const
{
    cout<<"bTree Height: "<<rTableTree.bTreeHeight()<<endl;
}

bool routerSim::search(const string data)
{
    bTreeNode<string> *nd=NULL;
    nd=rTableTree.search(data);
    if(nd==NULL)
        return false;
    else
        return true;
}

void routerSim::findMatched(string data, linkedQueue<string>& routerQ) const
//search the bTree and return a linked queue containing any entries that start with the passed string
{
    rTableTree.fuzzySearch(data, routerQ);
    
}

void routerSim::doRouting(string ipAddressesFile, string routesFile) const
//reading the source IP's from the passed file name, finding the appropriate destination address, and writing the source address and destination
//address to the passed output file
{
    string network;
    string destination;
    string data;
    string::size_type delin; //finds the first '.'
    ifstream infile(ipAddressesFile.c_str());
    ofstream outfile(routesFile.c_str());
    while (getline(infile, data) )
    {
        outfile << data<<"\t";
        delin=data.find_first_of('.');
        delin=data.find_first_of('.', delin+1); //cuts off everything after the network numbers
        network=data.substr(0, delin);
        findMatched(network, routerQ);          //use the truncated ip address to find matches
        destination=selectDestination(routerQ);
        outfile << destination<< "\n";
    }
    
}

void routerSim::split(const string tableLine, string& asPrefix, string& destination) const
//split a routing table entry into 2 strings a AS prefix and a destination address
{
    string::size_type pipeOne;
    string::size_type pipeTwo;
    pipeOne=tableLine.find_first_of('|');
    pipeTwo=tableLine.find_last_of('|');
    asPrefix=tableLine.substr(pipeOne, pipeTwo);
    destination=tableLine.substr(pipeTwo+1);
}

string routerSim::selectDestination(linkedQueue<string>& routerQ) const
//accepts a linked queue of routing table entries, and returns the final destination address selected based
//on the minimum sum of the AS prefixes.
{
    string asPrefix;
    string destination;
    string returnDest;
    int temp=0;
    int total=0;
    int min=numeric_limits<int>::max();

    if (routerQ.isEmpty()==true)
    {
        return "No Match.";
    }
    else
    {
        stringstream ss;
        while( routerQ.getQueueCount()!=0) //split the table entry
        {
            split(routerQ.front(), asPrefix, destination);
            //now find the sum of the AS prefixes
            ss<<asPrefix;
            while(ss>>temp)
                  {
                      total+=temp;
                  }
            if (total<min)
            {
                min=total;
                returnDest=destination;
            }
            total=0;
            ss.clear();
            routerQ.deleteItem();
        }
        return returnDest;
        
    }
}

















