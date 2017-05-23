//
//  routerSim.h
//  hw05
//
//  Created by clint goldstein on 9/25/15.
//  Copyright © 2015 clint goldstein. All rights reserved.
//
#include <string>
#include <cstdlib>
#include "linkedQueue.h"
#include "bTree.h"

#ifndef routerSim_h
#define routerSim_h

class routerSim
{
public:
    //constructor
    routerSim();
    
    //public member functions
    bool readRoutingTable(const std::string);
    void showTotalRoutesCount() const;
    void showBTreeNodesCount() const;
    void showTreeHeight() const;
    bool search(const std::string);
    void findMatched(std::string, linkedQueue<std::string>&) const;
    void doRouting(const std::string,const std::string) const;
    
private:
    unsigned int totalRoutesCount;
    bTree<std::string> rTableTree;
    int count; 
    
    //private member functions
    void split(const std::string, std::string&, std::string&) const;
    std::string selectDestination(linkedQueue<std::string>&) const;
};
#endif /* routerSim_h */
