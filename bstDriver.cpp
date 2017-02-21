//-----------------------------------------------------------------------------
//   File: bstDriver.cpp
//
//	 Function: main
//-----------------------------------------------------------------------------
#include <iostream>
#include <cstdlib>
#include "bst.h"
#include "bstinherited.h"
using namespace std;

//-------------------------------------------------------------------------------------------
//    Function:			main()
//
//    File:             bstDriver.cpp
//
//    Title:            AVL tree
//
//    Description:		This file contains function main() of AVL tree
//	  
//
//    Programmer:		Reinaldo Daniswara
//   
//    Date:             6/6/2016
// 
//    Version:          1.0
//  
//    Environment:   Intel COre i7
//						Software: MS Windows 10 for execution;
//						Compiles under Microsoft Visual Studio 2015
// 
//    Input:			None
// 
//    Output:			Screen display of 
// 
//    Calls:            findfirst(), insert(), printXlevel(), 
//						pophigh(), poplow(), popfirst()
// 
//    Called By:		n/a
// 
//    Parameters:		None
// 
//    Returns:          EXIT_SUCCESS  = successful 
//					    EXIT_FAILURE = catch exception 
//
//    History Log:
//                          6/6/2016  RD  completed version 1.0
// ----------------------------------------------------------------------------
int main(void)
{
	using RD_BST::bst;
	using RD_BST::node;
	using RD_BST::avltree;
	try
	{
		avltree<char> tree;
		node<char>* marker = NULL;
		char c;
		cout << "Welcome to AVL Tree by Reinaldo Daniswara" << endl;
		cout << "-----------------------------------------------------" << endl << endl;
		cout << "Enter some characters, followed by <Enter>.\n" ;
		do
		{ 
			cin.get(c);
			if(c == '\n')
				break;
			tree.insert(c); 
		}
		while(1);
		tree.printXlevel(cout);

		cout << endl << "Search : " << endl;
		cin.get(c);
		cin.ignore(256, '\n');
		tree.findfirst(c, tree.getroot(), marker);
		
		if (marker != NULL)
				cout << marker->value() << " is found!";
			else
				cout << " is not found";
		cout << endl << endl; 

		cout << "Whal element do you want to delete (popfirst): ";
		cin.get(c);
		cin.ignore(256, '\n');
		tree.popfirst(c, tree.getroot());
		tree.printXlevel(cout);
		cout << endl;
	
		cout << "Whal element do you want to delete (pophigh): ";
		cin.get(c);
		cin.ignore(256, '\n');
		marker = nullptr;
		tree.findfirst(c, tree.getroot(), marker);
		tree.pophigh(marker);
		tree.printXlevel(cout);
		cout << endl;

		cout << "Whal element do you want to delete (poplow): ";
		cin.get(c);
		cin.ignore(256, '\n');
		marker = nullptr;
		tree.findfirst(c, tree.getroot(), marker);
		tree.poplow(marker);
		tree.printXlevel(cout);
		cout << endl;

		cout << "Copying the first tree..." << endl;
		avltree<char> treetwo(tree);
		treetwo.printXlevel(cout);
		cout << endl;

		cout << "Insert use += operator.\n";
		cin.get(c);
		cin.ignore(256, '\n');
		treetwo += c;
		treetwo.printXlevel(cout);
		cout << endl;

		cout << "Delete the element of tree two : ";
		cin.get(c);
		cin.ignore(256, '\n');
		treetwo.popfirst(c, treetwo.getroot());
		treetwo.printXlevel(cout);
		
		tree.deltree(); //clean up the memory
		treetwo.deltree(); //clean up the memory
	}
	catch(exception e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	catch(...)
	{
		cout << "Unknown Exception: " << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	cout << "press \"Enter\" to continue" << endl;
	cin.get(); // keep window open
	return EXIT_SUCCESS;
} 
