//  Main program for testing bTree implementation.

#include <iostream>
#include <fstream>
#include <string>

#include "bTree.h"

using namespace std;

int main()
{

// *****************************************************************
//  Headers...

	string	bars, stars;
	bars.append(65, '-');
	stars.append(65, '*');

	cout << bars << endl << "CS 302 - Assignment #5" << endl;
	cout << endl;

// *****************************************************************
//  Testing for bTree functions with different types.

// ----------------------------------------
//  Testing with integers.

	bTree<int>	myTree(4);		// A B-Tree with degree 4

	myTree.insert(10);
	myTree.insert(20);
	myTree.insert(5);
	myTree.insert(6);
	myTree.insert(12);
	myTree.insert(30);
	myTree.insert(7);
	myTree.insert(17);

	cout << "Current Tree: ";
	myTree.printTree();
	cout << endl;

	cout << "bTree Height: " << myTree.bTreeHeight() << endl;
	cout << "bTree Node Count: " << myTree.nodeCount() << endl;
	cout << endl;

	if (myTree.search(6) == NULL)
		cout << "main: Error, 6 not found." << endl;

	if (myTree.search(15) != NULL)
		cout << "main: Error, 15 incorrectly found." << endl;

	cout << endl << bars << endl << endl;

// ----------------------------------------
//  Testing with shorts.

	bTree<short> myTree1(6);		// A B-Tree with degree 6

	myTree1.insert(1);
	myTree1.insert(3);
	myTree1.insert(7);
	myTree1.insert(10);
	myTree1.insert(11);
	myTree1.insert(13);
	myTree1.insert(14);
	myTree1.insert(15);
	myTree1.insert(18);
	myTree1.insert(16);
	myTree1.insert(19);
	myTree1.insert(24);

	cout << "Traversal of partial tree is\n";
	myTree1.printTree();
	cout << endl;

	myTree1.insert(9);
	myTree1.insert(25);
	myTree1.insert(21);
	myTree1.insert(4);
	myTree1.insert(5);
	myTree1.insert(20);
	myTree1.insert(22);
	myTree1.insert(2);
	myTree1.insert(17);
	myTree1.insert(12);
	myTree1.insert(6);

	cout << "Traversal of complete tree is\n";
	myTree1.printTree();
	cout << endl;

	cout << "bTree Height: " << myTree1.bTreeHeight() << endl;
	cout << "bTree Node Count: " << myTree1.nodeCount() << endl;
	cout << endl;

	cout << endl << bars << endl << endl;

// ----------------------------------------
//  Testing with strings.

	bTree<string>	myTree2(6);		// A B-Tree with degree 6

	linkedQueue<string>	resultsA;
	linkedQueue<string>	resultsB;
	linkedQueue<string>	resultsC;
	linkedQueue<string>	resultsD;

	myTree2.insert("lemon");
	myTree2.insert("orange");
	myTree2.insert("pear");
	myTree2.insert("peach");
	myTree2.insert("grape");
	myTree2.insert("grapefruit");
	myTree2.insert("apricot");
	myTree2.insert("blueberry");
	myTree2.insert("avacado");
	myTree2.insert("mango");
	myTree2.insert("melon");
	myTree2.insert("cantaloupe");
	myTree2.insert("blackberry");
	myTree2.insert("cherry");
	myTree2.insert("coconut");
	myTree2.insert("cranberry");
	myTree2.insert("apple");
	myTree2.insert("banana");
	myTree2.insert("date");
	myTree2.insert("fig");
	myTree2.insert("boysenberry");
	myTree2.insert("huckleberry");
	myTree2.insert("strawberry");
	myTree2.insert("kiwi");
	myTree2.insert("lime");
	myTree2.insert("nectarine");
	myTree2.insert("papaya");
	myTree2.insert("raspberry");

	cout << "Current Tree: ";
	myTree2.printTree();
	cout << endl;

	cout << "bTree Height: " << myTree2.bTreeHeight() << endl;
	cout << "bTree Node Count: " << myTree2.nodeCount() << endl;
	cout << endl;
	cout << endl;

	cout << "Matches for 'gra'" << endl;
	cout << "-----------------" << endl;
	myTree2.fuzzySearch("gra", resultsA);
	resultsA.printQueue();
	cout << endl;

	cout << "Matches for 'pe'" << endl;
	cout << "---------------" << endl;
	myTree2.fuzzySearch("pe", resultsB);
	resultsB.printQueue();
	cout << endl;

	cout << "Matches for 'b'" << endl;
	cout << "---------------" << endl;
	myTree2.fuzzySearch("b", resultsC);
	resultsC.printQueue();
	cout << endl;

	cout << "Matches for 'm'" << endl;
	cout << "---------------" << endl;
	myTree2.fuzzySearch("m", resultsD);
	resultsD.printQueue();
	cout << endl;

	if (myTree2.search("pear") == NULL)
		cout << "main: Error, 'pear' not found." << endl;

	if (myTree2.search("grapefruit") == NULL)
		cout << "main: Error, 'pear' not found." << endl;

	if (myTree2.search("potato") != NULL)
		cout << "main: Error, 'potato' incorrectly found." << endl;

//	cout << endl << bars << endl << endl;

// *****************************************************************
//  All done.

	cout << endl << bars << endl;
	cout << "Game Over, thank you for playing." << endl;

	return 0;
}

