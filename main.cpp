//  Main program for testing bTree implementation.
// clint goldstein
// cs 302 sec 002
// ast05
// A class that simulates IPv4 router using a b tree and circle queue
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#include "routerSim.h"
#include "linkedQueue.h"

using namespace std;

int main(int argc, char *argv[])
{
    
    // *****************************************************************
    //  Headers...
    
    string	bars, stars;
    bars.append(65, '-');
    stars.append(65, '*');
    
    string	routingTableFile;
    string	ipAddressesFile;
    string	routesFile;
    
    cout << bars << endl << "CS 302 - Assignment #5" << endl;
    cout << endl;
    
    // ----------------------------------------
    //  Check command line parameters (one at a time).
    
    if (argc == 1) {
        cout << "Usage: router -t <ipRoutingTable> -s <sourceIPs>";
        cout << " -o <outputFile>" << endl;
        return 0;
    }
    
    if (argc != 7) {
        cout << "Error, invalid command line options." << endl;
        return	0;
    }
    
    if (string(argv[1]) != "-t") {
        cout << "main: Invalid routing table specifier." << endl;
        return 0;
    }
    
    if (access(argv[2], F_OK) == -1) {
        cout << "main: Error, routing table file does not exist." << endl;
        return	0;
    }
    routingTableFile = string(argv[2]);
    
    if (string(argv[3]) != "-s") {
        cout << "main: Invalid source IP addresses file specifier." << endl;
        return 0;
    }
    
    if (access(argv[4], F_OK) == -1) {
        cout << "main: Error, source IP addresses file does not exist." << endl;
        return	0;
    }
    ipAddressesFile = string(argv[4]);
    
    if (string(argv[5]) != "-o") {
        cout << "main: Invalid output file specifier." << endl;
        return 0;
    }
    
    if (string(argv[6]) == "") {
        cout << "main: Invalid output file." << endl;
        return 0;
    }
    routesFile = string(argv[6]);
    
    // ----------------------------------------
    //  Read routing table and show stats (for reference)
    
    routerSim	myRouter;
    
    if (!myRouter.readRoutingTable(routingTableFile)) {
        cout << "main: Error, unable to read rouing file "
        << routingTableFile << "." << endl;
        return	0;
    }
    
    myRouter.showTotalRoutesCount();
    myRouter.showBTreeNodesCount();
    myRouter.showTreeHeight();
    
    // ----------------------------------------
    //  Some simple testing...
    
    /*
     linkedQueue<string>	ipMatches;
     
     myRouter.findMatches("192.125", ipMatches);
     
     cout << endl;
     if (!ipMatches.isEmpty()) {
     cout << "Count: " << ipMatches.getQueueCount() << endl;
     ipMatches.printQueue();
     }
     */
    
    // ----------------------------------------
    //  Read input file, create output file
    
    myRouter.doRouting(ipAddressesFile, routesFile);
    
    
    // *****************************************************************
    //  All done.
    
    cout << endl << bars << endl;
    cout << "Game Over, thank you for playing." << endl;
    
    return 0;
}

